<div align="center">

# ESP32-S3 GPIO & Button Control

### Laboratory Activity 3

A simple ESP32-S3 GPIO project demonstrating **digital input**, **internal pull-up logic**, and **opposite-state LED control** using a pushbutton.

<br>

<img src="https://img.shields.io/badge/Board-ESP32--S3-000000?style=for-the-badge&logo=espressif&logoColor=white">
<img src="https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white">
<img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white">
<img src="https://img.shields.io/badge/Status-Completed-22C55E?style=for-the-badge">

<br><br>

<img src="media/circuit.jpg" width="720" alt="ESP32-S3 GPIO Button Control Circuit">

</div>

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/info.svg" width="22"> Overview

This laboratory activity demonstrates GPIO input and output control using an **ESP32-S3 N16R8**.

A pushbutton connected to **GPIO 42** controls two LEDs:

- The **red LED** on GPIO 41 turns ON while the button is pressed.
- The **green LED** on GPIO 40 shows the opposite state.
- When the button is released, the green LED remains ON and the red LED remains OFF.

The pushbutton uses the ESP32's built-in `INPUT_PULLUP` configuration to maintain a stable input state and prevent floating GPIO readings.

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/target.svg" width="22"> Objectives

This laboratory activity aims to:

- Configure an ESP32-S3 GPIO as a digital input.
- Configure GPIO pins as digital outputs.
- Read the state of a pushbutton.
- Understand `HIGH` and `LOW` logic when using `INPUT_PULLUP`.
- Control two LEDs with opposite states.
- Verify the expected state after resetting the microcontroller.

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/cpu.svg" width="22"> Hardware

| Component | Quantity | Description |
|---|:---:|---|
| ESP32-S3 N16R8 | 1 | Main microcontroller |
| Pushbutton | 1 | Digital input |
| Red LED | 1 | Pressed-state indicator |
| Green LED | 1 | Released-state indicator |
| 220 Ω Resistor | 2 | LED current limiting |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | Several | Electrical connections |
| USB Cable | 1 | Power and programming |

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/cable.svg" width="22"> Pin Configuration

| Device | GPIO | Configuration |
|---|:---:|---|
| Pushbutton | `GPIO 42` | `INPUT_PULLUP` |
| Red LED | `GPIO 41` | `OUTPUT` |
| Green LED | `GPIO 40` | `OUTPUT` |

### Wiring

```text
ESP32-S3

GPIO 41 ── 220Ω ── Red LED ─── GND

GPIO 40 ── 220Ω ── Green LED ── GND

GPIO 42 ── Pushbutton ───────── GND
```

> The pushbutton does not require an external pull-up resistor because GPIO 42 uses the ESP32-S3's internal pull-up resistor.

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/image.svg" width="22"> Circuit Setup

The following image shows the physical circuit used during the laboratory activity.

<div align="center">

<img src="media/circuit.jpg" width="750" alt="ESP32-S3 GPIO Circuit">

</div>

### Circuit Description

The circuit consists of:

- A pushbutton connected between **GPIO 42 and GND**
- A red LED connected to **GPIO 41**
- A green LED connected to **GPIO 40**
- A **220 Ω resistor** connected in series with each LED

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/code-2.svg" width="22"> Source Code

```cpp
#include <Arduino.h>

// GPIO connections
const uint8_t BUTTON_PIN = 42;
const uint8_t RED_LED_PIN = 41;
const uint8_t GREEN_LED_PIN = 40;

void setup() {
  // Configure the button using the ESP32's
  // internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configure LEDs as outputs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Initial output state
  // Button released:
  // Red OFF, Green ON
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void loop() {

  // INPUT_PULLUP logic:
  // LOW  = pressed
  // HIGH = released
  const bool pressed = (digitalRead(BUTTON_PIN) == LOW);

  if (pressed) {

    // Button pressed
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

  } else {

    // Button released
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}
```

The complete source code can also be found in:

```text
Lab3_GPIO_Button_Control.ino
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/workflow.svg" width="22"> Program Logic

The button uses:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
```

This activates the ESP32-S3's internal pull-up resistor.

Therefore:

```text
Button Released
      │
      ▼
GPIO 42 = HIGH
      │
      ├──── Red LED   = OFF
      │
      └──── Green LED = ON
```

When the button is pressed:

```text
Button Pressed
      │
      ▼
GPIO 42 = LOW
      │
      ├──── Red LED   = ON
      │
      └──── Green LED = OFF
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/toggle-left.svg" width="22"> Why HIGH Means Released

The pushbutton uses an **active-low configuration**.

When the button is released, the ESP32's internal pull-up resistor keeps GPIO 42 connected logically toward **3.3 V**.

Therefore:

```text
Released → HIGH
```

When the pushbutton is pressed, GPIO 42 becomes connected to **GND**.

Therefore:

```text
Pressed → LOW
```

The program determines whether the button is pressed using:

```cpp
const bool pressed = (digitalRead(BUTTON_PIN) == LOW);
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/flask-conical.svg" width="22"> Testing Procedure

The circuit was tested using the following sequence:

