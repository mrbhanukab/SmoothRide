#pragma once

//! Joy Stick VRX to `y_axis` and VRY to `x_axis`
#define x_axis A15
#define y_axis A14

#define forward 30
#define backward 31
#define left 34
#define right 35

#define SWITCH 52
#define seat 53

inline void ioPinsSetup()
{
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(seat, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
}
