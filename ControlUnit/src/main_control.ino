#include <Wire.h>
#include <SPI.h>
#include <RF24.h>

// -------- DIGITAL SENSORS (KY-024) --------
const int sensor1 = 3;
const int sensor2 = 5;
const int sensor3 = 6;
const int sensor4 = 9;

// -------- FAST MODE SWITCH --------
const int fastSwitch = 4;  // NEW

// -------- ANALOG PEDAL SENSORS --------
const int brakes = A0;
const int accelerator = A1;

// -------- AS5600 --------
#define AS5600_ADDR 0x36
#define RAW_ANGLE_REGISTER 0x0C

// -------- STEERING LIMITS --------
const int steeringLeftMax = 800;
const int steeringRightMax = 2800;
int steeringCenter = 0;
const int deadzone = 5;

// -------- NRF24 SETUP --------
#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

// -------- STRUCT --------
struct Telemetry {
  uint8_t s1, s2, s3, s4;
  uint16_t brake;
  uint16_t accel;
  int16_t steering;
  bool fastMode;   // NEW
} telemetry;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);
  pinMode(sensor4, INPUT_PULLUP);

  pinMode(fastSwitch, INPUT_PULLUP); // NEW

  // -------- AUTO CENTER CALIBRATION --------
  Serial.println("Calibrating steering center...");
  delay(1000);

  long sum = 0;
  const int samples = 200;
  for (int i = 0; i < samples; i++) {
    sum += readAS5600Raw();
    delay(5);
  }
  steeringCenter = sum / samples;

  Serial.print("Center calibrated at: ");
  Serial.println(steeringCenter);

  // -------- NRF24 INIT --------
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

uint16_t readAS5600Raw() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_ANGLE_REGISTER);
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDR, 2);
  if (Wire.available() == 2) {
    uint16_t highByte = Wire.read();
    uint16_t lowByte = Wire.read();
    return (highByte << 8) | lowByte;
  }
  return 0;
}

void loop() {
  // ----- Digital sensors -----
  telemetry.s1 = digitalRead(sensor1);
  telemetry.s2 = digitalRead(sensor2);
  telemetry.s3 = digitalRead(sensor3);
  telemetry.s4 = digitalRead(sensor4);

  // ----- FAST MODE SWITCH -----
  telemetry.fastMode = (digitalRead(fastSwitch) == LOW);

  // ----- Pedals -----
  telemetry.brake = analogRead(brakes);
  telemetry.accel = analogRead(accelerator);

  // ----- Steering -----
  uint16_t steeringRaw = readAS5600Raw();
  int steeringMapped;

  if (abs(steeringRaw - steeringCenter) <= deadzone) {
    steeringMapped = 0;
  } else if (steeringRaw < steeringCenter) {
    steeringMapped = map(steeringRaw, steeringLeftMax, steeringCenter, -100, 0);
  } else {
    steeringMapped = map(steeringRaw, steeringCenter, steeringRightMax, 0, 100);
  }

  steeringMapped = constrain(steeringMapped, -100, 100);
  telemetry.steering = steeringMapped;

  // ----- Send -----
  bool ok = radio.write(&telemetry, sizeof(telemetry));
  if (!ok) Serial.println("NRF24 send failed!");

  // ----- Debug -----
  Serial.print("FAST: "); Serial.print(telemetry.fastMode);
  Serial.print(" | Steering: "); Serial.println(telemetry.steering);

  delay(10);
}