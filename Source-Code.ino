#include <DHT11.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LiquidCrystal.h>
#include <Adafruit_BMP280.h>
#include <MQUnifiedsensor.h>
#include <SoftwareSerial.h>

SoftwareSerial pmsSerial(7, 10); // PMS_TX-->7, PMS_RX-->10
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
Adafruit_BMP280 bmp; // BMP280 connected via I2C
DHT11 dht11(8); // DHT11 connected to pin 8

#define BMP280_ADDRESS 0x76
#define MQ2_PIN A0
#define MQ135_PIN A1
#define MQ7_PIN A2

// MQ-2 Configuration
MQUnifiedsensor MQ2("Arduino UNO", 5, 10, MQ2_PIN, "MQ-2");
#define MQ2_CLEAN_AIR_RATIO 9.83

// MQ-135 Configuration
MQUnifiedsensor MQ135("Arduino UNO", 5, 10, MQ135_PIN, "MQ-135");
#define MQ135_CLEAN_AIR_RATIO 3.6

// MQ-7 Configuration
MQUnifiedsensor MQ7("Arduino UNO", 5, 10, MQ7_PIN, "MQ-7");
#define MQ7_CLEAN_AIR_RATIO 27.6


// Non-blocking timing variables
unsigned long previousMillis = 0;
unsigned long interval = 1000; // Delay between updates in milliseconds

void setup() {
    // Serial Monitor Initialization
    Serial.begin(9600);  // Serial Monitor
    pmsSerial.begin(9600);
    while (!Serial); // Wait for Serial to be ready
    Serial.println(F("Initializing System..."));
    Serial.println();

    // LCD Initialization
    lcd.begin(16, 2);
    lcd.print(F("Air Monitoring"));
    lcd.setCursor(0, 1);
    lcd.print(F("Initializing..."));
    delay(2000);
    lcd.clear();

    // BMP280 Initialization
    if (!bmp.begin(BMP280_ADDRESS)) {
        Serial.println(F("BMP280 Initialization Failed! Check connections."));
        lcd.print(F("BMP280 Error!"));
        while (1); // Halt if BMP280 fails
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    // MQ-2 Initialization and Calibration
    MQ2.setRegressionMethod(1); // PPM = a * ratio^b
    MQ2.init();
    float r0 = calibrateSensor(MQ2, MQ2_CLEAN_AIR_RATIO, "MQ-2");
    MQ2.setR0(r0);

    // MQ-135 Initialization and Calibration
    MQ135.setRegressionMethod(1);
    MQ135.init();
    r0 = calibrateSensor(MQ135, MQ135_CLEAN_AIR_RATIO, "MQ-135");
    MQ135.setR0(r0);
    
    // MQ-7 Initialization and Calibration
    MQ7.setRegressionMethod(1);
    MQ7.init();
    r0 = calibrateSensor(MQ7, MQ7_CLEAN_AIR_RATIO, "MQ-7");
    MQ7.setR0(r0);

    Serial.println(F("System Initialized!"));
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
struct pms5003data data;

float calibrateSensor(MQUnifiedsensor &sensor, float cleanAirRatio, const char *sensorName) {
    Serial.print(F("Calibrating "));
    Serial.print(sensorName);
    Serial.println(F(", please wait..."));
    float r0 = 0;
    for (int i = 0; i < 10; i++) {
        sensor.update();
        r0 += sensor.calibrate(cleanAirRatio);
        delay(500);
    }
    r0 /= 10;
    if (isinf(r0) || r0 == 0) {
        Serial.print(sensorName);
        Serial.println(F(" calibration failed! Check wiring."));
        lcd.print(F("Calibration Error!"));
        while (1); // Halt if calibration fails
    }
    Serial.print(sensorName);
    Serial.println(F(" calibration successful."));
    return r0;
}

void loop() {
    // Non-blocking update based on interval
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        runBMP280();
        runDHT11();
        runMQ2();
        runMQ135();
        runMQ7();
        if (readPMSdata(&pmsSerial)) 
        {
         Serial.println("---------------------------------------");
         Serial.println("Concentration Units (environmental)");
         Serial.print("PM 2.5: "); Serial.print(data.pm25_env);
         Serial.print("\t\tPM 10: "); Serial.println(data.pm100_env);

         float co_ppm = MQ7.readSensor(); // Read CO value from MQ-7
         printAirQualityStatus(data.pm25_env, data.pm100_env, co_ppm); // Updated function call
         Serial.println("---------------------------------------");
         }
    }
}

void runBMP280() {
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude(1013.25);
    Serial.println(F("-------BMP280 & DHT11-------"));
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println(F(" *C"));

    Serial.print(F("Pressure: "));
    Serial.print(pressure);
    Serial.println(F(" Pa"));

    Serial.print(F("Altitude: "));
    Serial.print(altitude);
    Serial.println(F(" m"));

    lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(temperature);
    lcd.print(F("C"));
    lcd.setCursor(0, 1);
    lcd.print(F("Press: "));
    lcd.print(pressure);
    delay(interval);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Altitude: "));
    lcd.print(altitude);
    lcd.print(F("m"));
}

void runDHT11() {
    int temperature = 0, humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    if (result == 0) {
        Serial.print(F("Humidity: "));
        Serial.print(humidity);
        Serial.println(F(" %"));

        lcd.setCursor(0, 1);
        lcd.print(F("Humidity: "));
        lcd.print(humidity);
        lcd.print(F("%"));
        delay(interval);
    } else {
        Serial.println(DHT11::getErrorString(result));
        lcd.setCursor(0, 0);
        lcd.print(F("DHT11 Error!"));
    }
}

void runMQ2() {
    MQ2.update();

      /* H2 */
     MQ2.setA(987.99); 
     MQ2.setB(-2.162);
     float h2 = MQ2.readSensor();
  
    /* Alcohol */
    MQ2.setA(3616.1); 
    MQ2.setB(-2.675);
    float alcohol = MQ2.readSensor();
  
    /* Propane */
    MQ2.setA(658.71); 
    MQ2.setB(-2.168);
    float propane = MQ2.readSensor();

    /* LPG */
    MQ2.setA(574.25);
    MQ2.setB(-2.222);
    float lpg = MQ2.readSensor();

    Serial.println(F("*MQ2*"));
    Serial.print(F("LPG: "));
    Serial.print(lpg);
    Serial.println(F(" ppm"));
    
    Serial.print(F("Alcohol: "));
    Serial.print(alcohol);
    Serial.println(F(" ppm"));

    Serial.print(F("Propane: "));
    Serial.print(propane);
    Serial.println(F(" ppm"));

    Serial.print(F("H2: "));
    Serial.print(h2);
    Serial.println(F(" ppm"));
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("LPG: "));
    lcd.print(lpg);
    lcd.setCursor(0, 1);
    lcd.print(F("Propane: "));
    lcd.print(propane);
    delay(interval);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("H2: "));
    lcd.print(h2);
    lcd.setCursor(0, 1);
    lcd.print(F("Alcohol: "));
    lcd.print(alcohol);
    delay(interval);
}

