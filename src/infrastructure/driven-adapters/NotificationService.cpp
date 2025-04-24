#include "NotificationService.h"

void NotificationService::sendNotification(const Pond& pond) {
    String state = pond.getState();

    if (state == "CRITICO") {
        Serial.println("📡 SMS enviado: ¡Estado CRÍTICO! Actúe inmediatamente.");
    } else if (state == "ALERTA") {
        Serial.println("📡 SMS enviado: Estado en ALERTA. Revise las condiciones del estanque.");
    } else if (state == "ESTABLE") {
        Serial.println("📡 SMS: El estanque se encuentra en estado ESTABLE. Todo en orden.");
    } else {
        Serial.println("📡 SMS: Estado del estanque: " + state);
    }
}
