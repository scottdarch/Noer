#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

#define PIN_LED  13
#define PIN_SCLK 14
#define PIN_CS   A1
#define PIN_RDY  25
#define PIN_INT  24

SPISettings isd2360_spi_settings(400000, MSBFIRST, SPI_MODE3);
SdFatSdio sd;

#define ISD2360_REG_SPI_SND_DEC   0xC0
#define ISD2360_REG_SPI_VOICE_PLY 0xA6
#define ISD2360_REG_SPI_DIG_WRITE 0xA0
#define ISD2360_REG_SPI_CFG_WRITE 0xB8
#define ISD2360_REG_SPI_CFG_READ  0xBA
#define ISD2360_REG_STOP          0x2A
#define ISD2360_REG_READ_STATUS   0x40
#define ISD2360_REG_READ_INT      0x46
#define ISD2360_REG_READ_ID       0x48
#define ISD2360_REG_PWR_UP        0x10
#define ISD2360_REG_PWR_DN        0x12
#define ISD2360_REG_RESET         0x14

#define ISD2360_REG_PATH_CONTROL  0x02
#define ISD2360_REG_VOL_CONTROL   0x03

#define ISD2360_START_OF_VP       0x00400


void stream_voice(const char* sd_file) {
    auto ad4file = sd.open(sd_file, O_READ);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_SPI_SND_DEC);
    uint8_t bb = 0;
    while(1 == ad4file.read(&bb, 1)) {
        SPI.transfer(bb);
    }
    SPI.transfer(ISD2360_REG_STOP);
    digitalWrite(PIN_CS, HIGH);
}

static void write_to_register(uint8_t register_addr, uint8_t* buffer, size_t buffer_len) {
    SPI.transfer(ISD2360_REG_SPI_CFG_WRITE);
    SPI.transfer(register_addr);
    SPI.transfer(buffer, buffer_len);
}

static uint8_t read_from_register(uint8_t register_addr) {
    SPI.transfer(ISD2360_REG_SPI_CFG_READ);
    SPI.transfer(register_addr);
    return SPI.transfer(0x00);
}

static void write_application(const char* image_map_file) {
    auto image_map = sd.open(image_map_file, O_READ);

    digitalWrite(PIN_CS, LOW);
    uint8_t cmd_and_addr[4] = {ISD2360_REG_SPI_DIG_WRITE,
                            0x00, 0x00, 0x00 };
    SPI.transfer(cmd_and_addr, 4);
    uint8_t bb = 0;
    while(1 == image_map.read(&bb, 1)) {
        SPI.transfer(bb);
    }
    digitalWrite(PIN_CS, HIGH);
}

static void play_voice(uint16_t index) {

    uint8_t buffer[3] = {ISD2360_REG_SPI_VOICE_PLY,
                         0xFF & (index >> 8),
                         0xFF & index};
    SPI.transfer(buffer, 3);
}

// +--[FIRMWARE]--------------------------------------------------------------+
void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_RDY, INPUT);
    pinMode(PIN_INT, INPUT_PULLUP);
    digitalWrite(PIN_CS, HIGH);

    Serial.begin(115200);
    SPI.setSCK(PIN_SCLK);
    SPI.begin();
    SPI.beginTransaction(isd2360_spi_settings);
    sd.begin();
}

void program_image() {
    // ID
    digitalWrite(PIN_LED, HIGH);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_DN);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_RESET);
    digitalWrite(PIN_CS, HIGH);

    delay(500);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_UP);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    uint8_t buffer[4] = {ISD2360_REG_READ_ID, 0x0, 0x0, 0x0};
    SPI.transfer(buffer, 4);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    // Status
    digitalWrite(PIN_CS, LOW);
    uint8_t stat_buffer[2] = {ISD2360_REG_READ_STATUS, 0x0};
    SPI.transfer(stat_buffer, 2);
    digitalWrite(PIN_CS, HIGH);

    write_application("MemMap.map");

    while(1) {
        digitalWrite(PIN_LED, HIGH);
        delay(500);
        digitalWrite(PIN_LED, LOW);
        delay(1000);

    }
}

void play_dog() {

    // ID
    digitalWrite(PIN_LED, HIGH);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_DN);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_RESET);
    digitalWrite(PIN_CS, HIGH);

    delay(500);

    digitalWrite(PIN_CS, LOW);
    SPI.transfer(ISD2360_REG_PWR_UP);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    uint8_t buffer[4] = {ISD2360_REG_READ_ID, 0x0, 0x0, 0x0};
    SPI.transfer(buffer, 4);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    // Status
    digitalWrite(PIN_CS, LOW);
    uint8_t stat_buffer[2] = {ISD2360_REG_READ_STATUS, 0x0};
    SPI.transfer(stat_buffer, 2);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    uint8_t path = 0x44;
    write_to_register(ISD2360_REG_PATH_CONTROL, &path, 1);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    read_from_register(ISD2360_REG_PATH_CONTROL);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    uint8_t volume = 0x0;
    write_to_register(ISD2360_REG_VOL_CONTROL, &volume, 1);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_CS, LOW);
    read_from_register(ISD2360_REG_VOL_CONTROL);
    digitalWrite(PIN_CS, HIGH);

    delay(1);

    digitalWrite(PIN_LED, LOW);
    delay(500);

    while(1) {
        digitalWrite(PIN_LED, HIGH);
        digitalWrite(PIN_CS, LOW);
        play_voice(3);
        digitalWrite(PIN_CS, HIGH);
        digitalWrite(PIN_LED, LOW);
        delay(2000);

    }

}

int main()
{
    setup();

    delay(1000);

    //program_image();
    play_dog();
}
