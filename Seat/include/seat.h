//! Note: This is just a simulation of the seat rotation mechanism.
#pragma once

#include <Servo.h>
Servo servo;

inline void servo_int()
{
    servo.attach(3);
    servo.write(90);
}

inline void adjustSeatAngle(float yAngle)
{
    // Map the yAngle angle to the servo's range (0 to 180 degrees)
    int servoPosition = map(yAngle, -90, 90, 0, 180);
    // Serial.print("Pitch: ");
    // Serial.print(-yAngle);
    // Serial.print(" | Servo Position: ");
    // Serial.println(servoPosition);

    // Ensure the servo position stays within its physical range
    servoPosition = constrain(servoPosition, 0, 180);

    // Set the servo position to maintain the seat at 90 degrees
    servo.write(servoPosition);
}
