#include "Pond.h"
#include <Arduino.h>

Pond::Pond() : temperature(0), pH(0), oxygen(0), state("Unknown") {}

Pond::Pond(float tempVal, float phVal, float oxyVal, String stateVal)
    : temperature(tempVal), pH(phVal), oxygen(oxyVal), state(stateVal) {}

Pond::Pond(float tempVal, String stateVal)
    : temperature(tempVal), pH(0), oxygen(0), state(stateVal) {}

float Pond::getTemperature() const { return temperature; }
float Pond::getPH() const { return pH; }
float Pond::getOxygen() const { return oxygen; }
String Pond::getState() const { return state; }


void Pond::setTemperature(float tempVal) { temperature = tempVal; }
void Pond::setPH(float phVal) { pH = phVal; }
void Pond::setOxygen(float oxyVal) { oxygen = oxyVal; }
void Pond::setState(String stateVal) { state = stateVal; }
