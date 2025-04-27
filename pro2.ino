#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// Motor pins
#define M1_L    3    // Left IN1 (PWM)
#define M2_L    6    // Left IN2 (PWM)
#define ENC_L   5    // Left encoder (optional, not needed here)
#define M1_R    9    // Right IN1 (PWM)
#define ENC_R   10   // Right encoder (optional, not needed here)
#define M2_R    11   // Right IN2 (PWM)

// Car parameters
const float WHEEL_BASE = 0.15;   // Distance between wheels (meters)
const float WHEEL_DIAMETER = 0.03; // 3cm wheel diameter
const float MAX_RPM = 255.0;     // Maximum motor RPM

// Circle motion parameters
const float CIRCLE_RADIUS = 0.60;  // meters (adjust as needed)
const int BASE_SPEED = 225;        // Center speed (PWM 0-255)
const int MIN_WHEEL_SPEED = 200;    // Minimum PWM to keep wheels moving
const float KP = 10.0;             // Yaw-rate proportional gain
const bool STOP_AFTER_CIRCLE = true; // Set to false for continuous circling

Adafruit_MPU6050 mpu;

// Motion variables
float yaw = 0;
float yawAccum = 0;
float prevYaw = 0;
unsigned long prevTime = 0;

// Motor control functions
void setLeftMotor(int pwm) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(M1_L, pwm);
  digitalWrite(M2_L, LOW);
}

void setRightMotor(int pwm) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(M1_R, pwm);
  digitalWrite(M2_R, LOW);
}

// Setup
void setup() {
  Serial.begin(9600);
  
  // Motor outputs
  pinMode(M1_L, OUTPUT); pinMode(M2_L, OUTPUT);
  pinMode(M1_R, OUTPUT); pinMode(M2_R, OUTPUT);

  // MPU-6050 init
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("MPU-6050 not found!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  // Zero yaw
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  prevYaw = 0;
  yaw = 0;
  prevTime = micros();
  
  Serial.println("Starting circular movement with both wheels moving...");
}

// Main loop
void loop() {
  unsigned long now = micros();
  float dt = (now - prevTime) / 1e6;
  prevTime = now;

  // Read IMU data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyroZ = g.gyro.z;  // This is already in rad/s

  // Integrate yaw (in degrees)
  yaw += gyroZ * RAD_TO_DEG * dt;

  // Keep yaw between -180 to 180 degrees
  if (yaw > 180.0) yaw -= 360.0;
  if (yaw < -180.0) yaw += 360.0;

  // Calculate yaw change
  float dyaw = yaw - prevYaw;
  if (dyaw >  180.0) dyaw -= 360.0;
  if (dyaw < -180.0) dyaw += 360.0;

  yawAccum += fabs(dyaw);
  prevYaw = yaw;

  // Check if completed one circle
  if (STOP_AFTER_CIRCLE && yawAccum >= 360.0) {
    setLeftMotor(0);
    setRightMotor(0);
    Serial.println("Circle complete!");
    while (1);  // Halt forever
  }

  // Calculate wheel speeds for circle
  // For a circle: inner wheel travels shorter distance than outer wheel
  float innerRadius = CIRCLE_RADIUS - (WHEEL_BASE / 2);
  float outerRadius = CIRCLE_RADIUS + (WHEEL_BASE / 2);
  float ratio = innerRadius / outerRadius;
  
  // For counter-clockwise circle (adjust as needed):
  // Ensure inner wheel always gets at least MIN_WHEEL_SPEED
  float leftSpeed, rightSpeed;
  
  if (ratio * BASE_SPEED < MIN_WHEEL_SPEED) {
    // If calculated inner wheel speed would be too low, set it to minimum
    // and scale the outer wheel proportionally higher
    leftSpeed = MIN_WHEEL_SPEED;  // Inner wheel (left for counter-clockwise)
    rightSpeed = MIN_WHEEL_SPEED / ratio;  // Outer wheel scaled up
    
    // Make sure outer wheel doesn't exceed maximum
    if (rightSpeed > 255) {
      rightSpeed = 255;
      // We can't maintain the exact ratio, but at least both wheels are moving
    }
  } else {
    // Normal case - both wheels get enough speed
    rightSpeed = BASE_SPEED;  // Outer wheel
    leftSpeed = BASE_SPEED * ratio;  // Inner wheel
  }
  
  // Calculate actual linear speed (m/s) from PWM value
  // Max linear speed = (π × diameter × RPM) / 60
  float maxLinearSpeed = PI * WHEEL_DIAMETER * MAX_RPM / 60.0;
  float linearSpeed = ((leftSpeed + rightSpeed) / 2) / 255.0 * maxLinearSpeed;
  
  // Expected yaw rate for given circle radius
  float desiredYawRate = (linearSpeed / CIRCLE_RADIUS) * RAD_TO_DEG;  // deg/sec

  // Actual yaw rate from gyro (already in deg/sec)
  float actualYawRate = gyroZ * RAD_TO_DEG;
  
  // Apply PID correction
  float yawError = desiredYawRate - actualYawRate;
  float correction = KP * yawError;

  // Apply correction to motor speeds
  int pwmL = constrain(leftSpeed - correction, MIN_WHEEL_SPEED, 255);
  int pwmR = constrain(rightSpeed + correction, MIN_WHEEL_SPEED, 255);

  // Drive motors
  setLeftMotor(pwmL);
  setRightMotor(pwmR);

  // Debug
  Serial.print("yawAccum: "); Serial.print(yawAccum);
  Serial.print(", yaw: "); Serial.print(yaw);
  Serial.print(", ratio: "); Serial.print(ratio);
  Serial.print(", pwmL: "); Serial.print(pwmL);
  Serial.print(", pwmR: "); Serial.println(pwmR);

  delay(10);  // ~100Hz loop
}
