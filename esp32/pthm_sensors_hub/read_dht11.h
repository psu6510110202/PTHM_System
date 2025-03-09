// read_dht11.h
#ifndef READ_DHT11_H
#define READ_DHT11_H

#include <Arduino.h>
#include <DHT.h>

extern float room_temp;
extern float room_humid;
extern int dht11_status;

#define DHTPIN 14  // Define the pin where the DHT11 sensor is connected
#define DHTTYPE DHT11

void initDHT11();
void readDHT11();

#endif