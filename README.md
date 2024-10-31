# IR Sensor Stepper Motor Distance Mapping Project

## Project Overview

This project aims to collect distance data using an **infrared (IR) sensor** mounted on a **stepper motor**, which will rotate 180 degrees back and forth. The distance data will then be displayed on an **LCD display** to provide real-time feedback on the sensor's readings.

## Goal

The primary goal is to:

1. **Rotate an IR sensor** over a 180-degree arc using a stepper motor.
2. Collect **distance measurements** at different angles during the rotation.
3. Display the distance data on an **LCD display** to visualize the readings in real time.

## Technology Stack

- **Microcontroller**: STM32 (programmed using C)
- **IR Sensor**: For distance measurement
- **Stepper Motor**: Used to rotate the IR sensor
- **LCD Display**: To display the distance data collected from the IR sensor
- **ULN2003 Driver**: To control the stepper motor

## How It Works

1. **Stepper Motor Control**: The stepper motor will be driven by the **ULN2003 motor driver**, controlled by the STM32 microcontroller. The motor will rotate the IR sensor across a 180-degree span.
2. **Distance Measurement**: As the motor rotates, the IR sensor will measure distances at different angles.
3. **Data Display**: The distance measurements will be sent to an LCD display connected to the STM32 for real-time visualization.

## Components

- **STM32 Microcontroller**: The core controller, programmed in C to handle motor control, distance measurement, and data display.
- **IR Sensor**: Measures the distance to objects within its range.
- **Stepper Motor (28BYJ-48)**: Rotates the IR sensor with high precision.
- **ULN2003 Motor Driver**: Controls the stepper motor from the STM32 microcontroller.
- **LCD Display**: Shows the measured distances.

## Useful Documents
- Datasheet for lcd display: https://s3.eu-central-1.amazonaws.com/elektormagazine/shopify/datasheet-ILI9341.pdf

## Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/IR-stepper-motor-project.git
   cd IR-stepper-motor-project
2. **Make a Branch**:
   To make a new branch:
   ```bash
   git checkout -b branchName
   '''
   
