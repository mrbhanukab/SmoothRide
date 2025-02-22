#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Variables to store accelerometer calibration offsets
float accelOffsetX = 0.0;
float accelOffsetY = 0.0;
float accelOffsetZ = 0.0;

inline void initializeMPU6050()
{
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      delay(10);
  }
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +-250 deg/s
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);

  // set filter bandwidth to 44 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

  delay(100);
}

inline void calibrateAccelerometer()
{
  float sumX = 0.0;
  float sumY = 0.0;
  float sumZ = 0.0;
  const int numReadings = 100;

  for (int i = 0; i < numReadings; i++)
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sumX += a.acceleration.x;
    sumY += a.acceleration.y;
    sumZ += a.acceleration.z;
    delay(10);
  }

  accelOffsetX = sumX / numReadings;
  accelOffsetY = sumY / numReadings;
  accelOffsetZ = sumZ / numReadings;

  // Adjust Z offset to account for gravity
  accelOffsetZ -= 9.81; // Subtract gravitational acceleration (m/s^2)
}

inline int getYAngle()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Apply calibration offset to Y
  a.acceleration.y -= accelOffsetY;

  // Make sure that the absolute value doesn't exceed 9.81 (g) to avoid asin domain errors.
  float normalizedY = constrain(a.acceleration.y, -9.81, 9.81) / 9.81;
  float angleY = asin(normalizedY) * 180.0 / PI;
  return static_cast<int>(angleY);
}
