/*
 * Note about Return Values by readJoyStick():
 * Y-Axis
 *    1024: UP
 *       0: No Move
 *   -1024: DOWN
 *
 * X-Axis
 *   1024: RIGHT
 *      0: No Move
 *  -1024: LEFT
 *
 * Note about joystick readings:
 *       Y-Axis: 256(No Move), 1023 (Up), 0 (Down)
 *      X-Axis: 502(No Move), 1023 (Right), 0 (Left)
 */

#pragma once

struct JoyStick
{
    int x_axis;
    int y_axis;
};

inline JoyStick readJoyStick()
{
    JoyStick joyStick{};
    constexpr int zero_move_limits[2] = {256, 502};
    const int input[2] = {analogRead(y_axis), analogRead(x_axis)};

    for (int axis = 0; axis < 2; axis++)
    {
        int temp_var;

        // ? 0-(zero_move_limits[axis]-10): Down or Left
        if (input[axis] >= 0 && input[axis] <= zero_move_limits[axis] - 10)
            temp_var = map(
                input[axis], 0, zero_move_limits[axis] - 10, -1024, 0);

            // ? (zero_move_limits[axis]-10)-(zero_move_limits[axis]+10): No Move
        else if (input[axis] > zero_move_limits[axis] - 10 && input[axis] < zero_move_limits[axis] + 10) temp_var = 0;

            // ? (zero_move_limits[axis]+10)-1024: Up or Right
        else if (input[axis] >= zero_move_limits[axis] + 10 && input[axis] <= 1024)
            temp_var = map(
                input[axis], zero_move_limits[axis] + 10, 1023, 0, 1024);

        if (axis == 0) joyStick.y_axis = temp_var;
        else joyStick.x_axis = temp_var;
    }
    return joyStick;
}

inline bool readSwitch()
{
    return digitalRead(SWITCH);
}
