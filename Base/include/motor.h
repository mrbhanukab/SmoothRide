#pragma once

inline void motor(JoyStick joyStick)
{
    Serial.print("X-axis: ");
    Serial.print(joyStick.x_axis);
    Serial.print(" Y-axis: ");
    Serial.println(joyStick.y_axis);

    if (joyStick.y_axis < -800 || joyStick.y_axis > 800 || joyStick.x_axis > 800 || joyStick.x_axis < -800)
    {
        // Both Motors On
        digitalWrite(leftOn, HIGH);
        digitalWrite(rightOn, HIGH);

        if (joyStick.y_axis < -800)
        {
            // Forward
            digitalWrite(leftForward, HIGH);
            digitalWrite(leftBackward, LOW);
            digitalWrite(rightForward, HIGH);
            digitalWrite(rightBackward, LOW);
        }
        else if (joyStick.y_axis > 800)
        {
            // Backward
            digitalWrite(leftForward, LOW);
            digitalWrite(leftBackward, HIGH);
            digitalWrite(rightForward, LOW);
            digitalWrite(rightBackward, HIGH);
        }

        if (joyStick.x_axis > 800)
        {
            // Right
            digitalWrite(leftForward, HIGH);
            digitalWrite(leftBackward, LOW);
            digitalWrite(rightForward, LOW);
            digitalWrite(rightBackward, HIGH);
        }
        else if (joyStick.x_axis < -800)
        {
            // Left
            digitalWrite(leftForward, LOW);
            digitalWrite(leftBackward, HIGH);
            digitalWrite(rightForward, HIGH);
            digitalWrite(rightBackward, LOW);
        }
    }
    else
    {
        // Stop all motors
        digitalWrite(leftOn, LOW);
        digitalWrite(rightOn, LOW);
        digitalWrite(leftForward, LOW);
        digitalWrite(leftBackward, LOW);
        digitalWrite(rightForward, LOW);
        digitalWrite(rightBackward, LOW);
    }
}
