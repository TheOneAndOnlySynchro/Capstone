#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
// const char* password = "107WirelessNetwork!";

#define AIO_SERVER  "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "B_jones"
#define AIO_KEY  "aio_SleZ04m2cKVtIVAWykReHpkkwhd9"

#define DHTPIN 15
#define DHTTYPE  DHT22
#define CO2PIN A0
#define FLOATPIN 4
#define LEDPIN 2

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish tempFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.temp");
Adafruit_MQTT_Publish humFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.humidity");
Adafruit_MQTT_Publish co2Feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.co2");
Adafruit_MQTT_Publish lowLevelFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.lowLevel");
Adafruit_MQTT_Publish alarmFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.alarm");
Adafruit_MQTT_Publish lightsFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstone-project-feeds.lights");

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void connectToMQTT() {
  while (mqtt.connected() == false) 
  {
    int8_t ret = mqtt.connect();
  if (ret == 0) {
    Serial.println("Connected to MQTT");
  } else {
    Serial.print("MQTT connect failed, error: ");
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    delay(20000);
  }

  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(FLOATPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);

  connectToWiFi();
}

void loop() {
 connectToMQTT();  

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int co2    = analogRead(CO2PIN) / 4;
  int low    = digitalRead(FLOATPIN);
  bool alarm = (co2 > 200 || low);
  digitalWrite(LEDPIN, alarm);

  Serial.print("Publishing temp...");
  Serial.println(tempFeed.publish(temp) ? "OK" : "FAIL");

  Serial.print("Publishing humidity...");
  Serial.println(humFeed.publish(hum) ? "OK" : "FAIL");

  Serial.print("Publishing CO₂...");
  Serial.println(co2Feed.publish(String(co2).c_str()) ? "OK" : "FAIL");

  Serial.print("Publishing lowlevel...");
  Serial.println(lowLevelFeed.publish(String(low).c_str()) ? "OK" : "FAIL");

  Serial.print("Publishing alarm...");
  Serial.println(alarmFeed.publish(String(alarm).c_str()) ? "OK" : "FAIL");

  Serial.print("Publishing lights...");
  Serial.println(lightsFeed.publish("1") ? "OK" : "FAIL");

  mqtt.processPackets(10000);
  mqtt.ping();

  delay(15000);  
}
