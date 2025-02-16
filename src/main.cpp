#include <Arduino.h>
#include <AFMotor.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

#include "ioPins.h"
#include "joyStick.h"
#include "motor.h"
#include "seat.h"
#include "gyro.h"

unsigned long previousMillisJoystick = 0, previousMillisSwitch = 0, previousMillisGyro = 0;

void setup() {
Wire.begin();
    ioPinsSetup();
   Serial.begin(9600);
   myservo.attach(10);
   myservo.write(90);
   initializeMPU6050();
   calibrateAccelerometer();
}

void loop() {
   const unsigned long currentMillis = millis();

   //? Taask: Read Joy Stick Values and Control Motors
   if (currentMillis - previousMillisJoystick >= 10) {
      previousMillisJoystick = currentMillis;
      motor(readJoyStick());
   }

   //? Task: Read Joy Stick Switch Value And Rotate Seat 90 Degree
   if (currentMillis - previousMillisSwitch >= 10 && seatState == false && readSwitch()) {
         seatRotateStart(true);
         previousMillisSwitch = currentMillis;
   }

   //? Turn off the seat rotation after 2.5 seconds
   if (currentMillis - previousMillisSwitch >= 2500 && seatState == true)
      seatRotateStop();

    //? Task: Read Gyroscope Values & Control Seat
   if (currentMillis - previousMillisGyro >= 10) {
        adjustSeatAngle(pitch());
         previousMillisGyro = currentMillis;
   }

}