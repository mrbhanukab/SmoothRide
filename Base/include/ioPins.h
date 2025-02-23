#pragma once

//! Joy Stick VRX to `y_axis` and VRY to `x_axis`
#define x_axis A15
#define y_axis A14

#define leftForward 26
#define leftBackward 28
#define leftOn 30

#define rightForward 27
#define rightBackward 29
#define rightOn 31

#define SWITCH 52
#define seat 53

inline void ioPinsSetup()
{
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);

  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(leftOn, OUTPUT);

  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(rightOn, OUTPUT);

  pinMode(seat, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
}
