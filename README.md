# Theremin Instrument



## Overview
This project is a contactless, ultrasonic digital Theremin that translates physical hand proximity into synthesized audio frequencies. It serves as an interactive, touch-free auditory interface by combining spatial distance sensing with real-time signal generation. The system continuously measures hand distance and dynamically maps it to a pitch, while a debounced hardware "mute pedal" allows the user to instantly toggle the audio output.

## Hardware Components (BOM)
* Microcontroller (Arduino Uno)
* HC-SR04 Ultrasonic Distance Sensor (Connected to Pins 6 and 7) 
* 8-Ohm Salvaged Speaker (Driven via Pin 8)  
* BC547 NPN Transistor & 1k Resistor (Low-side switching amplifier circuit)
* Tactile Push Button (Connected to Pin 2)
* Power Supply (5V via USB)

## Circuit & Physical Build

*Breadboard prototype showing the HC-SR04 sensor positioning and the BC547 transistor acting as a power valve to safely amplify the Arduino's signal for the salvaged speaker.*

## Software & Libraries
*   **Language:** C++ (Arduino)
*   **Libraries:** Native Arduino Core (Utilizes built-in tone() and pulseIn() functions; no external libraries required)

## How It Works
1. The Arduino constantly polls Pin 2 using an internal pull-up resistor to detect if the physical "mute pedal" button has been pressed, toggling the global isPlaying state.  
2. If the system is unmuted, the ultrasonic sensor sends a 10-microsecond high pulse on Trigger Pin 7 and measures the bounce-back time on Echo Pin 6 to calculate the user's hand distance in centimeters.
3. If the hand is within the active tracking range of 5cm to 50cm, the distance value is mathematically mapped to an audio frequency between 200Hz and 3500Hz. 
4. The tone() function generates a square wave at that exact frequency on Pin 8, which triggers the transistor amplifier to drive the speaker.   
