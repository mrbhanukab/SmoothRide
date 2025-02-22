/*
* Formulas:
*! Wrong Need to Update
*?    Left_Motor_Speed = (y + x) * max(abs(y+x), abs(y-x), 1024) / 255
*?    Right_Motor_Speed = (y - x) * max(abs(y+x), abs(y-x), 1024) / 255
*/

#pragma once

inline void motor(JoyStick joyStick)
{
    // const int Left_Motor_Speed = calcMotorSpeed(joyStick.y_axis, joyStick.x_axis, true);
    // const int Right_Motor_Speed = calcMotorSpeed(joyStick.y_axis, joyStick.x_axis, false);
    // setMotorSpeed(leftMotor, Left_Motor_Speed);
    // setMotorSpeed(rightMotor, Right_Motor_Speed);
    Serial.print("X-axis: ");
    Serial.print(joyStick.x_axis);
    Serial.print(" Y-axis: ");
    Serial.println(joyStick.y_axis);

    if (joyStick.y_axis < -800)
    {
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
    } else if (joyStick.y_axis > 800)
    {
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
    } else if (joyStick.x_axis > 800)
    {
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        digitalWrite(left, HIGH);
        digitalWrite(right, LOW);
    }else if (joyStick.x_axis < -800)
    {
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        digitalWrite(left, LOW);
        digitalWrite(right, HIGH);
    }else
    {
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        digitalWrite(left, LOW);
        digitalWrite(right, LOW);
    }
}
