#include "DHT11.h"

SensorDHT11::SensorDHT11(Mqtt &defaulClient, int pin) : Sensor(defaulClient, pin),DHT (pin, DHT11){}

int SensorDHT11::getMeasurement(int magnitude)
{
  return measurement[magnitude];
}

void SensorDHT11::measure(int magnitude)
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

void SensorDHT11::publishMeasurement(int magnitude,int timeout)
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
    if (millis() > lastMsgDHT11[TEMPERATURE] + timeout) {
    lastMsgDHT11[TEMPERATURE] = millis(); 
    client.publish("sensor/dht11/temperature", bufferTemperature);
  }
  }
  
  if(magnitude == MOISTURE){
    if (millis() > lastMsgDHT11[MOISTURE] + timeout) {
    lastMsgDHT11[MOISTURE] = millis(); 
    client.publish("sensor/dht11/moisture", bufferMoisture);
  }
  }
  
  if(magnitude == ALL){
    if (millis() > lastMsgDHT11[ALL] + timeout) {
    lastMsgDHT11[ALL] = millis(); 
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
