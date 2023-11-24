#include "PD.h"

PD::PD(Mqtt &defaulClient, int pin) : Sensor(defaulClient, pin) {}

int PD::getMeasurement()
{
  return irPercentage;
}

void PD::measure()
{
  ir = analogRead(pin);
  irPercentage = map(ir, irMin, irMax, 0, 100);      
}

void PD::publishMeasurement(int timeout)
{
  StaticJsonDocument<200> ObjtIrPercentage;
  ObjtIrPercentage["unit"] = "%";
  ObjtIrPercentage["value"] = irPercentage;

  serializeJson(ObjtIrPercentage, bufferLuxPercentage);

  if(millis() > lastMsg + timeout){
    lastMsg = millis();
    client.publish("sensor/pd/ir", bufferLuxPercentage);
  }
}

void PD::callbackTopic(char *topic, byte *message, unsigned int length)
{
  String Message;
  for (int i = 0; i < length; i++)
  {
    Message += (char)message[i];
  }
  if (!strcmp(topic, "sensor/pd/ir_min"))
  {
    if (Message.toInt() > 0)
    {
      irMin = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/pd/ir_min", "The number must to be gratear than 0");
    }
  }
  if (!strcmp(topic, "sensor/pd/ir_max"))
  {
    if (Message.toInt() > 0)
    {
      irMax = Message.toInt();
    }
    else
    {
      client.publish("debug/sensor/pd/ir_max", "The number must to be gratear than 0");
    }
  }
}

void PD::callbackSubscribe()
{
  client.subscribe("sensor/pd/ir_min");
  client.subscribe("sensor/pd/ir_max");
  client.subscribe("debug/sensor/pd/ir_min");
  client.subscribe("debug/sensor/pd/ir_max");
}