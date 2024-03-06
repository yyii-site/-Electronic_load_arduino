#include <Arduino.h>
#include "gpio.h"

int16_t encoder;

bool enc_get_key_pressed()
{
  if (!digitalRead(ENCORD_K_PIN))
  {
    Serial.println("encoder_key press");
    return true;
  }
  else
  {
    return false;
  }
}

int16_t enc_get_new_moves()
{
  static int16_t last;
  int16_t change = 0;
  if (last != encoder)
  {
    change = encoder - last;
    last = encoder;
    Serial.print("encoder:");
    Serial.println(change);
  }
  return change;
}

void IRAM_ATTR pin_A_ISR()
{
    int pinB = digitalRead(ENCORD_B_PIN);

    if (pinB)
    {
      encoder--;
      Serial.println("encoder--");
    }
    else
    {
      encoder++;
      Serial.println("encoder++");
    }
}

void gpio_init(void)
{
    pinMode(ENCORD_A_PIN, INPUT);
    pinMode(ENCORD_B_PIN, INPUT);
    pinMode(ENCORD_K_PIN, INPUT);

    attachInterrupt(ENCORD_A_PIN, pin_A_ISR, FALLING);
}