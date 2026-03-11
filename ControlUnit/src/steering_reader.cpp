#include <Wire.h>

#define AS5600_ADDR 0x36   // I2C address of AS5600
#define RAW_ANGLE_MSB 0x0C // Raw angle MSB register
#define RAW_ANGLE_LSB 0x0D // Raw angle LSB register

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("AS5600 Angle Reader");
  Serial.println("-------------------");
}

void loop() {
  uint16_t rawAngle = readRawAngle();
  float angleDeg = (rawAngle * 360.0) / 4096.0;

  Serial.print("Raw: ");
  Serial.print(rawAngle);
  Serial.print(" | Angle: ");
  Serial.print(angleDeg, 2);
  Serial.println(" deg");

  delay(50); // smooth update rate
}

uint16_t readRawAngle() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_ANGLE_MSB);
  Wire.endTransmission(false);

  Wire.requestFrom(AS5600_ADDR, 2);

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  return ((msb << 8) | lsb) & 0x0FFF; // 12-bit angle
}