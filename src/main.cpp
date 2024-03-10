#include <Arduino.h>
#include <Wire.h>
#include "gpio.h"
#include "onebus_sensor.h"
#include "display.h"
#include "i2c_ads.h"
#include "i2c_dac.h"
#include "g_val.h"

// ESP32-WROVER-E N4R8  C967023

void calculator_other_status(void)
{
  loadStatus.power = loadStatus.voltage * loadStatus.current;
  if (abs(loadStatus.current) > 0.01)
  {
    loadStatus.resistance = loadStatus.voltage / loadStatus.current;
  }
  else
  {
    loadStatus.resistance = 999.99;
  }
}

uint16_t calculator_set_i(void)
{
  float buf_f = (loadSet.current * loadSet.current_mul + loadSet.current_base);
  if (buf_f < 0.0)
  {
    return 0;
  }
  else if (buf_f > 4095){
    return 4095;
  }
  else {
    return static_cast<uint16_t>(buf_f);
  }
}

void Core0task(void *args) // Wire
{
  Serial.print("task0");
  ads_v_init();
  dac_init();
  for (;;)
  {
    loadStatus.voltage = (ads_v_loop() - loadStatus.voltage_base) * loadStatus.voltage_mul;
    calculator_other_status();
    vTaskDelay(60 / portTICK_PERIOD_MS); // 60ms
    set_dac(calculator_set_i());
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void Core1task(void *args) // Wire1
{
  Serial.print("task1");
  ads_i_init();
  oled_init();
  for (;;)
  {
    loadStatus.current = (ads_i_loop() - loadStatus.current_base) * loadStatus.current_mul;
    calculator_other_status();
    vTaskDelay(20 / portTICK_PERIOD_MS);
    oled_loop();
    vTaskDelay(60 / portTICK_PERIOD_MS);
  }
}

void Core2task(void *args) // onebus
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
  gpio_loop();
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
