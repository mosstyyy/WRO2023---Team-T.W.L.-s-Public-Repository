#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include "Freenove_4WD_Car_For_ESP32.h"
#include "BluetoothSerial.h"
#include <Arduino.h>
#include "Freenove_4WD_Car_For_ESP32.h"

#define OBSTACLE_DISTANCE      50
#define OBSTACLE_DISTANCE_LOW  30
int distance[4];     //Storage of ultrasonic data

String entradaSerial = "";
bool entradaCompleta = false;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error BLuetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

BluetoothSerial SerialBT;
 
const char* WIFI_SSID = "S.I.N La Picola";
const char* WIFI_PASS = "AurorA!156*";
 
WebServer server(80);
 
 
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600); 
void get_distance(int car_mode)
{
  int add_angle=30;
  if(car_mode==1)
    add_angle=0;
  else
    add_angle=30;
    
  Servo_2_Angle(90);  
  Servo_1_Angle(120+add_angle);
  delay(100);
  distance[0] = Get_Sonar();//Get the data on the left

  Servo_1_Angle(90);
  delay(100);
  distance[1] = Get_Sonar();//Get the data in the middle

  Servo_1_Angle(60-120);
  delay(100);
  distance[2] = Get_Sonar();//Get the data on the right

  Servo_1_Angle(90);
  delay(100);
  distance[1] = Get_Sonar();//Get the data in the middle
}

void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));
 
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}
 
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgMid()
{
  if (!esp32cam::Camera.changeResolution(midRes)) {
    Serial.println("SET-MID-RES FAIL");
  }
  serveJpg();
} 
 
 
void  setup(){
  Ultrasonic_Setup();
  PCA9685_Setup();  //Initializes the chip that controls the motor
  Serial.begin(115200);
  SerialBT.begin("IS THAT THE BITE OF 87?!");
  Serial.println("the bluetooth device is ready to pair");
  Serial.println();

  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::FreeNove);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
 
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("  /cam-lo.jpg");
  Serial.println("  /cam-hi.jpg");
  Serial.println("  /cam-mid.jpg");
 
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam-mid.jpg", handleJpgMid);
 
  server.begin();
}
 
void loop()
{
  get_distance(1);//Get multiple Angle distance data
  if (distance[1] > OBSTACLE_DISTANCE)//There is no obstacle within 40cm of the front of the car
  {
    if (distance[0] >= distance[2] && distance[2] < OBSTACLE_DISTANCE_LOW)    //There is an obstacle on the right
      Motor_Move(-1000, -1000, 2000, 2000);                                   
    else if (distance[0] < distance[2] && distance[0] < OBSTACLE_DISTANCE_LOW)//There is an obstacle on the left
      Motor_Move(2000, 2000, -1000, -1000);                                  
    else                                                                      //There are no obstacles around
      Motor_Move(1000, 1000, 1000, 1000);                                                                         
    delay(20);
  }

  else if (distance[1] < OBSTACLE_DISTANCE)  //There is an obstacle ahead
  {
    Motor_Move(0, 0, 0, 0);                  //Stop the car to judge the situation
    get_distance(2);
    if (distance[1] < OBSTACLE_DISTANCE_LOW) //The car got too close to the obstacle
      Motor_Move(-1000, -1000, -1000, -1000);
    else if (distance[0] < distance[2])      //There is also an obstacle on the left
      Motor_Move(2000, 2000, -2000, -2000);
    else if (distance[0] > distance[2])      //There is also an obstacle on the right
      Motor_Move(-2000, -2000, 2000, 2000);
    delay(200);
  }
  
  server.handleClient();
  if (SerialBT.available()) serialEvent();

  // Servo 1 motion path; 90°- 0°- 180°- 90°
  if (entradaCompleta) {
    if (entradaSerial == "izq\n") {
      Serial.print("coso");
      Motor_Move(0, 0, 0, 0);  
      delay(4000);
      Motor_Move(-2000, -2000, 2000, 2000);  //turn left
      delay(1000);
    }
  // Servo 2 motion path; 90°- 150°- 90°
  else if (entradaSerial == "der\n") {
    Serial.print("nose hola");
    Motor_Move(0, 0, 0, 0);  
    delay(4000);
    Motor_Move(2000, 2000, -2000, -2000);  //turn right
    delay(1000);
  }

  
   else { // Cualquier otro dato recibido
      Serial.println("El dato recibido es inválido!!");
    }
    entradaSerial = "";
    entradaCompleta = false;
  }

    if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (Serial.available()) {
    Serial.write(SerialBT.read());
  }
}

void serialEvent() {
  while (SerialBT.available()) {
    // Obtener bytes de entrada:
    char inChar = (char)SerialBT.read();
    // Agregar al String de entrada:
    entradaSerial += inChar;
    // Para saber si el string está completo, se detendrá al recibir
    // el caracter de retorno de línea ENTER \n
    if (inChar == '\n') {
      entradaCompleta = true;
    }
  }
}