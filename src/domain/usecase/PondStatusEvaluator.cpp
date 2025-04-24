#include "PondStatusEvaluator.h"

String PondStatusEvaluator::evaluateStatus(const Pond& data) {
    
    Serial.println(String("Temperature: ") + String(data.getTemperature()));

    bool tempAlta = data.getTemperature() > 30;
    bool tempIdeal = data.getTemperature() >= 22 && data.getTemperature() <= 30;

    if (tempAlta) {
        return "CRITICO";
    } else if (tempIdeal) {
        return "ESTABLE";
    } else {
        return "ACEPTABLE";
    }

    /*
    bool phAcido = data.getPH() < 6.5;
    bool phNeutro = data.getPH() >= 6.5 && data.getPH() <= 8.5;

    bool oxiBajo = data.getOxygen() < 5;
    bool oxiAdecuado = data.getOxygen() >= 5 && data.getOxygen() <= 8;

    if ((tempAlta && oxiBajo) || (phAcido && oxiBajo)) {
        return "CRITICO";
    } else if ((phAcido || tempAlta || oxiBajo)) {
        return "ALERTA";
    } else if (tempIdeal && phNeutro && oxiAdecuado) {
        return "ESTABLE";
    } else {
        return "ACEPTABLE";
    }
    */
}
