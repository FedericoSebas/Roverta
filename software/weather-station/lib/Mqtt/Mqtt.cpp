#include "Mqtt.h"

subscribeCallback Mqtt::savedCallback = nullptr;

// Default configuraion
Mqtt::Mqtt(WiFiClientSecure &espClient) : PubSubClient(espClient)
{
  // If is a public IP address
  setServer(mqttServer, port);
  espClient.setCACert(mqttCertificates[HIVEMQ_CERTIFICATE]);

  // If is a private IP address
  // setServer(mqttServer, port);
  // setCallback(callbackFunc);
}


Mqtt::Mqtt(WiFiClient &espClient) : PubSubClient(espClient)
{
  // If is a public IP address
  setServer(mqttServer, port);

  // If is a private IP address
  // setServer(mqttServer, port);
  // setCallback(callbackFunc);
}

Mqtt::Mqtt(WiFiClient &espClient, char *server, int port) : PubSubClient(espClient)
{
  setServer(mqttServer, port);
}

Mqtt::Mqtt(WiFiClientSecure &espClient, char *server, int port, int chosenCertificate) : PubSubClient(espClient)
{
  setServer(server, port);
  espClient.setCACert(mqttCertificates[chosenCertificate]);
}
Mqtt::Mqtt(WiFiClientSecure &espClient, char *server, int port, char *certificate) : PubSubClient(espClient)
{
  setServer(server, port);
  espClient.setCACert(certificate);
}

void Mqtt::setCallbackSubscribe(subscribeCallback callback)
{
  savedCallback = callback;
}


void Mqtt::callCallbackSubscribe()
{
  if (savedCallback != nullptr)
  {
    savedCallback();
  }
}

void Mqtt::reconnect()
{
  while (!this->connected())
  {
    Serial.print("Attempting MQTT connection...");
    rand = random(1000);
    sprintf(clientId, "clientId-%ld", rand);
    if (this->connect(clientId, mqttUser, mqttPassword))
    {
      Serial.print(clientId);
      Serial.println(" connected");
    
      callCallbackSubscribe();
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(this->state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      continue;
    }
  }
}

void Mqtt::wifiConnect()
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