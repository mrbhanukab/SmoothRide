#pragma once

// MPU6050 I2C Address
#define MPU6050_ADDRESS 0x68
// Register Addresses
#define GYRO_DATA_START 0x43
#define ACCEL_DATA_START 0x3B
// Scaling Factors
#define GYRO_SENSITIVITY 131.0f
#define ACCEL_SENSITIVITY 16384.0f
#define PI 3.14159265358979323846f

// Struct to Hold Sensor Data
struct SensorReadings
{
  float x, y, z;

  SensorReadings& operator+=(const SensorReadings& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  SensorReadings operator-(const SensorReadings& other) const
  {
    return {x - other.x, y - other.y, z - other.z};
  }
};

// Global Variables for Calibration Errors and Angle Tracking
SensorReadings gyroCalibrationError = {0, 0, 0};
SensorReadings accelCalibrationError = {0, 0, 0};
SensorReadings currentAngle = {0, 0, 0};

// Function to Initialize the MPU6050
void initializeMPU6050()
{
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(0x6B); // Power management register
  Wire.write(0x00); // Wake up MPU6050
  Wire.endTransmission(true);
}

// Function to Read Gyroscope Data
SensorReadings readGyroscopeData()
{
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(GYRO_DATA_START);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 6, true);

  SensorReadings gyroData;
  gyroData.x = (Wire.read() << 8 | Wire.read()) / GYRO_SENSITIVITY;
  gyroData.y = (Wire.read() << 8 | Wire.read()) / GYRO_SENSITIVITY;
  gyroData.z = (Wire.read() << 8 | Wire.read()) / GYRO_SENSITIVITY;
  return gyroData;
}

// Function to Read Accelerometer Data
SensorReadings readAccelerometerData()
{
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(ACCEL_DATA_START);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 6, true);

  SensorReadings accelData;
  accelData.x = (Wire.read() << 8 | Wire.read()) / ACCEL_SENSITIVITY;
  accelData.y = (Wire.read() << 8 | Wire.read()) / ACCEL_SENSITIVITY;
  accelData.z = (Wire.read() << 8 | Wire.read()) / ACCEL_SENSITIVITY;
  return accelData;
}

// Function to Calibrate Sensors
void calibrateSensors()
{
  const int calibrationReadings = 500;
  for (int i = 0; i < calibrationReadings; i++)
  {
    gyroCalibrationError += readGyroscopeData();
    accelCalibrationError += readAccelerometerData();
    delay(3); // Stabilize readings
  }

  gyroCalibrationError.x /= calibrationReadings;
  gyroCalibrationError.y /= calibrationReadings;
  gyroCalibrationError.z /= calibrationReadings;

  accelCalibrationError.x /= calibrationReadings;
  accelCalibrationError.y /= calibrationReadings;
  accelCalibrationError.z /= calibrationReadings;
}

// Function to Calculate Angles from Accelerometer Data
SensorReadings calculateAccelerometerAngles(const SensorReadings& accelData)
{
  SensorReadings angles;
  angles.x = atan2f(accelData.y, sqrtf(accelData.x * accelData.x + accelData.z * accelData.z)) * 180 / PI;
  angles.y = atan2f(-accelData.x, sqrtf(accelData.y * accelData.y + accelData.z * accelData.z)) * 180 / PI;
  angles.z = 0; // Accelerometer does not provide meaningful Z-axis angle
  return angles;
}

// Function to Get Filtered Orientation Data
SensorReadings getFilteredOrientation()
{
  static unsigned long lastUpdateTime = 0;
  unsigned long currentTime = micros();
  float deltaTime = (currentTime - lastUpdateTime) / 1000000.0f; // Convert to seconds
  lastUpdateTime = currentTime;

  // Read Raw Sensor Data
  SensorReadings rawGyroData = readGyroscopeData() - gyroCalibrationError;
  SensorReadings rawAccelData = readAccelerometerData();

  // Compute Accelerometer Angles
  SensorReadings accelAngles = calculateAccelerometerAngles(rawAccelData);

  // Apply Complementary Filter
  currentAngle.x = 0.96f * (currentAngle.x + rawGyroData.x * deltaTime) + 0.04f * accelAngles.x;
  currentAngle.y = 0.96f * (currentAngle.y + rawGyroData.y * deltaTime) + 0.04f * accelAngles.y;
  currentAngle.z += rawGyroData.z * deltaTime;

  return currentAngle;
}
