#ifndef DHT22_H
#define DHT22_H

#include "Sensor.h"
#include <ArduinoJson.h>
#include "Arduino.h"
#include <DHT.h>


#define TEMPERATURE_MAX_DHT 25
#define TEMPERATURE_MIN_DHT 16
#define MOISTURE_MAX_DHT 80
#define MOISTURE_MIN_DHT 20


class SensorDHT22 : public Sensor, public DHT
{
private:
  int measurement[2];
  int temperatureMax = TEMPERATURE_MAX_DHT;
  int temperatureMin = TEMPERATURE_MIN_DHT;
  int moistureMax = MOISTURE_MAX_DHT;
  int moistureMin = MOISTURE_MIN_DHT;

  char bufferMoisture[520];
  char bufferTemperature[520];
  
  long unsigned lastMsg[4] = {0,0,0,0};

public:
//***functions not used***

int getMeasurement(){return 0;}

  void measure(){}

  void publishMeasurement(int timeout){}

//end

  SensorDHT22(Mqtt &defaulClient, int pin);

  int getMeasurement(int magnitude);
  
  void measure(int magnitude);

  void publishMeasurement(int magnitude,int timeout);

  void callbackTopic(char *topic, byte *message, unsigned int length);

  void callbackSubscribe();
};
#endif
