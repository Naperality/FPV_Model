#include <Servo.h>

Servo esc;

int signalPin = 9;
int neutral = 1500;

void setup() {
  Serial.begin(115200);

  esc.attach(signalPin, 1000, 2000);

  Serial.println("ESC Initializing...");
  
  // Send neutral signal for arming
  esc.writeMicroseconds(neutral);
  delay(3000); // allow ESC to arm
}

void loop() {
  // Example: slow forward
  esc.writeMicroseconds(1600);
  delay(2000);

  // Back to neutral
  esc.writeMicroseconds(1500);
  delay(2000);

  // Reverse
  esc.writeMicroseconds(1400);
  delay(2000);
}