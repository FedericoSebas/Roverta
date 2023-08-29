#include "LDR.h"

LDR::LDR(Mqtt &defaulClient, int pin) : Sensor(defaulClient, pin) {}

int LDR::getMeasurement()
{
  return luxPercentage;
}

void LDR::measure()
{
  analogValue = analogRead(pin);
  voltage = analogValue / 4095. * 5;
  resistance = 2000 * voltage / (1 - voltage / 5);
  lux = pow(rl10 * 1e3 * pow(10, gamma) / resistance, (1 / gamma));
  luxPercentage = map(round(lux), luxMin, luxMax, 0, 100);
  if (luxPercentage > luxMax)
  {
    luxPercentage = 100;
  }
}

void LDR::publishMeasurement()
{
  StaticJsonDocument<200> ObjtLuxPercentage;
  ObjtLuxPercentage["unit"] = "lux percent/s";
  ObjtLuxPercentage["value"] = luxPercentage;

  serializeJson(ObjtLuxPercentage, bufferLuxPercentage);

  client.publish("sensor/ldr/lux", bufferLuxPercentage);
}

void LDR::callbackTopic(char *topic, byte *message, unsigned int length)
{
  String Message;
  for (int i = 0; i < length; i++)
  {
    Message += (char)message[i];
  }

  if (!strcmp(topic, "sensor/ldr/rl10"))
  {
    if (Message.toFloat() > 0)
    {
      rl10 = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/ldr/rl10", "The number must to be gratear than 0");
    }
  }

  if (!strcmp(topic, "sensor/ldr/gamma"))
  {
    if (Message.toFloat() > 0)
    {
      gamma = Message.toFloat();
    }
    else
    {
      client.publish("debug/sensor/ldr/gamma", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/ldr/lux_min"))
  {
    if (Message.toInt() > 0)
    {
      luxMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/ldr/lux_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/ldr/lux_max"))
  {
    if (Message.toInt() > 0)
    {
      luxMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/ldr/lux_max", "The number must to be gratear than 0");
    }
  }
}

void LDR::callbackSubscribe()
{
  client.subscribe("sensor/ldr/rl10");
  client.subscribe("sensor/ldr/gamma");
  client.subscribe("sensor/ldr/lux_min");
  client.subscribe("sensor/ldr/lux_max");
  client.subscribe("debug/sensor/ldr/rl10");
  client.subscribe("debug/sensor/ldr/gamma");
  client.subscribe("debug/sensor/ldr/lux_min");
  client.subscribe("debug/sensor/ldr/lux_max");
}