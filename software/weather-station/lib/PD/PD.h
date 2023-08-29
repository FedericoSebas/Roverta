#ifndef PD_H
#define PD_H

#include "Sensor.h"
#include <ArduinoJson.h>
#include "Mqtt.h"
#include "Arduino.h"

#define IR_MIN 0
#define IR_MAX 4095

class PD : public Sensor
{
private:
  int ir;
  int irPercentage;
  int irMin = IR_MIN;
  int irMax = IR_MAX;

  char bufferLuxPercentage[520];

public:
//***functions not used***
  PD(Mqtt &defaulClient, int pin);

  int getMeasurement(int magnitude){return 0;}
  
  void measure(int magnitude){}
  
  void publishMeasurement(int magnitude, int timeout){}
// end

  int getMeasurement();

  void measure();

  void publishMeasurement();

  void callbackTopic(char *topic, byte *message, unsigned int length);

  void callbackSubscribe();
};
#endif

