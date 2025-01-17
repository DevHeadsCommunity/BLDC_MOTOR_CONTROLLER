# BLDC Motor Control using SPWM and FOC
## Project overview

This project aims to control a 3-phase BLDC motor using an STM32F103C8T6 microcontroller. Initially, the motor will be driven using Sinusoidal Pulse Width Modulation (SPWM), with speed control via an ADC-connected potentiometer. Later, the project will implement Field-Oriented Control (FOC) for improved efficiency and performance.
## Key Features

* SPWM-Based Motor Control: Generate three-phase sine wave signals using a precomputed sine table.

* Speed Control via ADC: Use a potentiometer to adjust motor speed by modifying the duty cycle of the SPWM signals.

* Hall Sensor Feedback: Utilize Hall sensors for accurate rotor position detection and proper commutation.

* Transition to FOC: Implement Field-Oriented Control for precise torque and speed regulation.

## Components Needed

* STM32F103C8T6 Microcontroller: Main controller for generating SPWM and handling motor control logic.

* BLDC Motor with Hall Sensors: Three-phase motor with position feedback.

* MOSFET Driver Circuit: To drive the motor windings with appropriate PWM signals.

* Potentiometer: For adjusting motor speed via ADC input.

* Power Supply: Suitable voltage and current rating for the BLDC motor.

* Supporting Components: Resistors, capacitors, connectors, etc.



## Project Plan
### 1. Set Up Development Environment
(i)  Install vs code for firmware development.

(ii) Set up the STM32F103C8T6 development board.

### 2. Configure Hardware
(i) Connect the BLDC motor phases to the MOSFET driver circuit.

(ii) Attach Hall sensors to the STM32 for rotor position feedback.

(iii) Connect a potentiometer to an ADC pin for speed control.

### 3. Firmware Development
#### (i) Initialize Peripherals
* Configure timers for SPWM generation.
* Set up ADC for reading the potentiometer.
* Configure GPIOs for Hall sensor inputs.
* Setup Usart for debugging
  
(ii) Implement SPWM Control
* Use a sine wave lookup table to generate 3-phase PWM signals.
* Adjust duty cycle based on ADC input to control speed.

(iii) Hall Sensor-Based Commutation
* Read Hall sensor inputs to determine rotor position.
* Align SPWM signals with the correct commutation step.
* 
### 4. Transition to FOC
* Implement Clarke and Park transformations for FOC.
* Use a PID controller for torque and speed regulation.
* Optimize performance by reducing torque ripple.
  
### 5. Testing and Validation
* Verify SPWM-based motor control and speed adjustment.
* Measure efficiency improvements after implementing FOC.
* Ensure smooth motor operation with minimal noise and vibration.

### 5. Future Enhancements
* Implement regenerative braking for energy recovery.
* Add closed-loop speed control using a feedback loop.

