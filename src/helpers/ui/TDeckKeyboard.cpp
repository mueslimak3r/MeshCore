#include "TDeckKeyboard.h"

TDeckKeyboard::TDeckKeyboard() {
    // Initialize keyboard
    Wire.beginTransmission(LILYGO_KB_SLAVE_ADDRESS);
    if (Wire.endTransmission() == 0) {
        keyboard_available = true;
        Serial.println("T-Deck keyboard found!");

        // Set initial keyboard brightness
        setKeyboardDefaultBrightness(127);
        setKeyboardBrightness(200);
    } else {
        Serial.println("T-Deck keyboard not found!");
    }
}

void TDeckKeyboard::setKeyboardBrightness(uint8_t value) {
  Serial.println("Setting keyboard brightness to " + String(value));
  if (!keyboard_available) {
    Serial.println("ERR: Cant set keyboard brightness, keyboard not available");
    return;
  }

  Wire.beginTransmission(LILYGO_KB_SLAVE_ADDRESS);
  Wire.write(LILYGO_KB_BRIGHTNESS_CMD);
  Wire.write(value);
  Wire.endTransmission();
}

void TDeckKeyboard::setKeyboardDefaultBrightness(uint8_t value) {
    Wire.beginTransmission(LILYGO_KB_SLAVE_ADDRESS);
    Wire.write(LILYGO_KB_BRIGHTNESS_CMD);
    Wire.write(value);
    Wire.endTransmission();
}

void TDeckKeyboard::getKeyPress() {
    static bool was_pressed = false;
    uint32_t current_time = millis();
    // Read key from keyboard
    char keyValue = 0;
    Wire.requestFrom(LILYGO_KB_SLAVE_ADDRESS, 1);
    if (Wire.available() > 0) {
        keyValue = Wire.read();

        if (keyValue != 0) {
        // Check if this is a new key press or key has been held long enough for
        // repeat
        if (!was_pressed || (last_key_code != keyValue) ||
            (current_time - last_key_time > 30)) {
                last_key_code = keyValue;
                last_key_time = current_time;
                key_is_new = true;
                was_pressed = true;

                Serial.print("Key registered: ");
                Serial.print(keyValue);
                Serial.print(" (");
                Serial.print((int)keyValue);
                Serial.println(")");
            }
        } else {
            was_pressed = false;
        }
    }
}