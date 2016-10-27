#include <Arduino.h>
#include <Wire.h>

// +--[WIRING PINS]-----------------------------------------------------------+
#define PIN_LED 13
#define PIN_SCL A5
#define PIN_SDA A4
#define PIN_GPIO_0 A3
#define PIN_INT A2
#define PIN_TRIGGER A6

// +--[I2C HELPERS]-----------------------------------------------------------+

#define VL6180X_I2C_ADDRESS 0x29

uint8_t read_from_vl6180x(uint16_t reg_addr, boolean send_stop)
{
    Wire.beginTransmission(VL6180X_I2C_ADDRESS);
    Wire.write(0xFF & (reg_addr >> 0x8));
    Wire.write(0xFF & reg_addr);
    Wire.endTransmission(false);
    Wire.requestFrom(VL6180X_I2C_ADDRESS, 1, send_stop);
    while (!Wire.available()) {
    }
    return Wire.read();
}

uint8_t read_from_vl6180x_range(uint16_t start_addr, boolean send_stop, uint8_t *buffer,
                                size_t buffer_len)
{
    Wire.beginTransmission(VL6180X_I2C_ADDRESS);
    Wire.write(0xFF & (start_addr >> 0x8));
    Wire.write(0xFF & start_addr);
    Wire.endTransmission(false);
    Wire.requestFrom(VL6180X_I2C_ADDRESS, buffer_len, send_stop);
    size_t bytes_read = 0;
    for (; bytes_read < buffer_len; ++bytes_read) {
        while (!Wire.available()) {
        }
        buffer[bytes_read] = Wire.read();
    }
    return bytes_read;
}

void write_to_vl6180x(uint16_t reg_addr, uint8_t value, boolean send_stop)
{
    Wire.beginTransmission(VL6180X_I2C_ADDRESS);
    Wire.write(0xFF & (reg_addr >> 0x8));
    Wire.write(0xFF & reg_addr);
    Wire.write(value);
    Wire.endTransmission(send_stop);
}

void write_to_vl6180x_16(uint16_t reg_addr, uint16_t value, boolean send_stop)
{
    Wire.beginTransmission(VL6180X_I2C_ADDRESS);
    Wire.write(0xFF & (reg_addr >> 0x8));
    Wire.write(0xFF & reg_addr);
    Wire.write(0xFF & (value >> 0x8));
    Wire.write(0xFF & value);
    Wire.endTransmission(send_stop);
}

// +--[VL6180X INTERFACE]-----------------------------------------------------+
#define VL6180X_REG_IDENTIFICATION__MODEL_ID 0x000

#define VL6180X_REG_SYSTEM_MODE_GPIO1 0x011
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG_GPIO 0x014
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR 0x015
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET 0x016
#define VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD 0x017

#define VL6180X_REG_SYSRANGE_START 0x018
#define VL6180X_REG_SYSRANGE_THRESH_LOW 0x01A
#define VL6180X_REG_SYSRANGE_INTERMEASUREMENT_PERIOD 0x01B
#define VL6180X_REG_SYSRANGE_MAX_CONVERGENCE_TIME 0x01C
#define VL6180X_REG_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE 0x022

#define VL6180X_REG_RESULT_RANGE_STATUS 0x04D
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO 0x04F
#define VL6180X_REG_RESULT_RANGE_VAL 0x062

#define VL6180X_REG_FIRMWARE_BOOTUP 0x119

typedef struct VL6180X_ID_t {
    uint8_t id : 8;
    uint8_t reserved_0 : 5;
    uint8_t model_maj : 3;
    uint8_t reserved_1 : 5;
    uint8_t model_min : 3;
    uint8_t reserved_2 : 5;
    uint8_t mod_maj : 3;
    uint8_t reserved_3 : 5;
    uint8_t mod_min : 3;
    uint8_t man_year : 4;
    uint8_t man_mon : 4;
    uint8_t man_day : 5;
    uint8_t man_phase : 3;
    uint16_t man_time : 16;
} VL6180X_ID __attribute__((packed));

void vl6180x_emit_version()
{
    VL6180X_ID id;
    memset(&id, 0, sizeof(id));
    read_from_vl6180x_range(VL6180X_REG_IDENTIFICATION__MODEL_ID, true, (uint8_t *)&id, sizeof(id));
    Serial.print("VL6180X{ id: ");
    Serial.print(id.id);
    Serial.print(", model : ");
    Serial.print(id.model_maj);
    Serial.print('.');
    Serial.print(id.model_min);
    Serial.print(", module : ");
    Serial.print(id.mod_maj);
    Serial.print('.');
    Serial.print(id.model_min);
    Serial.println(", manufactured { ");
    Serial.print("    year : ");
    Serial.print(id.man_year);
    Serial.print(", month : ");
    Serial.print(id.man_mon);
    Serial.print(", day : ");
    Serial.print(id.man_day);
    Serial.print(", phase : ");
    Serial.print(id.man_phase);
    Serial.print(", time : ");
    Serial.print(id.man_time);
    Serial.println(" }}");
}