### Test 1 — Initial State

Power the ESP32-S3 without pressing the pushbutton.

Expected:

```text
Button    = Released
GPIO 42   = HIGH
Red LED   = OFF
Green LED = ON
```

### Test 2 — Button Pressed

Press and hold the pushbutton.

Expected:

```text
Button    = Pressed
GPIO 42   = LOW
Red LED   = ON
Green LED = OFF
```

### Test 3 — Button Released

Release the pushbutton.

Expected:

```text
Button    = Released
GPIO 42   = HIGH
Red LED   = OFF
Green LED = ON
```

### Test 4 — Reset Test

Release the pushbutton and press the ESP32-S3 **RESET / EN** button.

Expected after restart:

```text
Red LED   = OFF
Green LED = ON
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/table-2.svg" width="22"> Observation Table

| Test | Button State | GPIO 42 | Red LED GPIO 41 | Green LED GPIO 40 | Result |
|---|---|:---:|:---:|:---:|:---:|
| Initial State | Released | HIGH | OFF | ON | PASS |
| Button Held | Pressed | LOW | ON | OFF | PASS |
| Button Released | Released | HIGH | OFF | ON | PASS |
| After Reset | Released | HIGH | OFF | ON | PASS |

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/circle-help.svg" width="22"> Laboratory Questions

### 1. What are the GPIO connections?

The pushbutton is connected to **GPIO 42** and GND.

The red LED is connected to **GPIO 41** through a 220 Ω resistor.

The green LED is connected to **GPIO 40** through another 220 Ω resistor.

---

### 2. What happens when the button is released?

When the button is released, GPIO 42 reads:

```text
HIGH
```

The resulting outputs are:

```text
Red LED   = OFF
Green LED = ON
```

---

### 3. What happens when the button is pressed?

Pressing the pushbutton connects GPIO 42 to GND.

The input therefore becomes:

```text
LOW
```

The resulting outputs are:

```text
Red LED   = ON
Green LED = OFF
```

---

### 4. What do HIGH and LOW mean for the button?

Because the input uses `INPUT_PULLUP`:

| GPIO Reading | Button State |
|:---:|---|
| `HIGH` | Released |
| `LOW` | Pressed |

The button therefore operates using **active-low logic**.

---

### 5. Why does the input not randomly change when the button is released?

The internal pull-up resistor keeps GPIO 42 at a defined HIGH voltage level while the button is open.

Without a pull-up or pull-down resistor, the GPIO pin could become a **floating input**, which can result in unpredictable HIGH and LOW readings.

---

### 6. What happens after resetting the board?

When the ESP32-S3 resets while the button is released, the `setup()` function runs again.

The program initializes:

```cpp
digitalWrite(RED_LED_PIN, LOW);
digitalWrite(GREEN_LED_PIN, HIGH);
```

Therefore, the expected state after reset is:

```text
Red LED   = OFF
Green LED = ON
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/video.svg" width="22"> Demonstration

A physical hardware demonstration was recorded to verify the circuit behavior.

<div align="center">

### Hardware Demo

[![Watch the Demonstration](media/demo-thumbnail.jpg)](media/demo.mp4)

**Click the image above to view the demonstration video.**

</div>

The demonstration shows:

1. Initial circuit state
2. Button released
3. Button pressed
4. Button held
5. Button released again
6. ESP32-S3 reset
7. Expected initial state after reset

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/check-circle-2.svg" width="22"> Success Criteria

The laboratory activity is considered successful when:

- [x] GPIO connections are correctly identified
- [x] Pushbutton input remains stable when released
- [x] Button released produces `HIGH`
- [x] Button pressed produces `LOW`
- [x] Red LED turns ON while the button is pressed
- [x] Green LED turns OFF while the button is pressed
- [x] Green LED turns ON when the button is released
- [x] Red LED turns OFF when the button is released
- [x] Both LEDs always show opposite states
- [x] Reset produces the expected initial output

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/folder-tree.svg" width="22"> Repository Structure

```text
Lab-3-GPIO-Button-Control/
│
├── Lab3_GPIO_Button_Control.ino
├── README.md
│
└── media/
    ├── circuit.jpg
    ├── demo-thumbnail.jpg
    └── demo.mp4
```

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/book-open.svg" width="22"> Key Concepts

This activity demonstrates several fundamental embedded-system concepts:

`GPIO` • `Digital Input` • `Digital Output` • `INPUT_PULLUP` • `Active-Low Logic` • `LED Control` • `ESP32-S3`

---

## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/graduation-cap.svg" width="22"> Conclusion

The laboratory activity successfully demonstrated digital GPIO control using an ESP32-S3.

The pushbutton was configured using `INPUT_PULLUP`, resulting in an active-low input where **HIGH represents the released state and LOW represents the pressed state**.

The red and green LEDs were programmed to operate in opposite states. The internal pull-up resistor also prevented the button input from floating when released, resulting in stable and predictable GPIO readings.

---

<div align="center">

### Laboratory Activity 3

**GPIO and Button Control using ESP32-S3**

Made for embedded systems laboratory experimentation.

</div>
