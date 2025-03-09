// read_dht11.cpp
#include "read_dht11.h"

DHT dht(DHTPIN, DHTTYPE);

float room_temp;
float room_humid;

float buffer_temp;
float buffer_humid;

int dht11_status;

void initDHT11() {
    Serial.println("Initializing DHT11...");
    dht.begin();
}

void readDHT11() {
    buffer_temp = dht.readTemperature();
    buffer_humid = dht.readHumidity();

    if (isnan(buffer_temp) || isnan(buffer_humid)) {
      // Serial.println("Failed to read from DHT11 sensor!");
      dht11_status = false;
      return;
    }
    room_temp = buffer_temp;
    room_humid = buffer_humid; 
    dht11_status = true;

    // Serial.print("Temperature: ");
    // Serial.print(room_temp);
    // Serial.print(" °C | Humidity: ");
    // Serial.print(room_humid);
    // Serial.println(" %");
}
