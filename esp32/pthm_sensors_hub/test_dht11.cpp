// test_dht11.cpp
#include "test_dht11.h"

DHT dht(DHTPIN, DHTTYPE);
float room_temp;
float room_humid;
int dht11_status;

void initDHT11() {
    Serial.println("Initializing DHT11...");
    dht.begin();
}

void readDHT11() {
    room_temp = dht.readTemperature();
    room_humid = dht.readHumidity();

    if (isnan(room_temp) || isnan(room_humid)) {
        Serial.println("Failed to read from DHT11 sensor!");
        dht11_status = false;
        return;
    }
    dht11_status = true;

    // Serial.print("Temperature: ");
    // Serial.print(room_temp);
    // Serial.print(" °C | Humidity: ");
    // Serial.print(room_humid);
    // Serial.println(" %");
}
