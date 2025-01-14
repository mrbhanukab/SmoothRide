#include <Arduino.h>
#include <AFMotor.h>
#include <Wire.h>

#include "ioPins.h"
#include "joyStick.h"
#include "motor.h"
#include "seat.h"
#include "gyro.h"

unsigned long previousMillisJoystick = 0, previousMillisSwitch = 0, previousMillisGyro = 0;

void setup() {
    ioPinsSetup();
   Serial.begin(9600);
   initializeMPU6050();
   calibrateSensors();
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
   if (currentMillis - previousMillisGyro >= 1000) {
         SensorReadings current = getFilteredOrientation();
         Serial.print("X: ");
         Serial.print(current.x);
          Serial.print(" | Y: ");
         Serial.print(current.y);
        Serial.print("  | Z: ");
         Serial.println(current.z);
         previousMillisGyro = currentMillis;
   }

}