
#include <WiFiMulti.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "domain/model/Pond.h"
#include "domain/usecase/PondStatusEvaluator.h"
#include "infrastructure/driven-adapters/NotificationService.h"
#include "infrastructure/driven-adapters/ThingSpeakService.h"
#include "infrastructure/entry-points/WeatherSensor.h"


LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// DHT
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
WeatherSensor weatherSensor(dht); 
WiFiMulti wifiMulti;
  
void setup_wifi() {
  delay(100); 
  Serial.println("Connecting to WiFi...");
  wifiMulti.addAP(ssid, password);  
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
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
  float temp;
  float ph;
  Serial.println("Measuring weather conditions... ");
  
  if (weatherSensor.isValid()) {
    temp = weatherSensor.getTemperature();
    ph = weatherSensor.getHumidity();
  }else{
    Serial.println("Failed to read from DHT sensor!");
    return;
  }     

  pond.setTemperature(map(temp, 0, 4095, 10, 40)); // °C
  pond.setPH(map(ph, 0, 4095, 4, 10)); // pH

  pond.setState(PondStatusEvaluator::evaluateStatus(pond));

  NotificationService::sendNotification(pond);

  delay(1000);

  ThingSpeakService::sendPondData(pond);
  
  delay(1000);

  printVars(pond.getTemperature(), pond.getPH());

  delay(1000);
}
