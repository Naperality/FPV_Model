#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial HC12(10, 11); // RX, TX

// ------------- PINS ------------
#define PIN_P 3
#define PIN_R 5
#define PIN_N 6
#define PIN_D 9

#define HORN_BUTTON 7

#define HALL1 A1  // Throttle
#define HALL2 A0  // Brake

#define TURN_LEFT_PIN 13
#define TURN_RIGHT_PIN 12

// -------- AS5600 STEERING SETTINGS --------
#define AS5600_ADDR 0x36
#define RAW_ANGLE_REGISTER 0x0C
const int steeringLeftMax = 800;
const int steeringRightMax = 2800;
int steeringCenter = 0;
const int deadzone = 8;

// Function to read raw angle from AS5600
uint16_t readAS5600Raw() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_ANGLE_REGISTER);
  
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDR, 2);
  uint32_t startWait = millis();
  while (Wire.available() < 2) {
    if (millis() - startWait > 10) return 0; // Timeout to prevent freezing
  }

  uint16_t highByte = Wire.read();
  uint16_t lowByte = Wire.read();
  return (highByte << 8) | lowByte;
  return 0;
}

void setup() {
  Serial.begin(115200);
  HC12.begin(9600);
  Wire.begin(); // Start I2C for AS5600
  Wire.setClock(400000); //reduce lag somehow

  pinMode(PIN_P, INPUT_PULLUP);
  pinMode(PIN_R, INPUT_PULLUP);
  pinMode(PIN_N, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);

  pinMode(HORN_BUTTON, INPUT_PULLUP);

  pinMode(TURN_LEFT_PIN, INPUT_PULLUP);
  pinMode(TURN_RIGHT_PIN, INPUT_PULLUP);

  // -------- STEERING CALIBRATION --------
  delay(1000);
  long sum = 0;
  const int samples = 100;
  for (int i = 0; i < samples; i++) {
    sum += readAS5600Raw();
    delay(5);
  }
  steeringCenter = sum / samples;
}

void loop() {
  char gear = 'X';

  // ---- GEAR ----
  if (digitalRead(PIN_P) == HIGH) gear = 'P';
  else if (digitalRead(PIN_R) == HIGH) gear = 'R';
  else if (digitalRead(PIN_N) == HIGH) gear = 'N';
  else if (digitalRead(PIN_D) == HIGH) gear = 'D';

  // ---- ANALOG ----
  int rawHall1 = analogRead(HALL1);
  int rawHall2 = analogRead(HALL2);

  int throttleVal = map(rawHall1, 177, 707, 0, 100);
  int brakeVal = map(rawHall2, 177, 707, 0, 100);

  throttleVal = constrain(throttleVal, 0, 100);
  brakeVal = constrain(brakeVal, 0, 100);

  // ---- HORN ----
  int horn = (digitalRead(HORN_BUTTON) == LOW) ? 1 : 0;

  // ---- BRAKE ----
  int brakeSignal = (brakeVal > 50) ? 1 : 0;

  // ---- 3. STEERING (AS5600) ----
  uint16_t steeringRaw = readAS5600Raw();
  int steeringMapped;

  if (abs((int)steeringRaw - steeringCenter) <= deadzone) {
    steeringMapped = 0;
  } else if (steeringRaw < steeringCenter) {
    steeringMapped = map(steeringRaw, steeringLeftMax, steeringCenter, -100, 0);
  } else {
    steeringMapped = map(steeringRaw, steeringCenter, steeringRightMax, 0, 100);
  }
  steeringMapped = constrain(steeringMapped, -100, 100);

  // ---- TURN SIGNAL ----
  int turnSignal = 0;
  if (digitalRead(TURN_LEFT_PIN) == LOW) turnSignal = -1;
  else if (digitalRead(TURN_RIGHT_PIN) == LOW) turnSignal = 1;

  // ---- SEND (FIXED FORMAT) ----
  HC12.print(gear);
  HC12.print(",");
  HC12.print(throttleVal);
  HC12.print(",");
  HC12.print(horn);
  HC12.print(",");
  HC12.print(brakeSignal);
  HC12.print(",");
  HC12.println(turnSignal); // ONLY ONE println

  // ---- DEBUG ----
  Serial.print(gear);
  Serial.print(",");
  Serial.print(throttleVal);
  Serial.print(",");
  Serial.print(brakeVal);
  Serial.print(",");
  Serial.print(steeringMapped);
  Serial.print(",");
  Serial.println(turnSignal);

  delay(80);
}