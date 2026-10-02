#include <Arduino.h>

// GPIO connections
const uint8_t BUTTON_PIN = 42;
const uint8_t RED_LED_PIN = 41;
const uint8_t GREEN_LED_PIN = 40;

void setup() {
  // Internal pull-up resistor for the pushbutton
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // LEDs are outputs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Initial state:
  // Button released = Green ON, Red OFF
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void loop() {

  // INPUT_PULLUP means:
  // LOW  = button pressed
  // HIGH = button released
  bool pressed = (digitalRead(BUTTON_PIN) == LOW);

  if (pressed) {
    // Button pressed
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
  else {
    // Button released
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}