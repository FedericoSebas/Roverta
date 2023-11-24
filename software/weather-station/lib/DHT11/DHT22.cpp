#include "DHT22.h"

SensorDHT22::SensorDHT22(Mqtt &defaulClient, int pin) : Sensor(defaulClient, pin),DHT (pin,DHT22){}

int SensorDHT22::getMeasurement(int magnitude)
{
  return measurement[magnitude];
}

void SensorDHT22::measure(int magnitude)
{
  if(magnitude == TEMPERATURE){
    measurement[TEMPERATURE] = readTemperature();
  }
  else if(magnitude == MOISTURE){
    measurement[MOISTURE] = readHumidity();
  }
  else if(magnitude == ALL){
    measurement[TEMPERATURE] = readTemperature();
    measurement[MOISTURE] = readHumidity();
  }
}

void SensorDHT22::publishMeasurement(int magnitude,int timeout)
{
  StaticJsonDocument<200> ObjtTemperature;
  ObjtTemperature["unit"] = "ºC";
  ObjtTemperature["value"] = measurement[TEMPERATURE];

  serializeJson(ObjtTemperature, bufferTemperature);

  
  StaticJsonDocument<200> ObjtMoisutre;
  ObjtMoisutre["unit"] = "%";
  ObjtMoisutre["value"] = measurement[MOISTURE];

  serializeJson(ObjtMoisutre, bufferMoisture);

  if(magnitude == TEMPERATURE){
    if (millis() > lastMsg[TEMPERATURE] + timeout) {
    lastMsg[TEMPERATURE] = millis(); 
    client.publish("sensor/DHT22/temperature", bufferTemperature);
  }
  }
  
  if(magnitude == MOISTURE){
    if (millis() > lastMsg[MOISTURE] + timeout) {
    lastMsg[MOISTURE] = millis(); 
    client.publish("sensor/DHT22/moisture", bufferMoisture);
  }
  }
  
  if(magnitude == ALL){
    if (millis() > lastMsg[ALL] + timeout) {
    lastMsg[ALL] = millis(); 
    client.publish("sensor/DHT22/temperature", bufferTemperature);
    client.publish("sensor/DHT22/moisture", bufferMoisture);
  }
  }
}


void SensorDHT22::callbackTopic(char *topic, byte *message, unsigned int length)
{
  String Message;
  for (int i = 0; i < length; i++)
  {
    Message += (char)message[i];
  }

  if (!strcmp(topic, "sensor/DHT22/temperature_min"))
  {
    if (Message.toInt())
    {
      temperatureMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/DHT22/temperature_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/DHT22/temperature_max"))
  {
    if (Message.toInt())
    {
      temperatureMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/DHT22/temperature_max", "The number must to be gratear than 0");
    }
  }

  
  if (!strcmp(topic, "sensor/DHT22/moisture_min"))
  {
    if (Message.toInt() > 0)
    {
      moistureMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/DHT22/moisture_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/DHT22/moisture_max"))
  {
    if (Message.toInt() > 0)
    {
      moistureMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/DHT22/moisture_max", "The number must to be gratear than 0");
    }
  }
}

void SensorDHT22::callbackSubscribe()
{
  client.subscribe("sensor/DHT22/temperature_min");
  client.subscribe("sensor/DHT22/temperature_max");
  client.subscribe("sensor/DHT22/moisture_min");
  client.subscribe("sensor/DHT22/moisture_max");
  client.subscribe("debug/sensor/DHT22/temperature_min");
  client.subscribe("debug/sensor/DHT22/temperature_max");
  client.subscribe("debug/sensor/DHT22/moisture_min");
  client.subscribe("debug/sensor/DHT22/moisture_max");
}
