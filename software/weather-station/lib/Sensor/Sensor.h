#ifndef SENSOR_H
#define SENSOR_H

#include "Mqtt.h"
#include "Arduino.h"

class Sensor
{
  protected:
    int pin;
    Mqtt &client;
  public:
    virtual void measure() = 0;

    virtual void measure(int magnitude) = 0;

    virtual int getMeasurement() = 0;

    virtual int getMeasurement(int magnitude) = 0;

    virtual void publishMeasurement() = 0;

    virtual void publishMeasurement(int magnitude, int timeout) = 0;

    virtual void callbackTopic(char *topic, byte *message, unsigned int length) = 0;

    virtual void callbackSubscribe() = 0;

    Sensor(Mqtt &defaultClient, int pin) : client(defaultClient), pin(pin){}
};

#endif
