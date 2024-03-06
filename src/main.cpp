#include <Arduino.h>
#include <Wire.h>
#include "gpio.h"
#include "onebus_sensor.h"
#include "display.h"
#include "i2c_ads.h"
#include "i2c_dac.h"

// ESP32-WROVER-E N4R8  C967023

void setup() {
  Wire.begin(I2C1_SDA_PIN, I2C1_SCL_PIN);
  Wire1.begin(I2C2_SDA_PIN, I2C2_SCL_PIN);
  Serial.begin(115200);
  Serial.println("start");
  onebus_init();
  gpio_init();
  oled_init();
  ads_init();
  dac_init();
}

void loop() {
  onebus_loop();
  oled_loop();
  enc_get_key_pressed();
  ads_loop();
  dac_loop();
  delay(1000);
}