void vl6180x_setup_for_range()
{
    while (!(0x1 & read_from_vl6180x(VL6180X_REG_RESULT_RANGE_STATUS, true))) {
        delay(1);
    }
    write_to_vl6180x(VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD, 0x1, false);

    write_to_vl6180x(VL6180X_REG_SYSTEM_MODE_GPIO1, 0x10, false);
    write_to_vl6180x(VL6180X_REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x01, false);
    write_to_vl6180x(VL6180X_REG_SYSRANGE_THRESH_LOW, 50, false);
    write_to_vl6180x(VL6180X_REG_SYSRANGE_MAX_CONVERGENCE_TIME, 30, false);
    write_to_vl6180x(VL6180X_REG_SYSRANGE_INTERMEASUREMENT_PERIOD, 10, false);
    write_to_vl6180x_16(VL6180X_REG_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 204, false);

    write_to_vl6180x(VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD, 0x0, false);

    write_to_vl6180x(VL6180X_REG_SYSRANGE_START, 0x03, true);
}

static const char *const VL6180X_ERR_0000 = "No error";
static const char *const VL6180X_ERR_0001 = "VCSEL Continuity Test";
static const char *const VL6180X_ERR_0010 = "VCSEL Watchdog Test";
static const char *const VL6180X_ERR_0011 = "VCSEL Watchdog";
static const char *const VL6180X_ERR_0100 = "PLL1 Lock";
static const char *const VL6180X_ERR_0101 = "PLL2 Lock";
static const char *const VL6180X_ERR_0110 = "Early Convergence Estimate";
static const char *const VL6180X_ERR_0111 = "Max Convergence";
static const char *const VL6180X_ERR_1000 = "No Target Ignore";
static const char *const VL6180X_ERR_1001 = "Not used";
static const char *const VL6180X_ERR_1010 = "Not used";
static const char *const VL6180X_ERR_1011 = "Max Signal To Noise Ratio";
static const char *const VL6180X_ERR_1100 = "Raw Ranging Algo Underflow";
static const char *const VL6180X_ERR_1101 = "Raw Ranging Algo Overflow";
static const char *const VL6180X_ERR_1110 = "Ranging Algo Underflow";
static const char *const VL6180X_ERR_1111 = "Ranging Algo Overflow";
static const char *const VL6180X_ERR_XXXX = "(unknown)";

const char *vl6180x_get_error(uint8_t error)
{
    switch (error) {
    case 0:
        return VL6180X_ERR_0000;
    case 1:
        return VL6180X_ERR_0001;
    case 2:
        return VL6180X_ERR_0010;
    case 3:
        return VL6180X_ERR_0011;
    case 4:
        return VL6180X_ERR_0100;
    case 5:
        return VL6180X_ERR_0101;
    case 6:
        return VL6180X_ERR_0110;
    case 7:
        return VL6180X_ERR_0111;
    case 8:
        return VL6180X_ERR_1000;
    case 9:
        return VL6180X_ERR_1001;
    case 10:
        return VL6180X_ERR_1010;
    case 11:
        return VL6180X_ERR_1011;
    case 12:
        return VL6180X_ERR_1100;
    case 13:
        return VL6180X_ERR_1101;
    case 14:
        return VL6180X_ERR_1110;
    case 15:
        return VL6180X_ERR_1111;
    default:
        return VL6180X_ERR_XXXX;
    }
}

void vl6180x_wait_for_standby()
{
    digitalWrite(PIN_LED, HIGH);
    while (!read_from_vl6180x(VL6180X_REG_FIRMWARE_BOOTUP, true)) {
        digitalWrite(PIN_LED, LOW);
        delay(500);
        digitalWrite(PIN_LED, HIGH);
    }
    while (!read_from_vl6180x(VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET, true)) {
        digitalWrite(PIN_LED, LOW);
        delay(500);
        digitalWrite(PIN_LED, HIGH);
    }
    digitalWrite(PIN_LED, LOW);
    delay(100);
    digitalWrite(PIN_LED, HIGH);
    write_to_vl6180x(VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET, 0x00, true);
    digitalWrite(PIN_LED, LOW);
}

// +--[FIRMWARE]--------------------------------------------------------------+
void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_GPIO_0, INPUT_PULLUP);
    pinMode(PIN_INT, INPUT_PULLUP);
    pinMode(PIN_TRIGGER, OUTPUT);
    digitalWrite(PIN_TRIGGER, LOW);
    Serial.begin(115200);
    Wire.setSDA(PIN_SDA);
    Wire.setSCL(PIN_SCL);
    Wire.begin();
}

int main()
{
    setup();

    digitalWrite(PIN_TRIGGER, HIGH);

    vl6180x_wait_for_standby();

    digitalWrite(PIN_LED, HIGH);
    vl6180x_setup_for_range();
    digitalWrite(PIN_LED, LOW);

    delay(100);

    digitalWrite(PIN_LED, HIGH);
    vl6180x_emit_version();
    digitalWrite(PIN_LED, LOW);

    digitalWrite(PIN_TRIGGER, LOW);

    while (1) {
        delay(10);
        digitalWrite(PIN_LED, HIGH);
        const uint8_t int_status =
            read_from_vl6180x(VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO, true);
        if (int_status & 1) {
            write_to_vl6180x(VL6180X_REG_SYSTEM_INTERRUPT_CLEAR, 1, true);
            Serial.println("NEAR.");
        }
        else {
            const uint8_t status = read_from_vl6180x(VL6180X_REG_RESULT_RANGE_STATUS, true);
            if (!(0xF0 & status)) {
                Serial.print("RANGE: ");
                Serial.println(read_from_vl6180x(VL6180X_REG_RESULT_RANGE_VAL, true));
            }
            else {
                Serial.print("ERROR: ");
                Serial.println(vl6180x_get_error(status >> 4));
            }
        }
        digitalWrite(PIN_LED, LOW);
    }
}
