#include <Arduino.h>
#include "gyro.h"
#include "seat.h"

void setup() {
    initializeMPU6050();
    calibrateAccelerometer();
    servo_int();
}

void loop() {
    adjustSeatAngle(getYAngle());
    delay(10);
}