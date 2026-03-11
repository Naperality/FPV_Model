// Pins
const int gasPin = A0;
const int brakePin = A1;

// Calibration for Gas
int gasMin = 150; 
int gasMax = 850;

// Calibration for Brake
int brakeMin = 120; 
int brakeMax = 900;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // --- Process Gas Pedal ---
  int gasRaw = analogRead(gasPin);
  int gasClean = constrain(gasRaw, gasMin, gasMax);
  int gasPercent = map(gasClean, gasMin, gasMax, 0, 100);

  // --- Process Brake Pedal ---
  int brakeRaw = analogRead(brakePin);
  int brakeClean = constrain(brakeRaw, brakeMin, brakeMax);
  int brakePercent = map(brakeClean, brakeMin, brakeMax, 0, 100);

  // --- Display Results ---
  Serial.print("GAS: ");
  Serial.print(gasPercent);
  Serial.print("% | BRAKE: ");
  Serial.print(brakePercent);
  Serial.println("%");

  delay(30); // Faster refresh for two pedals
}