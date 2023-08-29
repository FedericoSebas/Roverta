
// From https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide

#include "Arduino.h"
#include <WiFiClientSecure.h>
#include "Mqtt.h"
#include "BMP280.h"
#include "DHT11.h"
#include "LDR.h"
#include "PD.h"
#include "WiFiKeys.h"
#include <PubSubClient.h>
#include "WiFiClientSecure.h"

#define LDR_PIN 34
#define PD_PIN 35
#define DHT11_PIN 5

WiFiClientSecure espClient;
Mqtt client(espClient);

Sensor *ldr = new LDR(client, LDR_PIN);
Sensor *pd = new PD(client, PD_PIN);
Sensor *dht = new SensorDHT11(client, DHT11_PIN);
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
  randomSeed(analogRead(0));
  client.setCallback(CallbackTopic);
  client.setCallbackSubscribe(CallbackSubscribe);
  client.wifiConnect();
}

void loop() {
  client.reconnect();
  client.loop();
  ldr->measure();
  pd->measure();
  bmp->measure(ALL_BMP);
  dht->measure(ALL_DHT);
}
