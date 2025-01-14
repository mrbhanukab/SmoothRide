/*
* Formulas:
*! Wrong Need to Update
*?    Left_Motor_Speed = (y + x) * max(abs(y+x), abs(y-x), 1024) / 255
*?    Right_Motor_Speed = (y - x) * max(abs(y+x), abs(y-x), 1024) / 255
*/

#pragma once

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);

inline int calcMotorSpeed(int Y, int X, bool left)
{
    const float x_normalized = (float)X / 1024;
    const float y_normalized = (float)Y / 1024;
    const float scale = max(max(fabs(y_normalized + x_normalized), fabs(y_normalized - x_normalized)), 1.0f);

    if (left)
        return (int)(255 * ((y_normalized + x_normalized) / scale));
    else
        return (int)(255 * ((y_normalized - x_normalized) / scale));
}

inline void setMotorSpeed(AF_DCMotor& motor, int speed)
{
    motor.setSpeed(abs(speed));
    if (speed < 0)
    {
        motor.run(BACKWARD);
    }
    else if (speed > 0)
    {
        motor.run(FORWARD);
    }
    else
    {
        motor.run(RELEASE);
    }
}

inline void motor(JoyStick joyStick)
{
    const int Left_Motor_Speed = calcMotorSpeed(joyStick.y_axis, joyStick.x_axis, true);
    const int Right_Motor_Speed = calcMotorSpeed(joyStick.y_axis, joyStick.x_axis, false);
    setMotorSpeed(leftMotor, Left_Motor_Speed);
    setMotorSpeed(rightMotor, Right_Motor_Speed);
}
