#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// -------- NRF24 --------
RF24 radio(7, 8);
const byte address[6] = "00001";

// -------- SERVOS --------
Servo esc;
Servo steering;

const int escPin = 6;
const int steerPin = 5;

// -------- STRUCT --------
struct Telemetry {
  uint8_t s1, s2, s3, s4;
  uint16_t brake;
  uint16_t accel;
  int16_t steering;
  bool fastMode;
};

Telemetry data;

// -------- PEDAL CALIBRATION --------
const int pedalMin = 170;
const int pedalMax = 700;
const int deadzone = 20;

// -------- ESC VALUES --------
int ESC_FORWARD_MAX = 1600;
int ESC_REVERSE_MAX = 1400;
const int ESC_NEUTRAL = 1500;

// -------- PHYSICS CONSTANTS (TUNE THESE) --------
float virtualSpeed = 1500.0;   // The "Momentum" of the car
float rollingResistance = 0.1; // How much speed is lost to air/friction (Neutral)
float engineBraking = 0.4;    // Extra drag when in gear but off the gas
float brakingForce = 3.5;     // Strength of the brake pedal
float accelerationRate = 2.5; // How fast the engine pushes the car

// -------- STATE --------
enum Gear { PARK, REVERSE, NEUTRAL, DRIVE };
Gear currentGear = PARK;
unsigned long lastReceiveTime = 0;

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  esc.attach(escPin);
  steering.attach(steerPin);

  // Calibration sequence for ESC
  esc.writeMicroseconds(ESC_NEUTRAL);
  steering.write(121); 
  delay(3000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("VEHICLE READY - PHYSICS ENABLED");
}

// -------- GEAR SELECT --------
Gear getGear() {
  if (data.s1 == HIGH) return PARK;
  if (data.s2 == HIGH) return REVERSE;
  if (data.s3 == HIGH) return NEUTRAL;
  if (data.s4 == HIGH) return DRIVE;
  return NEUTRAL;
}

// -------- LOOP --------
void loop() {

  if (radio.available()) {
    radio.read(&data, sizeof(data));
    lastReceiveTime = millis();

    currentGear = getGear();

    // Update Speed Limits
    if (data.fastMode) {
      ESC_FORWARD_MAX = 1850;
      ESC_REVERSE_MAX = 1150;
    } else {
      ESC_FORWARD_MAX = 1650;
      ESC_REVERSE_MAX = 1350;
    }

    // -------- STEERING (Direct Control) --------
    int angle = map(data.steering, -100, 100, 60, 170);
    steering.write(angle);

    // -------- PEDAL PROCESSING --------
    int accelVal = constrain(data.accel, pedalMin, pedalMax);
    int brakeVal = constrain(data.brake, pedalMin, pedalMax);

    // Apply deadzone
    if (accelVal < pedalMin + deadzone) accelVal = pedalMin;
    if (brakeVal < pedalMin + deadzone) brakeVal = pedalMin;

    float accelNorm = (float)(accelVal - pedalMin) / (pedalMax - pedalMin);
    float brakeNorm = (float)(brakeVal - pedalMin) / (pedalMax - pedalMin);

    // -------- PHYSICS ENGINE --------
    float appliedForce = 0;

    switch (currentGear) {
      
      case DRIVE:
        appliedForce = accelNorm * accelerationRate;
        // Apply engine braking if no throttle is applied
        if (accelNorm < 0.01 && virtualSpeed > ESC_NEUTRAL) {
          virtualSpeed -= engineBraking;
        }
        break;

      case REVERSE:
        appliedForce = -accelNorm * (accelerationRate * 0.85); // Reverse is usually slower
        // Apply engine braking in reverse
        if (accelNorm < 0.01 && virtualSpeed < ESC_NEUTRAL) {
          virtualSpeed += engineBraking;
        }
        break;

      case NEUTRAL:
        appliedForce = 0; // No engine power
        break;

      case PARK:
        appliedForce = 0;
        // Park acts as a strong permanent brake
        if (virtualSpeed > ESC_NEUTRAL) virtualSpeed -= 5.0;
        else if (virtualSpeed < ESC_NEUTRAL) virtualSpeed += 5.0;
        break;
    }

    // Update Virtual Speed with Engine Force
    virtualSpeed += appliedForce;

    // Apply Brake Pedal (Affects whatever speed we currently have)
    if (brakeNorm > 0.05) {
      float totalBrake = brakeNorm * brakingForce;
      if (virtualSpeed > ESC_NEUTRAL) virtualSpeed -= totalBrake;
      else if (virtualSpeed < ESC_NEUTRAL) virtualSpeed += totalBrake;
    }

    // Natural Rolling Resistance (Always happens)
    if (virtualSpeed > ESC_NEUTRAL) virtualSpeed -= rollingResistance;
    else if (virtualSpeed < ESC_NEUTRAL) virtualSpeed += rollingResistance;

    // Zero-out jitter (Stop the car from creeping at 1500.5 etc)
    if (abs(virtualSpeed - ESC_NEUTRAL) < 1.0) virtualSpeed = ESC_NEUTRAL;

    // Final Constraints
    virtualSpeed = constrain(virtualSpeed, ESC_REVERSE_MAX, ESC_FORWARD_MAX);

    // Write to ESC
    esc.writeMicroseconds((int)virtualSpeed);

    // -------- DEBUG --------
    static unsigned long lastLog = 0;
    if (millis() - lastLog > 100) {
      Serial.print("G: "); Serial.print(currentGear);
      Serial.print(" | SPD: "); Serial.println(virtualSpeed);
      lastLog = millis();
    }
  }

  // -------- FAILSAFE --------
  if (millis() - lastReceiveTime > 500) {
    virtualSpeed = ESC_NEUTRAL;
    esc.writeMicroseconds(ESC_NEUTRAL);
    steering.write(121);
  }
}