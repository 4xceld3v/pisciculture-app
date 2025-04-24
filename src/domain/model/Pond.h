#ifndef PONDDATA_H
#define PONDDATA_H
#include <Arduino.h>

class Pond {

private:
    float temperature;
    float pH;
    float oxygen;
    String state;

public:
    
    Pond();
    Pond(float tempVal, float phVal, float oxyVal, String stateVal);
    Pond(float tempVal, String stateVal);

    float getTemperature() const;
    float getPH() const;
    float getOxygen() const;
    String getState() const;

    void setTemperature(float tempVal);
    void setPH(float phVal);
    void setOxygen(float oxyVal);
    void setState(String stateVal);
};

#endif
