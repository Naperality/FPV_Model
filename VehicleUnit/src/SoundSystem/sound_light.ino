#      include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans24pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define RED_LED 2
#define YELLOW_LED 6
#define BUZZER 12
#define F_LED1 4
#define F_LED2 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char currentGear = 'P';
int throttle = 0;
bool horn = false;
bool brake = false;
int turnSignal = 0; 

unsigned long lastBeep = 0;
bool beepState = false;
unsigned long lastBlink = 0;
bool blinkState = false;

void setup() {
  Serial.begin(9600); // Using Hardware Serial

  pinMode(F_LED1, OUTPUT);
  pinMode(F_LED2, OUTPUT);
  digitalWrite(F_LED1, HIGH);
  digitalWrite(F_LED2, HIGH);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(110);
  updateDisplay();
}

void loop() {
  // Reset outputs every loop
  digitalWrite(F_LED1, HIGH);
  digitalWrite(F_LED2, HIGH);
  // ---- 1. DATA RECEIVE & STRING PARSING ----
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    if (line.length() > 5) { 
      // Count commas to find exactly where Horn, Brake, and Turn are
      int c1 = line.indexOf(',');
      int c2 = line.indexOf(',', c1 + 1);
      int c3 = line.indexOf(',', c2 + 1);
      int c4 = line.indexOf(',', c3 + 1);

      if (c1 > 0 && c2 > c1 && c3 > c2 && c4 > c3) {
        char gear = toupper(line.charAt(0));
        throttle = line.substring(c1 + 1, c2).toInt();
        horn = (line.substring(c2 + 1, c3).toInt() == 1);
        brake = (line.substring(c3 + 1, c4).toInt() == 1);
        turnSignal = line.substring(c4 + 1).toInt();

        if (gear != currentGear && (gear == 'P' || gear == 'R' || gear == 'N' || gear == 'D')) {
          currentGear = gear;
          updateDisplay();
        }
      }else {
        // 🚑 FAIL SAFE RESET
        horn = false;
        brake = false;
        turnSignal = 0;
      }
    }
    while(Serial.available()) Serial.read(); 
  }

  // ---- 2. PRIORITY LOGIC (Restoring your old setup) ----

  if (horn) {
    // 📢 HORN ALWAYS WINS
    // Rapid flicker for Front LEDs during horn
    if ((millis() / 100) % 2 == 0) {
    digitalWrite(F_LED1, LOW); digitalWrite(F_LED2, LOW);
    } else {
    digitalWrite(F_LED1, HIGH); digitalWrite(F_LED2, HIGH);
    }
    tone(BUZZER, 440);
  } 
  else if (brake) {
    // 🟥 BRAKE (Solid lights, no sound)
    noTone(BUZZER);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
  }
  else if (currentGear == 'R') {
    // 🔁 REVERSE (Your old pulsed alarm logic)
    handleReverseAlarm();
  }
  else if (turnSignal != 0) {
    // 🟡 TURN SIGNALS (Only if not in Reverse or Braking)
    noTone(BUZZER);
    if (millis() - lastBlink > 400) {
      lastBlink = millis();
      blinkState = !blinkState;
    }
    
    if (turnSignal == -1) { // Left
      digitalWrite(YELLOW_LED, blinkState);
      digitalWrite(RED_LED, LOW);
    } else if (turnSignal == 1) { // Right
      digitalWrite(RED_LED, blinkState);
      digitalWrite(YELLOW_LED, LOW);
    }
  }
  else {
    // ⚪ IDLE (PRND with no signals) - LEDs MUST BE OFF
    noTone(BUZZER);
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    beepState = false; 
    blinkState = false;
  }
}

void handleReverseAlarm() {
  unsigned long interval = 600; // realistic constant beep
  interval = 600 - (throttle * 2); // subtle change only
  interval = constrain(interval, 400, 700);

  if (millis() - lastBeep >= interval) {
    lastBeep = millis();
    beepState = !beepState;

    if (beepState) {
      tone(BUZZER, 800); 
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
    } else {
      noTone(BUZZER);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
    }
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setFont(&FreeSans24pt7b);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(48, 38); 
  display.print(currentGear);
  display.display(); 
}