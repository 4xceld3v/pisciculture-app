#include "WeatherSensor.h"

float WeatherSensor::getTemperature() {
    return sensor.readTemperature();
}

float WeatherSensor::getHumidity() {
    return sensor.readHumidity();
}

bool WeatherSensor::isValid() {
    float temperature = getTemperature();
    float humidity = getHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return false;
    }

    return true;
}
