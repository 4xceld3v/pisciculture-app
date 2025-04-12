#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.mqttdashboard.com";
const char* mqtt_topic = "wokwi-weather";
const char* mqtt_client_id = "esp32-weather-demo";

// DHT
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

String prevWeather = "";

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT server... ");
    if (client.connect(mqtt_client_id)) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
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
  //setup_wifi();
  //client.setServer(mqtt_server, 1883);
}

void loop() {
  /*if (!client.connected()) {
    reconnect();
  }
  client.loop();*/

  Serial.print("Measuring weather conditions... ");
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String payload = "{\"temp\":" + String(temperature, 1) + ",\"humidity\":" + String(humidity, 1) + "}";
  Serial.println(payload);

  printVars(temperature, humidity);

  /*if (payload != prevWeather) {
    Serial.println("Updated!");
    Serial.print("Reporting to MQTT topic ");
    Serial.print(mqtt_topic);
    Serial.print(": ");
    Serial.println(payload);
    client.publish(mqtt_topic, payload.c_str());
    prevWeather = payload;
  } else {
    Serial.println("No change");
  }*/

  delay(1000);
}