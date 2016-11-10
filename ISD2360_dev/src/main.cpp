#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

#define PIN_LED  13
#define PIN_SCLK 14
#define PIN_CS   A1

SPISettings isd2360_spi_settings(800000, MSBFIRST, SPI_MODE3);
SdFatSdio sd;

#define ISD2360_REG_SPI_SND_DEC   0xC0
#define ISD2360_REG_STOP          0x2A
#define ISD2360_REG_READ_STATUS   0x40
#define ISD2360_REG_READ_INT      0x46
#define ISD2360_REG_READ_ID       0x48
#define ISD2360_REG_PWR_UP        0x10
#define ISD2360_REG_PWR_DN        0x12

#define ISD2360_REG_PATH_CONTROL  0x02
#define ISD2360_REG_VOL_CONTROL   0x03


void write_voice0() {
    auto ad4file = sd.open("0000.bin", O_READ);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_SPI_SND_DEC);
    uint8_t bb = 0;
    while(1 == ad4file.read(&bb, 1)) {
        SPI.transfer(bb);
    }
    SPI.transfer(ISD2360_REG_STOP);
    digitalWrite(PIN_CS, HIGH);
}

// +--[FIRMWARE]--------------------------------------------------------------+
void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_CS, HIGH);
    Serial.begin(115200);
    SPI.setSCK(PIN_SCLK);
    SPI.begin();
    SPI.beginTransaction(isd2360_spi_settings);
    sd.begin();
}

int main()
{
    setup();

    delay(1500);
    // ID
    digitalWrite(PIN_LED, HIGH);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_UP);
    digitalWrite(PIN_CS, HIGH);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_UP);
    digitalWrite(PIN_CS, HIGH);

    digitalWrite(PIN_CS, LOW);
    uint8_t buffer[4] = {ISD2360_REG_READ_ID, 0x0, 0x0, 0x0};
    SPI.transfer(buffer, 4);
    digitalWrite(PIN_CS, HIGH);

    // Status
    digitalWrite(PIN_CS, LOW);
    uint8_t stat_buffer[2] = {ISD2360_REG_READ_STATUS, 0x0};
    SPI.transfer(stat_buffer, 2);
    digitalWrite(PIN_CS, HIGH);

    digitalWrite(PIN_CS, LOW);
    uint16_t spi_in = (ISD2360_REG_PATH_CONTROL << 8) | 0x64;
    SPI.transfer16(spi_in);
    digitalWrite(PIN_CS, HIGH);

    digitalWrite(PIN_CS, LOW);
    uint16_t max_vol = (ISD2360_REG_VOL_CONTROL << 8) | 0x00;
    SPI.transfer16(max_vol);
    digitalWrite(PIN_CS, HIGH);

    digitalWrite(PIN_LED, LOW);
    delay(500);

    while(1) {
        digitalWrite(PIN_LED, HIGH);
        write_voice0();
        digitalWrite(PIN_LED, LOW);
        delay(1000);

    }
}
