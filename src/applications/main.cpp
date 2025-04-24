
#include <WiFiMulti.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "domain/model/Pond.h"
#include "domain/use_case/PondStatusEvaluator.h"
#include "infrastructure/driven-adapters/NotificationService.h"
#include "infrastructure/driven-adapters/ThingSpeakService.h"

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// DHT
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WiFiMulti wifiMulti;
  
void setup_wifi() {
  Serial.print("Connecting to WiFi");
  wifiMulti.addAP(ssid, password);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
}

void printVars(float temperature, float humidity) {
  LCD.setCursor(0, 0);
  LCD.println("temp: ");
  LCD.setCursor(8, 0);
  LCD.println(temperature);
  LCD.setCursor(0, 1);
  LCD.println("humi: ");
  LCD.println(humidity);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  LCD.init();
  LCD.backlight();
  setup_wifi();
}

void loop() {
  Pond pond;

  Serial.print("Measuring weather conditions... ");
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  pond.setTemperature(temperature);

  pond.setState(PondStatusEvaluator::evaluateStatus(pond));

  NotificationService::sendNotification(pond);

  ThingSpeakService::sendPondData(pond);
  
  printVars(temperature, humidity);

  delay(1000);
}
