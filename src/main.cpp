#include <Arduino.h>
#include <Wire.h>
#include "gpio.h"
#include "onebus_sensor.h"
#include "display.h"
#include "i2c_ads.h"
#include "i2c_dac.h"
#include "g_val.h"

// ESP32-WROVER-E N4R8  C967023

void calculator(void)
{
  load.power = load.voltage * load.current;
  if (abs(load.current) > 0.01)
  {
    load.resistance = load.voltage / load.current;
  }
  else
  {
    load.resistance = 999.99;
  }
}

uint16_t calculator_set_i(void)
{
  return load.set_current * load.current_sub - load.current_base;
}

void Core0task(void *args) //Wire
{
  Serial.print("task0");
  ads_v_init();
  dac_init();
  for (;;)
  {
    load.voltage = (ads_v_loop()-load.voltage_base)*load.voltage_sub;
    calculator();
    vTaskDelay(60 / portTICK_PERIOD_MS); //60ms
    set_dac(4095);
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void Core1task(void *args) //Wire1
{
  Serial.print("task1");
  ads_i_init();
  oled_init();
  for (;;)
  {
    load.current = (ads_i_loop()-load.current_base)*load.current_sub;
    calculator();
    vTaskDelay(20 / portTICK_PERIOD_MS);
    oled_loop();
    vTaskDelay(60 / portTICK_PERIOD_MS);
  }
}

void Core2task(void *args) //onebus
{
  Serial.print("task2");
  onebus_init();
  for (;;)
  {
    temputer = onebus_loop();
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Wire.begin(I2C1_SDA_PIN, I2C1_SCL_PIN);
  Wire1.begin(I2C2_SDA_PIN, I2C2_SCL_PIN);
  Serial.begin(115200);
  Serial.println("start");
  gpio_init();

  xTaskCreatePinnedToCore(Core0task, "Core0task", 2048, NULL, 3, NULL, 0);
  xTaskCreatePinnedToCore(Core1task, "Core1task", 2048, NULL, 4, NULL, 1);
  xTaskCreatePinnedToCore(Core2task, "Core2task", 1024, NULL, 5, NULL, 0);
}

void loop()
{
  enc_get_key_pressed();
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
