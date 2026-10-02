<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
<div align="center">

[![Arduino][arduino-shield]][arduino-url]
[![ESP32][esp32-shield]][esp32-url]
[![License: Academic][license-shield]][license-url]
[![GitHub last commit][commit-shield]][commit-url]

</div>

<br />

<!-- PROJECT HEADER -->
<div align="center">
  <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/cpu.svg" width="80" height="80" alt="CPU icon" />

  <h1>GPIO and Button Control with LEDs</h1>

  <p>
    Laboratory Activity 3 &mdash; Opposite-state LED switching on an ESP32-S3 using a pushbutton and internal pull-up.
  </p>

  <p>
    <a href="#demo">View Demo</a>
    &nbsp;&middot;&nbsp;
    <a href="#circuit">Circuit Diagram</a>
    &nbsp;&middot;&nbsp;
    <a href="#source-code">Source Code</a>
  </p>
</div>

<br />

<!-- TABLE OF CONTENTS -->
<details>
  <summary><img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/list.svg" width="16" height="16" alt="list" />&nbsp; Table of contents</summary>
  <ol>
    <li><a href="#about">About</a></li>
    <li><a href="#demo">Demo</a></li>
    <li><a href="#circuit">Circuit</a></li>
    <li><a href="#source-code">Source code</a></li>
    <li><a href="#high-and-low-with-input_pullup">HIGH and LOW with INPUT_PULLUP</a></li>
    <li><a href="#observation-table">Observation table</a></li>
    <li><a href="#procedure">Procedure</a></li>
    <li><a href="#hardware-requirements">Hardware requirements</a></li>
    <li><a href="#getting-started">Getting started</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

<br />

---

<!-- ABOUT -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/info.svg" width="20" height="20" alt="info" />&nbsp; About

A pushbutton on **GPIO 42** controls two LEDs wired to **GPIO 41** (red) and **GPIO 40** (green). Release the button and the green LED stays on while the red stays off. Press it and they swap. The two always show opposite states.

The board uses `INPUT_PULLUP`, so GPIO 42 reads **HIGH** when released and **LOW** when pressed. No external pull-up resistor is needed, and the line never floats.

### Built with

<p>
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Arduino_IDE-00878F?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE" />
  <img src="https://img.shields.io/badge/ESP32--S3-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32-S3" />
</p>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- DEMO -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/play-circle.svg" width="20" height="20" alt="play" />&nbsp; Demo

<div align="center">

<video src="https://github.com/xavieryyyyyy/GPIO-Button-Control_with_LEDS/raw/main/media/demo.mp4" controls width="720" poster="media/demo-thumbnail.jpg">
  Your browser does not support the video tag.
</video>

<br />

*Pressing the button turns the red LED on and the green LED off. Releasing it reverses them.*

</div>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- CIRCUIT -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/circuit-board.svg" width="20" height="20" alt="circuit" />&nbsp; Circuit

<div align="center">
  <img src="media/circuit.jpg" alt="Breadboard with ESP32-S3, pushbutton, red LED, and green LED" width="560" />
</div>

<br />

### GPIO pin map

| Component | GPIO | Mode |
|:----------|:----:|:----:|
| <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/pointer.svg" width="14" height="14" /> Pushbutton | `42` | Input (pull-up) |
| <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/lightbulb.svg" width="14" height="14" /> Red LED | `41` | Output |
| <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/lightbulb.svg" width="14" height="14" /> Green LED | `40` | Output |

### Wiring

```
ESP32-S3
  ├── GPIO 42 ──── Button ──── GND
  ├── GPIO 41 ──── 220Ω ──── Red LED (+) ──── GND
  └── GPIO 40 ──── 220Ω ──── Green LED (+) ──── GND
```

> **Note:** Each LED has a 220 Ω current-limiting resistor. The pushbutton connects between GPIO 42 and GND; the internal pull-up holds the line HIGH when the button is open.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- SOURCE CODE -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/code.svg" width="20" height="20" alt="code" />&nbsp; Source code

