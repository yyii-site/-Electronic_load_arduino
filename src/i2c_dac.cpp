#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void dac_init()
{
  dac.begin(0x60, &Wire);
}

void dac_loop()
{
  static uint16_t counter;
  counter += 100;
  if (counter > 4095)
  {
    counter = 0;
  }
  dac.setVoltage(counter, false);
}
