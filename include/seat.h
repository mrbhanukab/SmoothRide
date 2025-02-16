//! Note: This is just a simulation of the seat rotation mechanism.

#pragma once

Servo myservo;

bool seatState = false;

inline void seatRotateStart(bool switchState)
{
    if (switchState == true)
    {
        digitalWrite(seat, HIGH);
        seatState = true;
    }
}

inline void seatRotateStop()
{
    digitalWrite(seat, LOW);
    seatState = false;
}

inline void adjustSeatAngle(float pitch)
{
    // Map the pitch angle to the servo's range (0 to 180 degrees)
    int servoPosition = map(pitch, -30, 30, 60, 120);

    // Ensure the servo position stays within its physical range
    servoPosition = constrain(servoPosition, 0, 180);

    // Set the servo position to maintain the seat at 90 degrees
    myservo.write(servoPosition);
}
