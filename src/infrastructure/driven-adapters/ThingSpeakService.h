#ifndef THINGSPEAK_SERVICE_H
#define THINGSPEAK_SERVICE_H

#include <Arduino.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "domain/model/Pond.h"

class ThingSpeakService {
public:
    static void sendPondData(const Pond& pond);
};

#endif