Full sketch: [`Paraguya_LabAct3_GPIO_and_Button_Control.ino`](Paraguya_LabAct3_GPIO_and_Button_Control.ino)

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

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- HIGH AND LOW -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/toggle-left.svg" width="20" height="20" alt="toggle" />&nbsp; HIGH and LOW with INPUT_PULLUP

When `INPUT_PULLUP` is enabled, the ESP32-S3 ties an internal resistor between the GPIO pin and 3.3 V. That keeps the pin at HIGH until something actively pulls it to GND.

| Button state | GPIO 42 reads | Reason |
|:-------------|:-------------:|:-------|
| **Released** | `HIGH` | Internal pull-up resistor holds the pin at 3.3 V. Nothing is pulling it down. |
| **Pressed** | `LOW` | The button shorts GPIO 42 to GND, which overrides the pull-up. |

Because the pull-up is always active, the pin never floats. The reading stays stable when the button is released, no random toggling.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- OBSERVATION TABLE -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/table.svg" width="20" height="20" alt="table" />&nbsp; Observation table

| Button state | GPIO 42 | Red LED (GPIO 41) | Green LED (GPIO 40) | Opposite? |
|:-------------|:-------:|:------------------:|:-------------------:|:---------:|
| Released | `HIGH` | OFF | ON | ✅ |
| Pressed | `LOW` | ON | OFF | ✅ |

After a board reset, `setup()` sets the red LED LOW and the green LED HIGH. This matches the "Released" row. The initial outputs are the same every time the board powers up.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- PROCEDURE -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/clipboard-list.svg" width="20" height="20" alt="procedure" />&nbsp; Procedure

1. Drew and labeled the GPIO connections on paper before powering the board.
2. Wired the pushbutton to GPIO 42 and the two LEDs to GPIO 41 and GPIO 40 on the breadboard.
3. Uploaded the sketch and confirmed that the green LED turns on and the red LED stays off after power-up.
4. Pressed the button and observed the LEDs swap (red on, green off).
5. Released the button and confirmed the LEDs swap back (green on, red off).
6. Reset the board and verified the initial state matches the expected "released" row.
7. Left the button untouched for a period and confirmed the input does not toggle randomly.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- HARDWARE REQUIREMENTS -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/wrench.svg" width="20" height="20" alt="wrench" />&nbsp; Hardware requirements

| Qty | Component |
|:---:|:----------|
| 1 | ESP32-S3 development board |
| 1 | Pushbutton |
| 1 | Red LED |
| 1 | Green LED |
| 2 | 220 Ω resistor |
| 1 | Breadboard |
| — | Jumper wires |
| 1 | USB cable |

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- GETTING STARTED -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/rocket.svg" width="20" height="20" alt="rocket" />&nbsp; Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add ESP32 board support through the Board Manager.
2. Clone this repository:
   ```sh
   git clone https://github.com/xavieryyyyyy/GPIO-Button-Control_with_LEDS.git
   ```
3. Open `Paraguya_LabAct3_GPIO_and_Button_Control.ino` in the Arduino IDE.
4. Select your ESP32-S3 board and COM port under **Tools**.
5. Click **Upload**.
6. Press and release the pushbutton to see the LEDs alternate.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- LICENSE -->
## <img src="https://raw.githubusercontent.com/lucide-icons/lucide/main/icons/scale.svg" width="20" height="20" alt="license" />&nbsp; License

This project was built for academic purposes as part of a laboratory activity on GPIO and button control.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

---

<!-- MARKDOWN LINKS & IMAGES -->
[arduino-shield]: https://img.shields.io/badge/Arduino-00878F?style=flat&logo=arduino&logoColor=white
[arduino-url]: https://www.arduino.cc/
[esp32-shield]: https://img.shields.io/badge/ESP32--S3-E7352C?style=flat&logo=espressif&logoColor=white
[esp32-url]: https://www.espressif.com/en/products/socs/esp32-s3
[license-shield]: https://img.shields.io/badge/License-Academic-blue?style=flat
[license-url]: #license
[commit-shield]: https://img.shields.io/github/last-commit/xavieryyyyyy/GPIO-Button-Control_with_LEDS?style=flat
[commit-url]: https://github.com/xavieryyyyyy/GPIO-Button-Control_with_LEDS/commits/main
