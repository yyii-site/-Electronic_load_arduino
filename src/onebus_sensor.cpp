#include <Arduino.h>
#include <OneWire.h>

OneWire ds(ONEBUS_PIN); // on pin (a 4.7K resistor is necessary)

float onebus_loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[9];
  byte addr[8] = {0x28, 0x8A, 0x77, 0x48, 0xF6, 0x02, 0x3C, 0x2B};
  float celsius;
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  vTaskDelay(1000 / portTICK_PERIOD_MS);;     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
//   Serial.print("  Temperature = ");
//   Serial.print(celsius);
//   Serial.print(" Celsius, ");
  return celsius;
}