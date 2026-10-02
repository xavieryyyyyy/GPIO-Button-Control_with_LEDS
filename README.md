# Paraguya_LabAct3_GPIO_and_Button_Control

> Laboratory Activity 3 — GPIO and button control with opposite-state LEDs on an ESP32-S3 board.

<br>

<div align="center">

<video src="https://github.com/xavieryyyyyy/GPIO-Button-Control_with_LEDS/raw/main/media/demo.mp4" controls width="720">
  Your browser does not support the video tag.
</video>

*Pressing and releasing the button toggles the red and green LEDs into opposite states.*

</div>

<br>

## What this does

A pushbutton on GPIO 42 controls two LEDs wired to GPIO 41 (red) and GPIO 40 (green). When the button is released, the green LED stays on and the red stays off. Press the button and they swap: red on, green off. The two LEDs always show opposite states.

The board uses `INPUT_PULLUP`, so the pin reads HIGH when released and LOW when pressed. No external pull-up resistor is needed, and the input stays stable without floating.

## Circuit

<div align="center">

<img src="media/circuit.jpg" alt="Breadboard circuit with ESP32-S3, pushbutton, red LED, and green LED" width="520">

</div>

### GPIO connections

| Component    | GPIO pin | Direction |
|:-------------|:--------:|:---------:|
| Pushbutton   | 42       | Input (pull-up) |
| Red LED      | 41       | Output    |
| Green LED    | 40       | Output    |

### Wiring notes

- Each LED connects through a current-limiting resistor to its GPIO pin, with the cathode to GND.
- One side of the pushbutton connects to GPIO 42, the other to GND.
- The internal pull-up resistor on GPIO 42 holds the line HIGH when the button is open.

## Source code

The full sketch is in [`Paraguya_LabAct3_GPIO_and_Button_Control.ino`](Paraguya_LabAct3_GPIO_and_Button_Control.ino). Here is the complete listing:

```cpp
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
```

## How HIGH and LOW work with INPUT_PULLUP

With `INPUT_PULLUP` enabled, the ESP32-S3 connects an internal resistor between the GPIO pin and 3.3 V. That keeps the pin at HIGH when nothing pulls it down.

| Button state | GPIO 42 reads | Why |
|:-------------|:-------------:|:----|
| Released     | HIGH          | The internal pull-up resistor holds the line at 3.3 V. |
| Pressed      | LOW           | The button shorts GPIO 42 to GND, overriding the pull-up. |

Because the pull-up is always active, the pin never floats. The input does not change randomly when the button is released.

## Pressed and released observation table

| Button state | GPIO 42 | Red LED (GPIO 41) | Green LED (GPIO 40) |
|:-------------|:-------:|:------------------:|:-------------------:|
| Released     | HIGH    | OFF                | ON                  |
| Pressed      | LOW     | ON                 | OFF                 |

After a board reset, the `setup()` function sets the red LED LOW and the green LED HIGH, matching the "released" row above. The initial outputs are predictable every time.

## Procedure followed

1. Drew and labeled the GPIO connections on paper before powering the board.
2. Wired the pushbutton to GPIO 42 and the two LEDs to GPIO 41 and GPIO 40 on the breadboard.
3. Uploaded the sketch and confirmed that releasing the button turns the green LED on and the red LED off.
4. Pressed the button and confirmed the LEDs swap states.
5. Reset the board and verified the initial outputs match the expected "released" state.
6. Observed that the input stays stable when the button is released (no random toggling).

## Requirements

- ESP32-S3 development board
- 1 pushbutton
- 1 red LED, 1 green LED
- 2 current-limiting resistors (220 ohm recommended)
- Breadboard and jumper wires
- Arduino IDE with ESP32 board support installed

## License

This project was built for academic purposes as part of a laboratory activity on GPIO and button control.
