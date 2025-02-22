//! Note: This is just a simulation of the seat rotation mechanism.

#pragma once

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