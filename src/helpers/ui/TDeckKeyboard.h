#include <Arduino.h>
#include <Wire.h>
#include "helpers/ESP32Board.h"
#include <driver/rtc_io.h>

#define LILYGO_KB_SLAVE_ADDRESS 0x55
#define LILYGO_KB_BRIGHTNESS_CMD 0x01
#define LILYGO_KB_ALT_B_BRIGHTNESS_CMD 0x02

#define PIN_I2C_SDA 18
#define PIN_I2C_SCL 8

class TDeckKeyboard {
    public:
        TDeckKeyboard();
        void setKeyboardDefaultBrightness(uint8_t value);
        void setKeyboardBrightness(uint8_t value);
        void getKeyPress();
    private:
        uint32_t last_key_code = 0;
        bool key_is_new = false;
        uint32_t last_key_time = 0;
        bool keyboard_available = false;
};