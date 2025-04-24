#ifndef WEATHER_SENSOR_H
#define WEATHER_SENSOR_H

#include <DHT.h>

class WeatherSensor {
private:
    DHT& sensor;  // Referencia al objeto DHT
public:
    WeatherSensor(DHT& dhtSensor) : sensor(dhtSensor) {}

    float getTemperature();
    float getHumidity();
    bool isValid();
};

#endif