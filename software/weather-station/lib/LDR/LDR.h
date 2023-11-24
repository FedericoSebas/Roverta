#ifndef LDR_H
#define LDR_H

#include "Sensor.h"
#include <ArduinoJson.h>
#include "Mqtt.h"
#include "Arduino.h"

#define GAMMA 0.7
#define RL10 360
#define LUX_MIN 0
// #define LUX_MAX 100000
#define LUX_MAX 400

class LDR : public Sensor
{
private:
  volatile float rl10 = RL10;
  volatile float gamma = GAMMA;
  volatile float analogValue;
  volatile float voltage;
  volatile float resistance;
  volatile float lux;
  volatile int luxPercentage;
  volatile int luxMin = LUX_MIN;
  volatile int luxMax = LUX_MAX;

  long unsigned lastMsg = 0;

  char bufferLuxPercentage[520];

public:
//***functions not used***
int getMeasurement(int magnitude){return 0;}

  void measure(int magnitude){}

  void publishMeasurement(int magnitude, int timeout){}
// end


  LDR(Mqtt &defaulClient, int pin);

  int getMeasurement();

  void measure();

  void publishMeasurement(int timeout);

  void callbackTopic(char *topic, byte *message, unsigned int length);

  void callbackSubscribe();
};
#endif