void runMQ135() {
    MQ135.update();

    MQ135.setA(110.47);
    MQ135.setB(-2.862);
    float co2 = MQ135.readSensor();

    MQ135.setA(102.2); 
    MQ135.setB(-2.473);
    float nh4 = MQ135.readSensor();

    MQ135.setA(34.68);
    MQ135.setB(-3.369);
    float acetone = MQ135.readSensor();

    MQ135.setA(44.947);
    MQ135.setB(-3.445);
    float toluene = MQ135.readSensor();

    Serial.println(F("=======MQ135======="));
    Serial.print(F("CO2: "));
    Serial.print(co2);
    Serial.println(F(" ppm"));

    Serial.print(F("NH4: "));
    Serial.print(nh4);
    Serial.println(F(" ppm"));
    
    Serial.print(F("Acetone: "));
    Serial.print(acetone);
    Serial.println(F(" ppm"));

    Serial.print(F("Toluene: "));
    Serial.print(toluene);
    Serial.println(F(" ppm"));
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("CO2: "));
    lcd.print(co2);
    lcd.setCursor(0, 1);
    lcd.print(F("NH4: "));
    lcd.print(nh4);
    delay(interval);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Toluene: "));
    lcd.print(toluene);
    lcd.setCursor(0, 1);
    lcd.print(F("Acetone: "));
    lcd.print(acetone);
    delay(interval);
}

void runMQ7() { 

    MQ7.update();

    MQ7.setA(99.042);
    MQ7.setB(-1.518);
    float co = MQ7.readSensor();

    MQ7.setA(60000000000000);
    MQ7.setB(-10.54);
    float methane = MQ7.readSensor();
    
    Serial.println(F("-------MQ7-------"));
    Serial.print(F("CO: "));
    Serial.print(co);
    Serial.println(F(" ppm"));
    
    Serial.print(F("CH4: "));
    Serial.print(methane);
    Serial.println(F(" ppm"));

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("CO: "));
    lcd.print(co);
    lcd.setCursor(0, 1);
    lcd.print(F("CH4: "));
    lcd.print(methane);
    delay(interval);
}

