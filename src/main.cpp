#include <Arduino.h>
#include <Wire.h>
#include "gpio.h"
#include "display.h"
#include "i2c_ads.h"

// ESP32-WROVER-E N4R8  C967023

void setup() {
  Wire.begin(I2C1_SDA_PIN, I2C1_SCL_PIN);
  Wire1.begin(I2C2_SDA_PIN, I2C2_SCL_PIN);
  Serial.begin(115200);
  Serial.println("start");
  gpio_init();
  oled_init();
  ads_init();
}

void loop() {
  oled_loop();
  enc_get_key_pressed();
  ads_loop();
  delay(1000);
}
