# Smart Energy Meter with IoT Integration
## Overview
This project is an IoT-based Smart Energy Meter that continuously monitors and reports power consumption data in real-time. It measures voltage, current, power, energy usage, and frequency using accurate sensors and transmits the data wirelessly over WiFi.

The system leverages the ESP8266 microcontroller to collect readings from the PZEM-004T energy sensor and a Current Transformer (CT) sensor, displaying the data on a web-based interface for convenient monitoring.

## Hardware Components
* ESP8266 (NodeMCU) – Microcontroller for processing and WiFi communication
* PZEM-004T – Measures voltage, current, power, energy, and frequency
* CT Sensor (Current Transformer) – Additional current sensing (for calibration or validation)
* Arduino Uno – Used for initial sensor interfacing or auxiliary processing (if applicable)
* Connecting Wires – For establishing hardware connections
* Resistors/Headers – As required for secure sensor interfacing

## Software Requirements
* Arduino IDE (latest version)
* ESP8266 Board Package – Install via Arduino Board Manager

Required Libraries:
* ESP8266WiFi.h
* ESP8266WebServer.h
* PZEM004T.h
* SoftwareSerial.h

