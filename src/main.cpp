#include <Arduino.h>

#include "ioPins.h"
#include "joyStick.h"
#include "motor.h"
#include "seat.h"

unsigned long previousMillisJoystick = 0;
unsigned long previousMillisSwitch = 0;

void setup() {
   pinMode(x_axis, INPUT);
   pinMode(y_axis, INPUT);
   pinMode(seat, OUTPUT);
   pinMode(SWITCH, INPUT_PULLUP);
   Serial.begin(9600);
}

void loop() {
   const unsigned long currentMillis = millis();

   //? Taask: Read Joy Stick Values and Control Motors
   if (currentMillis - previousMillisJoystick >= 10) {
      previousMillisJoystick = currentMillis;
      motor(readJoyStick());
   }

   //? Task: Read Joy Stick Switch Value And Rotate Seat 90 Degree
   if (currentMillis - previousMillisSwitch >= 10 && seatState == false) {
      if (readSwitch()) {
         seatRotateStart(true);
         previousMillisSwitch = currentMillis;
      }
   }

   //? Turn off the seat rotation after 2.5 seconds
   if (currentMillis - previousMillisSwitch >= 2500 && seatState == true)
      seatRotateStop();

}