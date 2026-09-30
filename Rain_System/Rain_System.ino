#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
const int RAIN_SENSOR_PIN = A0;
const int BUZZER_PIN= 8;
const int LED_ALERT_PIN = 7;
Adafruit_BME280 bme;
unsigned long lastSampleTime = 0;
const unsigned long SAMPLE_INTERVAL = 3600000UL;
float previousPressure = 0.0;
float currentPressure = 0.0;
float currentHumidity  = 0.0;
float deltaPressure= 0.0;
const float HUMIDITY_SPLIT  = 66.5;
const float DELTA_P_HIGH_HUMID  = -0.65;
const float DELTA_P_LOW_HUMID = -1.55;
bool predictRain(float humidity, float deltaP) {
     if (humidity > HUMIDITY_SPLIT) {
        if (deltaP <= DELTA_P_HIGH_HUMID) {
            return true;
        }
    } else {
       if (deltaP <= DELTA_P_LOW_HUMID) {
            return true;
        }
    }
    return false;
    }
    void setup() {
    Serial.begin(9600);
    while (!Serial);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_ALERT_PIN, OUTPUT);
    pinMode(RAIN_SENSOR_PIN, INPUT);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_ALERT_PIN, LOW);
    if (!bme.begin(0x76)) {
        Serial.println("Error: Could not find a valid BME280 sensor! Check wiring.");
        while (1);
    }

    Serial.println("BME280 initialized successfully.");
    previousPressure = bme.readPressure() / 100.0F;
    currentPressure  = previousPressure;
    lastSampleTime   = millis();

    Serial.print("Initial Baseline Pressure: ");
    Serial.print(previousPressure);
    Serial.println(" hPa");
}