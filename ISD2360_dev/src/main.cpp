#include <Arduino.h>
#include <SPI.h>

#define PIN_LED  13
#define PIN_SCLK 14
#define PIN_CS   15

SPISettings isd2360_spi_settings(16000000, MSBFIRST, SPI_MODE3);

// +--[FIRMWARE]--------------------------------------------------------------+
void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    Serial.begin(115200);
    SPI.setSCK(PIN_SCLK);
    SPI.begin();
    SPI.beginTransaction(isd2360_spi_settings);
}

int main()
{
    setup();
    while(1) {
        digitalWrite(PIN_LED, HIGH);
        Serial.println("Hello.");
        digitalWrite(PIN_CS, LOW);
        SPI.transfer(16);
        digitalWrite(PIN_CS, HIGH);
        delay(500);
        digitalWrite(PIN_LED, LOW);
        delay(500);
    }
}
