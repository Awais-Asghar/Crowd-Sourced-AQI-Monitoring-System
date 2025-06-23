# Crowd-Sourced AQI Monitoring System

![Project Status](https://img.shields.io/badge/status-Completed-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Arduino-blue.svg)
![Tool](https://img.shields.io/badge/tool-Arduino%20IDE-lightgrey.svg)
![Communication](https://img.shields.io/badge/Bluetooth-HC--05-blue.svg)
![Sensors](https://img.shields.io/badge/sensors-MQ135%2C%20PMS5003%2C%20DHT22-orange.svg)
![Language](https://img.shields.io/badge/language-C%2FC++-blue.svg)
![Simulation](https://img.shields.io/badge/simulation-Real%20Environment-yellow.svg)

## Description
An IoT-based, community-driven air quality monitoring system designed to provide real-time AQI (Air Quality Index) estimation using multiple sensors. Built for both urban and rural coverage, this project empowers individuals to participate in environmental monitoring and decision-making.

---

## Overview
This project presents a low-cost, scalable solution for air quality monitoring using IoT. It uses MQ-series gas sensors, particulate matter sensors, temperature & humidity sensors, and Bluetooth communication to calculate and visualize AQI in real-time.

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

---

## System Design

- Sensors → Arduino → Bluetooth → Mobile App  
- Local output via LCD  
- Data processed & visualized for AQI  
- Crowd-sourced model: Users install devices across regions  

---

## Working Principle

Each pollutant’s concentration is read by the sensors. AQI is calculated using EPA-based formulae.  
The final AQI is determined by the maximum AQI among critical pollutants (PM2.5, PM10, CO).

Example:

- PM2.5 AQI: 212.40 (Very Unhealthy)  
- PM10 AQI: 108.42  
- CO AQI: 0.00  
- → Overall AQI = 212.40

---

## Data Collection

Sample Measurements:

- PM2.5: 162 µg/m³  
- PM10: 170 µg/m³  
- CO2: 2.01 ppm  
- CO: 0.32 ppm  
- AQI calculated using official EPA scales  

---

## Results & Analysis

Taken on 19th December, 2024 – 10:42 PM – Islamabad

| Parameter | Value      | AQI Value | Health Impact         |
|-----------|------------|-----------|------------------------|
| PM2.5     | 162 µg/m³  | 212.40    | Very Unhealthy         |
| PM10      | 170 µg/m³  | 108.42    | Unhealthy (Sensitive)  |
| CO        | 0.32 ppm   | 0.00      | Good                   |

- Our AQI: 212.40  
- Accuracy: 99% vs US Embassy AQI System  

---

## Accuracy Validation

- Compared to official U.S. Embassy AQI values  
- Real-time performance testing  
- Achieved 99% correlation for PM2.5 and PM10 values  

Screenshots to Include:

- Hardware Setup  
- Sensor Readings (LCD + Mobile)  
- Block Diagram  
- Comparative Graphs  
- AQI Visualizations  

---

## Future Work

We aim to:

- Integrate LSTM-based ML models for future AQI prediction  
- Enhance sensor calibration  
- Add GPS tagging for geo-based AQI mapping  
- Build a centralized web dashboard for user-friendly analysis  

---

## Contributors

- Awais Asghar  
- Muhammad Hammad Sarwar  
- Muhammad Ashar Javid  
- School of Electrical Engineering & Computer Science, NUST  
