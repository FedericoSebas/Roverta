#include "BMP280.h"

BMP280::BMP280(Mqtt &defaulClient) : Sensor(defaulClient, -1),Adafruit_BMP280() {
  begin(0x76);
}

int BMP280::getMeasurement(int magnitude)
{
  return measurement[magnitude];
}

void BMP280::measure(int magnitude)
{
  if(magnitude == TEMPERATURE){
    measurement[TEMPERATURE] = readTemperature();
  }
  else if(magnitude == PRESSURE){
    measurement[PRESSURE] = readPressure();
  }
  else if(magnitude == ALTITUDE){
    measurement[ALTITUDE] = readAltitude(1013.25);
  }
  else if(magnitude == ALL){
    measurement[TEMPERATURE] = readTemperature();
    measurement[PRESSURE] = readPressure();
    measurement[ALTITUDE] = readAltitude(1013.25);
  }
}


void BMP280::publishMeasurement(int magnitude,int timeout)
{
  StaticJsonDocument<200> ObjtTemperature;
  ObjtTemperature["unit"] = "ºC";
  ObjtTemperature["value"] = measurement[TEMPERATURE];

  serializeJson(ObjtTemperature, bufferTemperature);

  StaticJsonDocument<200> ObjtPressure;
  ObjtPressure["unit"] = "hPa";
  ObjtPressure["value"] = measurement[PRESSURE];

  serializeJson(ObjtPressure, bufferPressure);
  
  StaticJsonDocument<200> ObjtAltitude;
  ObjtAltitude["unit"] = "MASL";
  ObjtAltitude["value"] = measurement[ALTITUDE];

  serializeJson(ObjtAltitude, bufferAltitude);
  
  

  if(magnitude == TEMPERATURE){
    if (millis() > lastMsgBMP280[TEMPERATURE] + timeout) {
    lastMsgBMP280[TEMPERATURE] = millis(); 
    client.publish("sensor/bmp280/temperature", bufferTemperature);
  }
  }
  
  if(magnitude == PRESSURE){
    if (millis() > lastMsgBMP280[PRESSURE] + timeout) {
    lastMsgBMP280[PRESSURE] = millis(); 
    client.publish("sensor/bmp280/pressure", bufferPressure);
  }
  if(magnitude == ALTITUDE){
    if (millis() > lastMsgBMP280[ALTITUDE] + timeout) {
    lastMsgBMP280[ALTITUDE] = millis(); 
    client.publish("sensor/bmp280/altitude", bufferAltitude);
  }
  }
  if(magnitude == ALL){
    if (millis() > lastMsgBMP280[ALL] + timeout) {
    lastMsgBMP280[ALL] = millis(); 
    client.publish("sensor/bmp280/temperature", bufferTemperature);
    client.publish("sensor/bmp280/pressure", bufferPressure);
    client.publish("sensor/bmp280/altitude", bufferAltitude);
  }
  }
}
}

void BMP280::callbackTopic(char *topic, byte *message, unsigned int length)
{
  String Message;
  for (int i = 0; i < length; i++)
  {
    Message += (char)message[i];
  }

  if (!strcmp(topic, "sensor/bmp280/temperature_min"))
  {
    if (Message.toFloat() > 0)
    {
      temperatureMin = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/temperature_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/bmp280/temperature_max"))
  {
    if (Message.toFloat() > 0)
    {
      temperatureMax = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/temperature_max", "The number must to be gratear than 0");
    }
  }

  
  if (!strcmp(topic, "sensor/bmp280/pressure_min"))
  {
    if (Message.toFloat() > 0)
    {
      pressureMin = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/pressure_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/bmp280/pressure_max"))
  {
    if (Message.toFloat() > 0)
    {
      pressureMax = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/pressure_max", "The number must to be gratear than 0");
    }
  }
  

  if (!strcmp(topic, "sensor/bmp280/altitude_min"))
  {
    if (Message.toFloat() > 0)
    {
      altitudeMin = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/altitude_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/bmp280/altitude_max"))
  {
    if (Message.toFloat() > 0)
    {
      altitudeMax = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/bmp280/altitude_max", "The number must to be gratear than 0");
    }
  }
}

void BMP280::callbackSubscribe()
{
  client.subscribe("sensor/bmp280/temperature_min");
  client.subscribe("sensor/bmp280/temperature_max");
  client.subscribe("sensor/bmp280/pressure_min");
  client.subscribe("sensor/bmp280/pressure_max");
  client.subscribe("sensor/bmp280/altitude_min");
  client.subscribe("sensor/bmp280/altitude_max");
  client.subscribe("debug/sensor/bmp280/temperature_min");
  client.subscribe("debug/sensor/bmp280/temperature_max");
  client.subscribe("debug/sensor/bmp280/pressure_min");
  client.subscribe("debug/sensor/bmp280/pressure_max");
  client.subscribe("debug/sensor/bmp280/altitude_min");
  client.subscribe("debug/sensor/bmp280/altitude_max");
}
