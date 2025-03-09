#ifndef TEST_DS18B20_H
#define TEST_DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

// Declare OneWire and DallasTemperature objects
extern OneWire oneWire;
extern DallasTemperature sensors;
extern float body_temp;

void initDS18B20();
void readDS18B20();

#endif