void printAirQualityStatus(uint16_t pm25, uint16_t pm10, float co_ppm) {
  // Calculate AQI for PM2.5, PM10, and CO
  float aqi_pm25 = calculateAQI(pm25, "PM2.5");
  float aqi_pm10 = calculateAQI(pm10, "PM10");
  float aqi_co = calculateAQI(co_ppm, "CO");

  // Display AQI results
  Serial.println("Air Quality Status:");
  Serial.print("PM2.5 AQI: ");
  Serial.print(aqi_pm25);
  Serial.print(" (");
  Serial.print(getAQICategory(aqi_pm25));
  Serial.println(")");

  Serial.print("PM10 AQI: ");
  Serial.print(aqi_pm10);
  Serial.print(" (");
  Serial.print(getAQICategory(aqi_pm10));
  Serial.println(")");

  Serial.print("CO AQI: ");
  Serial.print(aqi_co);
  Serial.print(" (");
  Serial.print(getAQICategory(aqi_co));
  Serial.println(")");

  // Overall AQI is the maximum of the three
  float overall_aqi = max(aqi_pm25, max(aqi_pm10, aqi_co));
  Serial.print("Overall AQI: ");
  Serial.print(overall_aqi);
  Serial.print(" (");
  Serial.print(getAQICategory(overall_aqi));
  Serial.println(")");
}

float calculateAQI(float concentration, String pollutant) {
  // Define AQI breakpoints for PM2.5, PM10, and CO
  float c_lo, c_hi, i_lo, i_hi;

  if (pollutant == "PM2.5") {
    if (concentration <= 12.0) { c_lo = 0; c_hi = 12.0; i_lo = 0; i_hi = 50; }
    else if (concentration <= 35.4) { c_lo = 12.1; c_hi = 35.4; i_lo = 51; i_hi = 100; }
    else if (concentration <= 55.4) { c_lo = 35.5; c_hi = 55.4; i_lo = 101; i_hi = 150; }
    else if (concentration <= 150.4) { c_lo = 55.5; c_hi = 150.4; i_lo = 151; i_hi = 200; }
    else if (concentration <= 250.4) { c_lo = 150.5; c_hi = 250.4; i_lo = 201; i_hi = 300; }
    else { c_lo = 250.5; c_hi = 500.4; i_lo = 301; i_hi = 500; }
  } else if (pollutant == "PM10") {
    if (concentration <= 54) { c_lo = 0; c_hi = 54; i_lo = 0; i_hi = 50; }
    else if (concentration <= 154) { c_lo = 55; c_hi = 154; i_lo = 51; i_hi = 100; }
    else if (concentration <= 254) { c_lo = 155; c_hi = 254; i_lo = 101; i_hi = 150; }
    else if (concentration <= 354) { c_lo = 255; c_hi = 354; i_lo = 151; i_hi = 200; }
    else if (concentration <= 424) { c_lo = 355; c_hi = 424; i_lo = 201; i_hi = 300; }
    else { c_lo = 425; c_hi = 604; i_lo = 301; i_hi = 500; }
  } else if (pollutant == "CO") {
    if (concentration <= 4.4) { c_lo = 0; c_hi = 4.4; i_lo = 0; i_hi = 50; }
    else if (concentration <= 9.4) { c_lo = 4.5; c_hi = 9.4; i_lo = 51; i_hi = 100; }
    else if (concentration <= 12.4) { c_lo = 9.5; c_hi = 12.4; i_lo = 101; i_hi = 150; }
    else if (concentration <= 15.4) { c_lo = 12.5; c_hi = 15.4; i_lo = 151; i_hi = 200; }
    else if (concentration <= 30.4) { c_lo = 15.5; c_hi = 30.4; i_lo = 201; i_hi = 300; }
    else { c_lo = 30.5; c_hi = 50.4; i_lo = 301; i_hi = 500; }
  }

  // Apply AQI formula
  float aqi = ((i_hi - i_lo) / (c_hi - c_lo)) * (concentration - c_lo) + i_lo;
  return aqi;
}

String getAQICategory(float aqi) {
  if (aqi <= 50) return "Good";
  if (aqi <= 100) return "Moderate";
  if (aqi <= 150) return "Unhealthy for Sensitive Groups";
  if (aqi <= 200) return "Unhealthy";
  if (aqi <= 300) return "Very Unhealthy";
  return "Hazardous";
}

boolean readPMSdata(Stream *s) {
  if (!s->available()) {
    return false;
  }

  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  return true;
}
