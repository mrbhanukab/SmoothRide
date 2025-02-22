#include <Arduino.h>
#include "ioPins.h"
#include "seat.h"
#include "joyStick.h"
#include "motor.h"

unsigned long previousMillisJoystick = 0, previousMillisSwitch = 0;

void setup() {
  Serial.begin(9600);
    ioPinsSetup();
}

void loop() {
    const unsigned long currentMillis = millis();

       if (currentMillis - previousMillisJoystick >= 100) {
          previousMillisJoystick = currentMillis;
          JoyStick joyStick = readJoyStick();
		  motor(joyStick);
       }

       if (currentMillis - previousMillisSwitch >= 100 && seatState == false && readSwitch()) {
             seatRotateStart(true);
             previousMillisSwitch = currentMillis;
       }

       if (currentMillis - previousMillisSwitch >= 2500 && seatState == true)
          seatRotateStop();

}

