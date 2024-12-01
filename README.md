# IoT-Based Air Quality Monitoring System with Machine Learning

## Description
This project focuses on creating an IoT-powered system for monitoring air quality using a combination of advanced sensors and machine learning models. It collects real-time environmental data, transmits it via the HC-05 Bluetooth module, and predicts air quality indices using a custom-built mobile app. The solution is designed for urban and industrial settings to help track air quality and ensure healthier living conditions.

---

## Features
- **Real-time Data Collection**: Monitors environmental parameters such as temperature, humidity, and pollutant levels using:
  - **BME280**: Measures temperature, humidity, and pressure.
  - **MQ7**: Detects carbon monoxide (CO).
  - **MQ2**: Detects flammable gases like propane and methane.
  - **MQ135**: Measures air quality by detecting harmful gases.
  - **PMS5003**: Measures particulate matter (PM2.5 and PM10).
- **Data Transmission**: Uses the HC-05 Bluetooth module for seamless serial communication.
- **Machine Learning Predictions**: Leverages ML models in a mobile app for predicting air quality indices.
- **User-Friendly Mobile App**: Displays real-time sensor data and provides predictions with actionable insights.

---

## Hardware Requirements
- **BME280** sensor
- **MQ7** sensor
- **MQ2** sensor
- **MQ135** sensor
- **PMS5003** sensor
- **HC-05 Bluetooth module**
- Arduino/ESP32/Raspberry Pi (for microcontroller setup)
- Power source

---

## Software Requirements
- Arduino IDE or relevant microcontroller programming software
- Python (for ML model training and testing)
- Mobile App (developed using Flutter/React Native/other frameworks)
- Libraries:
  - `sklearn`
  - `numpy`
  - `matplotlib`
  - `serial`

---

## Installation and Usage
### 1. **Hardware Setup**
   - Connect the sensors (BME280, MQ7, MQ2, MQ135, PMS5003) to the microcontroller.
   - Attach the HC-05 module for data transfer.
   - Power up the microcontroller.

### 2. **Software Configuration**
   - Clone this repository:
     ```bash
     git clone https://github.com/yourusername/iot-air-quality-monitoring.git
     cd iot-air-quality-monitoring
     ```
   - Program the microcontroller using the Arduino IDE with the provided code in the `/microcontroller` folder.

### 3. **Data Processing and Prediction**
   - Run the ML scripts in the `/ml-model` folder to preprocess and predict air quality indices.
   - Install the mobile app from the `/app` directory to visualize the data.

### 4. **Testing**
   - Verify sensor readings on a serial monitor.
   - Confirm data transmission to the mobile app.

---

## Project Structure
```plaintext
iot-air-quality-monitoring/
├── app/                  # Mobile app source code
├── microcontroller/      # Code for sensor and Bluetooth setup
├── ml-model/             # ML scripts for predictions
├── data/                 # Collected datasets and preprocessing scripts
├── docs/                 # Documentation and guides
└── README.md             # Project overview
