# STM32L432 Binary Counter

A simple educational project demonstrating binary counting using STM32L432 microcontroller.

## Overview

This project implements an 8-bit binary counter using an STM32L432 microcontroller. It provides a hands-on way to visualize binary numbers through LEDs and interact with them using push buttons.

## Features

- **Binary Visualization**: 8 LEDs display the binary representation of a number (0-255)
- **Interactive Controls**: 
  - Increment button: increases the counter by 1
  - Decrement button: decreases the counter by 1
  - Reset button: sets the counter back to 0
- **Bare Metal Implementation**: Direct register access without HAL libraries
- **Single File**: Entire implementation in one C file for simplicity

## Hardware Requirements

- STM32L432 development board (or custom PCB with STM32L432)
- 8 LEDs (with appropriate current-limiting resistors)
- 3 push buttons
- Connecting wires
- Power supply

## Pin Configuration

| Component | GPIO Pin |
|-----------|----------|
| LEDs (8)  | PA0-PA7  |
| Increment Button | PB0 |
| Decrement Button | PB1 |
| Reset Button | PB2 |

## Getting Started

### Building the Project

1. Clone this repository:
   ```
   git clone https://github.com/yourusername/stm32-binary-counter.git
   ```

2. Set up your toolchain (ARM GCC, Make, etc.)

3. Build the project:
   ```
   make
   ```

### Flashing to the Device

Use your preferred STM32 flashing tool:

```
st-flash write build/binary-counter.bin 0x8000000
```

Or use STM32CubeProgrammer if you prefer a GUI.

## How It Works

The program initializes the GPIO pins, setting up LEDs as outputs and buttons as inputs with pull-up resistors. The main loop continuously checks for button presses:

1. When the increment button is pressed, the counter increases by 1
2. When the decrement button is pressed, the counter decreases by 1
3. When the reset button is pressed, the counter resets to 0

After each button press, the LEDs update to display the binary representation of the current counter value.

## Educational Value

This project is an excellent way to:
- Learn about binary numbers and counting
- Understand bit manipulation in C
- Practice direct microcontroller register access
- Get started with STM32 without complex libraries

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- STMicroelectronics for their excellent microcontrollers
- The embedded systems community for inspiration
