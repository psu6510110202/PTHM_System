// test_dht11.h
#ifndef TEST_DHT11_H
#define TEST_DHT11_H

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 14  // Define the pin where the DHT11 sensor is connected
#define DHTTYPE DHT11

void initDHT11();
void readDHT11();

#endif