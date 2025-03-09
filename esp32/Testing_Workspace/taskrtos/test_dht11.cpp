// test_dht11.cpp
#include "test_dht11.h"

DHT dht(DHTPIN, DHTTYPE);

void initDHT11() {
    Serial.println("Initializing DHT11...");
    dht.begin();
}

void readDHT11() {
    delay(2000);
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT11 sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
}
