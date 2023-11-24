
// From https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide

#include "Arduino.h"
#include <WiFiClientSecure.h>
#include "Mqtt.h"
#include "BMP280.h"
#include "DHT22.h"
#include "LDR.h"
#include "PD.h"
#include "WiFiKeys.h"
#include <PubSubClient.h>
#include "WiFiClientSecure.h"
#include "env.h"
#include "WiFiKeys.h"

#define LDR_PIN 36
#define PD_PIN 39
#define DHT22_PIN 4

WiFiClient espClient;
Mqtt client(espClient);

void wifiConnect()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

Sensor *ldr = new LDR(client, LDR_PIN);
Sensor *pd = new PD(client, PD_PIN);
Sensor *dht = new SensorDHT22(client, DHT22_PIN);
Sensor *bmp = new BMP280(client);

void CallbackTopic(char *topic, byte *message, unsigned int length)
{
  ldr->callbackTopic(topic, message, length);
  pd->callbackTopic(topic, message, length);
  dht->callbackTopic(topic, message, length);
  bmp->callbackTopic(topic, message, length);
}

void CallbackSubscribe()
{
  ldr->callbackSubscribe();
  pd->callbackSubscribe();
  dht->callbackSubscribe();
  bmp->callbackSubscribe();
}


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(13));
  client.setCallback(CallbackTopic);
  client.setCallbackSubscribe(CallbackSubscribe);
  wifiConnect();
}

void loop() {
  client.reconnect();
  client.loop();
  ldr->measure();
  pd->measure();
  bmp->measure(ALL);
  dht->measure(ALL);
  
  ldr->publishMeasurement(1000);
  pd->publishMeasurement(1000);
  bmp->publishMeasurement(ALL,1000);
  dht->publishMeasurement(ALL,1000);
}
