#include "ThingSpeakService.h"

const String API_KEY = "7EA840IG2LIKS73U";
const String URL_BASE = "https://api.thingspeak.com/update?api_key=";
extern WiFiMulti wifiMulti;

void ThingSpeakService::sendPondData(const Pond& pond) {

    if (wifiMulti.run() != WL_CONNECTED) {
        Serial.println("🚫 WiFi no conectado. No se puede enviar a ThingSpeak.");
        return;
    }

    HTTPClient http;

    String url = URL_BASE + API_KEY;
    url += "&field1=" + String(pond.getTemperature());
    url += "&field2=" + String(pond.getPH());
    //url += "&field3=" + String(pond.getOxygen());
    //url += "&field4=" + pond.getState();

    Serial.println("🌐 Enviando datos a: " + url);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
        Serial.println("✅ ThingSpeak respuesta: " + String(httpCode));
        String payload = http.getString();
        Serial.println("📩 Payload: " + payload);
    } else {
        Serial.println("❌ Error en la petición: " + String(http.errorToString(httpCode)));
    }

    http.end();
}
