#include <Arduino.h>
#include "ioPins.h"
#include "joyStick.h"
#include "motor.h"

unsigned long previousMillisJoystick = 0;
unsigned long previousMillisSwitch = 0;

void setup()
{
    pinMode(x_axis, INPUT);
    pinMode(y_axis, INPUT);
    pinMode(SWITCH, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
        motor(readJoyStick());
//    const unsigned long currentMillis = millis();
//
//    // Task 1: Read joystick state
//    if (currentMillis - previousMillisJoystick >= 10)
//    {
//        previousMillisJoystick = currentMillis;
//        readJoystick();
//        motor();
//
//        Serial.print((current_state[0].y[0] == -1) ? "DOWN" : (current_state[0].y[0] == 0) ? "NO MOVE" : "UP");
//        Serial.print(": ");
//        Serial.print(current_state[0].y[1]);
//        Serial.print("% | ");
//        Serial.print((current_state[0].x[0] == -1) ? "LEFT" : (current_state[0].x[0] == 0) ? "NO MOVE" : "RIGHT");
//        Serial.print(": ");
//        Serial.print(current_state[0].x[1]);
//        Serial.println("%");
//    }
//
//    // Task 2: Read switch state
//    if (currentMillis - previousMillisSwitch >= 50)
//    {
//        previousMillisSwitch = currentMillis;
//        readSwitch();
//        if (switchState)
//        {
//            const long switchActivatedTime = static_cast<long>(millis());
//            while (static_cast<long>(millis()) - switchActivatedTime < 150)
//            {
//                Serial.println("Switch Activated");
//            }
//        }
//
//        // Add other non-blocking tasks here
//    }
//
////    leftMotor.run(FORWARD);
////    leftMotor.setSpeed(255);
////    delay(2000);
////    leftMotor.run(RELEASE);
////    leftMotor.run(BACKWARD);
////    leftMotor.setSpeed(255);
////    delay(2000);
}
