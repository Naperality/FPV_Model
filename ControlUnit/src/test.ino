// Define sensor pins
const int sensor1 = 3;
const int sensor2 = 5;
const int sensor3 = 6;
const int sensor4 = 9;

void setup() {
  // Start Serial communication
  Serial.begin(9600);

  // Set sensor pins as input
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);
  pinMode(sensor4, INPUT_PULLUP);
}

void loop() {
  // Read sensor states
  int state1 = digitalRead(sensor1);
  int state2 = digitalRead(sensor2);
  int state3 = digitalRead(sensor3);
  int state4 = digitalRead(sensor4);

  // Print results
  Serial.print("Sensor 1: ");
  Serial.print(state1);
  Serial.print(" | Sensor 2: ");
  Serial.print(state2);
  Serial.print(" | Sensor 3: ");
  Serial.print(state3);
  Serial.print(" | Sensor 4: ");
  Serial.println(state4);

  delay(500);  // Small delay for readability
}