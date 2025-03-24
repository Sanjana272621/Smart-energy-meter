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
* PZEM004Tv30.h

## Installation and Setup
* Install Libraries: Download and install the required libraries in Arduino IDE.
* Hardware Setup: Connect ESP8266, PZEM-004T, and CT sensor as per the circuit diagram.
* WiFi Credentials: Update your WiFi SSID and password in the Arduino code.
* Upload Code: Upload the sketch to the ESP8266 via Arduino IDE.

Access Dashboard:
* Open the Serial Monitor to get the assigned IP address.
* Enter the IP address in your web browser to view real-time energy data.

## Features
* Web Dashboard: Displays real-time voltage, current, power, energy consumption, and frequency.
* Live Updates: Data is refreshed at regular intervals automatically (no manual reload required).
* WiFi Enabled: Monitor energy usage wirelessly via any browser on the local network.
* Accurate Readings: Uses industrial-grade PZEM-004T for precise power metrics.
* Compact Design: Minimal hardware footprint with easy integration into existing setups.

## Web Interface
The web-based interface displays:
* Voltage (V)
* Current (A)
* Power (W)
* Energy Usage (Wh)
* Frequency (Hz)

Future Improvements
* Integration with cloud platforms (e.g., Thingspeak, Firebase) for remote access and data logging.
* Mobile application for energy tracking and usage alerts.
* Enhanced UI with charts and historical data trends.
* Automatic power threshold alerts via email or SMS.
