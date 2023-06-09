Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2023 (Team T.W.L).

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction

_Hello, Here Luis from Team T.W.L., and together with my colleagues we will expand a little in the operation and elements present in the robotic solution for this 2023 season._

-------------------------------------------------------------------------------------------------------------------------------------  

  

_The designed robotic solution model consists of a robot car that uses pre-fabricated elements and is based on the ESP32 SoC chip. This chip is a microcontroller that integrates Wi-Fi and Bluetooth and allows programming the robot with the Arduino IDE environment. The ESP32 chip has 36 pins that can be used to connect the different sensors and actuators to the robot. In addition, the ESP32 chip has a dual-core processor that can run two tasks simultaneously, which increases the performance and efficiency of the robot._

_The robot car has the following main elements:_

  
  

   -   _Motors: The robot has four direct current (DC) motors that allow it to move in different directions. The motors are connected to an L298N motor controller that regulates the speed and direction of rotation of each motor. In addition, the robot has two servomotors that allow it to rotate the ultrasonic plate and the camera._  

  

   

   -   _Buzzer: The robot has a Buzzer integrated into the base plate. The Buzzer is used to emit sounds that indicate the state of the robot, such as when it connects to the computer by USB or when it finishes loading the program from the Arduino IDE. It is also capable of emitting very basic melodies._

  

 

   -   _Dot Matrix Module: The robot has a dot matrix module of 8x8 pixels that can be controlled with the ESP32. The LED board can display different facial expressions or emoticons that represent the mood or personality of the robot. It can also display text messages or numbers. (Optionally, you can replace this function with the “Ultrasonic Board”)._ 

  

 

   -   _Ultrasonic board: The robot has an HC-SR04 ultrasonic board that works as a sonar. The “Head” moves, emiting sound waves and measuring the time they take to bounce off nearby objects. In this way, the robot can measure the distance to obstacles and avoid them. The ultrasonic board is mounted on a servomotor that allows it to rotate and explore the environment._  
  

  

   -   _Camera: The robot has an OV2640 camera that can be connected to the ESP32. The camera has a resolution of 2 megapixels and can capture images in color or grayscale. The camera is used to recognize objects, people or colors using artificial vision algorithms. The camera is also mounted on a servomotor that allows it to orient itself._  

  
  

   -   _Line Tracking Module: An infrared sensor used to track lines or paths on the ground. This sensor emits an infrared light that is reflected on clear surfaces and absorbed on dark ones. In this way, the sensor can detect if it is on a black line or a white background. The sensor has a potentiometer that allows adjusting the sensitivity to ambient light. The sensor connects to the microcontroller through a digital pin that sends a high or low signal depending on whether there is a line or not. The sensor is used in mobile robots to follow a predefined route._  

  


   -   _3.7V 18650 Lithium Batteries: The robot, due to its high energy consumption, uses this peculiar type of batteries to supply itself with energy. These batteries are rechargeable and have a capacity of between 1500 and 3500 mAh. The batteries have a nominal voltage of 3.7V and a maximum voltage of 4.2V. The batteries are connected to the robot through a battery holder that has an on/off switch. The batteries can be charged with a special charger that has a protection circuit against overloads and short circuits._  


  

   -   _LEDs: The robot has integrated on its base plate 12 LEDs that it can control with the ESP32 chip. The LEDs can display different lighting effects that give the robot a more attractive and fun appearance. For example, the robot can turn on the LEDs in a wide variety of colors following certain configurations, such as:_  

  
  - _Static light: The robot turns on the LEDs in a single color and keeps them that way until the configuration changes._  

  - _Flashing light: The robot makes the LEDs blink in a single color or in several alternating colors at a certain speed._ 

  - _"Breathing" light: The robot makes the LEDs turn on and off gradually in a single color or in several alternating colors, simulating the rhythm of breathing._  

  - _“Rainbow” light: The robot makes the LEDs show all the colors of the rainbow in all the LEDs as time goes by, creating a very striking multicolor effect._  


_With multiple combinations that can be created, such as the effect of being calm with the "breathing" light with a blue or white color, or “Rainbow” to celebrate some achievement._

  

----------------------------------------------------------------------------------------------------------------------------------------

_The artificial vision algorithms that are used to recognize objects or colors are computer programs that process the images captured by the OV2640 camera and extract relevant information from them. For example, to recognize colors, I use an algorithm that converts color images to grayscale and then applies a red, green or blue color mask depending on the color we want to detect. Then, we calculate the percentage of pixels of the desired color in the image and compare it with a predefined threshold to determine whether or not there is presence of the color. The way to load the code would be to connect a Micro-USB cable to the USB port of the ESP32, start loading the code from the programming environment and wait for the process to finish._

  
_The objective of this robotic solution model is to demonstrate the capabilities of the ESP32 chip and its possible applications in the field of educational robotics. The robot can perform different tasks such as following a line, avoiding obstacles, recognizing colors or expressing emotions._

_Thank You._

## How to prepare the repo based on the template

_Remove this section before the first commit to the repository_

1. Clone this repo by using the `git clone` functionality.
2. Remove `.git` directory
3. [Initialize a new public repository on GitHub](https://github.com/new) by following instructions from "create a new repository on the command line" section (appeared after pressing "Create repository" button).
