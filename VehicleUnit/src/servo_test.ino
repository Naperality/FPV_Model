#include <Servo.h>

Servo myServo;

int potPin = A0;
int servoPin = 9;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(potPin); // 0–1023

  // Map to servo angle
  int angle = map(potValue, 0, 1023, 0, 180);

  myServo.write(angle);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Angle: ");
  Serial.println(angle);

  delay(15);
}