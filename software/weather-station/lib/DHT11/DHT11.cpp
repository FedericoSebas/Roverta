#include "DHT11.h"

SensorDHT11::SensorDHT11(Mqtt &defaulClient, int pin) : Sensor(defaulClient, pin),DHT (pin, DHT11){}

int SensorDHT11::getMeasurement(int magnitude)
{
  return measurement[magnitude];
}

void SensorDHT11::measure(int magnitude)
{
  if(magnitude == TEMPERATURE_DHT11){
    measurement[TEMPERATURE_DHT11] = readTemperature();
  }
  else if(magnitude == MOISTURE_DHT11){
    measurement[MOISTURE_DHT11] = readHumidity();
  }
  else if(magnitude == ALL_DHT11){
    measurement[TEMPERATURE_DHT11] = readTemperature();
    measurement[MOISTURE_DHT11] = readHumidity();
  }
}

void SensorDHT11::publishMeasurement(int magnitude,int timeout)
{
  StaticJsonDocument<200> ObjtTemperature;
  ObjtTemperature["unit"] = "ºC";
  ObjtTemperature["value"] = measurement[TEMPERATURE_DHT11];

  serializeJson(ObjtTemperature, bufferTemperature);

  
  StaticJsonDocument<200> ObjtMoisutre;
  ObjtMoisutre["unit"] = "%";
  ObjtMoisutre["value"] = measurement[MOISTURE_DHT11];

  serializeJson(ObjtMoisutre, bufferMoisture);

  if(magnitude == TEMPERATURE_DHT11){
    if (millis() > lastMsgDHT11[TEMPERATURE_DHT11] + timeout) {
    lastMsgDHT11[TEMPERATURE_DHT11] = millis(); 
    client.publish("sensor/dht11/temperature", bufferTemperature);
  }
  }
  
  if(magnitude == MOISTURE_DHT11){
    if (millis() > lastMsgDHT11[MOISTURE_DHT11] + timeout) {
    lastMsgDHT11[MOISTURE_DHT11] = millis(); 
    client.publish("sensor/dht11/moisture", bufferMoisture);
  }
  }
  
  if(magnitude == ALL_DHT11){
    if (millis() > lastMsgDHT11[ALL_DHT11] + timeout) {
    lastMsgDHT11[ALL_DHT11] = millis(); 
    client.publish("sensor/dht11/temperature", bufferTemperature);
    client.publish("sensor/dht11/moisture", bufferMoisture);
  }
  }
}


void SensorDHT11::callbackTopic(char *topic, byte *message, unsigned int length)
{
  String Message;
  for (int i = 0; i < length; i++)
  {
    Message += (char)message[i];
  }

  if (!strcmp(topic, "sensor/dht11/temperature_min"))
  {
    if (Message.toInt())
    {
      temperatureMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/dht11/temperature_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/dht11/temperature_max"))
  {
    if (Message.toInt())
    {
      temperatureMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/dht11/temperature_max", "The number must to be gratear than 0");
    }
  }

  
  if (!strcmp(topic, "sensor/dht11/moisture_min"))
  {
    if (Message.toInt() > 0)
    {
      moistureMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/dht11/moisture_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/dht11/moisture_max"))
  {
    if (Message.toInt() > 0)
    {
      moistureMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/dht11/moisture_max", "The number must to be gratear than 0");
    }
  }
}

void SensorDHT11::callbackSubscribe()
{
  client.subscribe("sensor/dht11/temperature_min");
  client.subscribe("sensor/dht11/temperature_max");
  client.subscribe("sensor/dht11/moisture_min");
  client.subscribe("sensor/dht11/moisture_max");
  client.subscribe("debug/sensor/dht11/temperature_min");
  client.subscribe("debug/sensor/dht11/temperature_max");
  client.subscribe("debug/sensor/dht11/moisture_min");
  client.subscribe("debug/sensor/dht11/moisture_max");
}
