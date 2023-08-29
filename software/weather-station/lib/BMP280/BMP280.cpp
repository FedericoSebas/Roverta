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
  if(magnitude == TEMPERATURE_BMP){
    measurement[TEMPERATURE_BMP] = readTemperature();
  }
  else if(magnitude == PRESSURE_BMP){
    measurement[PRESSURE_BMP] = readPressure();
  }
  else if(magnitude == ALTITUDE_BMP){
    measurement[ALTITUDE_BMP] = readAltitude(1013.25);
  }
  else if(magnitude == ALL_BMP){
    measurement[TEMPERATURE_BMP] = readTemperature();
    measurement[PRESSURE_BMP] = readPressure();
    measurement[ALTITUDE_BMP] = readAltitude(1013.25);
  }
}


void BMP280::publishMeasurement(int magnitude,int timeout)
{
  StaticJsonDocument<200> ObjtTemperature;
  ObjtTemperature["unit"] = "ºC";
  ObjtTemperature["value"] = measurement[TEMPERATURE_BMP];

  serializeJson(ObjtTemperature, bufferTemperature);

  StaticJsonDocument<200> ObjtPressure;
  ObjtPressure["unit"] = "hPa";
  ObjtPressure["value"] = measurement[PRESSURE_BMP];

  serializeJson(ObjtPressure, bufferPressure);
  
  StaticJsonDocument<200> ObjtAltitude;
  ObjtAltitude["unit"] = "MASL";
  ObjtAltitude["value"] = measurement[ALTITUDE_BMP];

  serializeJson(ObjtAltitude, bufferAltitude);
  
  

  if(magnitude == TEMPERATURE_BMP){
    if (millis() > lastMsgBMP280[TEMPERATURE_BMP] + timeout) {
    lastMsgBMP280[TEMPERATURE_BMP] = millis(); 
    client.publish("sensor/bmp280/temperature", bufferTemperature);
  }
  }
  
  if(magnitude == PRESSURE_BMP){
    if (millis() > lastMsgBMP280[PRESSURE_BMP] + timeout) {
    lastMsgBMP280[PRESSURE_BMP] = millis(); 
    client.publish("sensor/bmp280/pressure", bufferPressure);
  }
  if(magnitude == ALTITUDE_BMP){
    if (millis() > lastMsgBMP280[ALTITUDE_BMP] + timeout) {
    lastMsgBMP280[ALTITUDE_BMP] = millis(); 
    client.publish("sensor/bmp280/altitude", bufferAltitude);
  }
  }
  if(magnitude == ALL_BMP){
    if (millis() > lastMsgBMP280[ALL_BMP] + timeout) {
    lastMsgBMP280[ALL_BMP] = millis(); 
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
