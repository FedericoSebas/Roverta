#ifndef BMP280_H
#define BMP280_H

#include "Sensor.h"
#include <ArduinoJson.h>
#include "Mqtt.h"
#include "Arduino.h"
#include <Adafruit_BMP280.h>


#define TEMPERATURE_MAX_BMP 25
#define TEMPERATURE_MIN_BMP 16
#define PRESSURE_MAX_BMP 1024
#define PRESSURE_MIN_BMP 800
#define ALTITUDE_MAX_BMP 2000
#define ALTITUDE_MIN_BMP 1000


class BMP280 : public Sensor, public Adafruit_BMP280
{
private:
  float measurement[3];
  float temperatureMax = TEMPERATURE_MAX_BMP;
  float temperatureMin = TEMPERATURE_MIN_BMP;
  float pressureMax = PRESSURE_MAX_BMP;
  float pressureMin = PRESSURE_MIN_BMP;
  float altitudeMax = ALTITUDE_MAX_BMP;
  float altitudeMin = ALTITUDE_MIN_BMP;

  
long unsigned lastMsgBMP280[4] = {0,0,0,0};
  
  char bufferTemperature[520];
  char bufferPressure[520];
  char bufferAltitude[520];

public:

//***functions not used***
  int getMeasurement(){return 0;}

  void measure(){}

  void publishMeasurement(){}
// end

  BMP280(Mqtt &defaulClient);

  int getMeasurement(int magnitude);
  
  void measure(int magnitude);

  void publishMeasurement(int magnitude, int timeout);

  void callbackTopic(char *topic, byte *message, unsigned int length);

  void callbackSubscribe();
};
#endif
