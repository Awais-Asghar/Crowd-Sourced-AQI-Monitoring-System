# Crowd-Sourced AQI Monitoring System

![Project Status](https://img.shields.io/badge/status-Completed-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Arduino-blue.svg)
![Tool](https://img.shields.io/badge/tool-Arduino%20IDE-lightgrey.svg)
![Communication](https://img.shields.io/badge/Bluetooth-HC--05-blue.svg)
![Simulation](https://img.shields.io/badge/simulation-Real%20Environment-yellow.svg)

## Description
An IoT-based, community-driven air quality monitoring system designed to provide real-time AQI (Air Quality Index) estimation using multiple sensors. Built for both urban and rural coverage, this project empowers individuals to participate in environmental monitoring and decision-making.

---

## Overview
This project presents a low-cost, scalable solution for air quality monitoring using IoT. It uses MQ-series gas sensors, particulate matter sensors, temperature & humidity sensors, and Bluetooth communication to calculate and visualize AQI in real-time.

---

What is AQI (Air Quality Index)?
The Air Quality Index (AQI) is a standardized system used to measure and report the quality of air in a specific location. It tells you how clean or polluted the air is, and what associated health effects might be a concern for you.

- AQI ranges from 0 to 500.
- Lower AQI = cleaner air
- Higher AQI = more polluted air

| AQI Range | Air Quality                  | Health Impact                                                |
| --------- | ---------------------------- | ------------------------------------------------------------ |
| 0–50      | Good                         | Air quality is satisfactory                                  |
| 51–100    | Moderate                     | Acceptable; some pollutants may affect very sensitive people |
| 101–150   | Unhealthy (Sensitive Groups) | May cause health effects for sensitive groups                |
| 151–200   | Unhealthy                    | Everyone may begin to experience health effects              |
| 201–300   | Very Unhealthy               | Health warnings of emergency conditions                      |
| 301–500   | Hazardous                    | Health alert: everyone may be affected                       |


AQI is calculated based on concentrations of pollutants like:

- PM2.5, PM10
- CO (Carbon Monoxide)
- O₃ (Ozone)
- SO₂ (Sulfur Dioxide)
- NO₂ (Nitrogen Dioxide)

![Image](https://github.com/user-attachments/assets/d900efa6-26d8-4b85-b4a6-39c2af37bed6)

--- 

## What is Crowd-Sourcing?
Crowd-sourcing is the practice of collecting data, services, or information by engaging a large number of people, especially from a community or public platform.
In this project:
- Crowd-sourced AQI monitoring means many individuals place sensors in different locations (homes, streets, neighborhoods).
- These devices collect air quality data from multiple locations simultaneously.
- The data is combined to create a detailed and widespread pollution map, much more efficiently and cheaply than using a few government stations.

![Image](https://github.com/user-attachments/assets/96cdc47d-8c97-47a2-92b6-cacf7918e0a5)

![Image](https://github.com/user-attachments/assets/e2660370-3f2e-47b2-8f9d-be9a15b63288)

--- 

## Hardware Used

| Component         | Functionality               |
|------------------|-----------------------------|
| Arduino UNO       | Main microcontroller        |
| MQ135             | CO₂, NH₃, benzene detection |
| MQ7               | Carbon Monoxide (CO)        |
| MQ2               | Smoke, LPG, Methane         |
| PMS5003           | PM2.5, PM10 detection       |
| DHT11 / DHT22     | Temperature & Humidity      |
| BME280            | Pressure, Temp, Humidity    |
| HC-05 Bluetooth   | Mobile communication        |
| 16x2 LCD Display  | Real-time local display     |

![Image](https://github.com/user-attachments/assets/d72cbf4f-22c4-4e3c-ab39-b0de0dce3a24)

---

## Block Diagram
![Image](https://github.com/user-attachments/assets/983c8604-e113-4f46-9f29-8489a401c369)

## System Design 
My Crowd-Sourced AQI Monitoring System is designed using IoT architecture with low-cost, easily available hardware components. It consists of:

### 1. Sensor Unit
- Gas Sensors: MQ135, MQ7, MQ2 – detect CO₂, NH₃, CO, smoke, etc.
- Particulate Matter Sensor: PMS5003 – measures PM2.5 and PM10.
- Environmental Sensors: DHT11/DHT22 and BME280 – for temperature, humidity, and pressure.

### 2. Processing Unit
- Arduino UNO: Reads data from all sensors and processes it.

### 3. Display Unit
- 16x2 LCD: Displays real-time values of gas concentrations, PM levels, temperature, humidity, and calculated AQI.

### 4. Communication Module
- HC-05 Bluetooth: Sends processed data to a mobile app for visualization and logging.

### 5. Crowd-Sourcing
- Multiple such devices are deployed in various locations by different users (the crowd), forming a distributed monitoring network.

### 6. Optional Mobile App
- Receives real-time AQI data via Bluetooth.

---

## Working Principle

### 1. Data Sensing

Each sensor continuously reads the concentration of gases (like CO, CO₂, NH₃), particulate matter (PM2.5, PM10), temperature, and humidity.

### 2. Data Processing

- Arduino processes the raw values.
- Using standard EPA formulas, it calculates the AQI for each pollutant.
- The maximum AQI among CO, PM2.5, PM10 is selected as the overall AQI.

### 3. Display and Transmission

- The AQI and sensor readings are shown on the LCD.
- The same data is sent to a connected mobile device via Bluetooth.

### 4. Crowd-Sourcing Model

- When many users deploy this system in different areas, a network of real-time AQI monitors is created.
- This increases the spatial coverage and data accuracy of air quality reports.

### 5. Validation

The system's output was compared with official AQI data from the US Embassy in Islamabad and showed 99% accuracy.

### Sample AQI Calculation

| Pollutant | Concentration | AQI Value | AQI Category        |
|-----------|---------------|-----------|---------------------|
| PM2.5     | 162 µg/m³     | 212.5     | Very Unhealthy      |
| PM10      | 170 µg/m³     | 108.4     | Unhealthy (Sensitive Groups) |
| CO        | 0.32 ppm      | 3.6       | Good                |
| **Overall AQI** | —           | **212.4** | **Very Unhealthy**  |

![Image](https://github.com/user-attachments/assets/d07f7d54-c0f8-45a5-a543-74eb7523c05b)

---

## Methodology

![Image](https://github.com/user-attachments/assets/73514bed-3920-4543-a980-762a4b41029e)

![Image](https://github.com/user-attachments/assets/5306fee4-887e-4d2c-8217-3eea0e0fd304)

---

## Results & Analysis

Taken on 19th December, 2024 – 10:42 PM – Islamabad

| Parameter | Value      | AQI Value | Health Impact          |
|-----------|------------|-----------|------------------------|
| PM2.5     | 162 µg/m³  | 212.40    | Very Unhealthy         |
| PM10      | 170 µg/m³  | 108.42    | Unhealthy (Sensitive)  |
| CO        | 0.32 ppm   | 0         | Good                   |

- Our AQI: 212.40  
- Accuracy: 99% vs US Embassy AQI System
  
![Image](https://github.com/user-attachments/assets/d18bc0ca-dfac-4171-bb7a-161f1f6226eb)

---

## Future Work

![Image](https://github.com/user-attachments/assets/5fb694e4-9c2a-471b-a319-6f9eb60aec02)

---

## Contributors

- Awais Asghar  
- Muhammad Hammad Sarwar  
- Muhammad Ashar Javid  
- School of Electrical Engineering & Computer Science, NUST  
