#include <Arduino.h>
#include "gpio.h"
#include "OneButton.h"
#include "g_val.h"
#include <math.h>

int16_t encoder;
OneButton button_k(ENCORD_K_PIN, true); // parameter activeLOW is true, because external wiring sets the button to LOW when pressed.

float bit_change_value(float source, int8_t select_bit, int8_t change_step)
{
  float target;
  if (select_bit > 0)
    select_bit--;
  float factor = pow(10, abs(select_bit));

  if (select_bit >= 0)
  {
    float change_value = change_step * factor;
    target = source + change_value;
  }
  else
  {
    float change_value = change_step / factor;
    target = source + change_value;
  }
  if (target > 99.99)
  {
    target = 99.99;
  }
  else if (target < 0)
  {
    target = 0;
  }
  return target;
}

void encoder_change_current(int16_t value)
{
  static int16_t last = 0;
  if (last != value)
  {
    int16_t change = encoder - last;
    Serial.print("change_bit:");
    Serial.println(loadSet.change_bit);
    Serial.print("change:");
    Serial.println(change);

    loadSet.current = bit_change_value(loadSet.current, loadSet.change_bit, change);
    last = value;
  }
}

// This function will be called when the button1 was pressed 1 time
void click_k()
{
  Serial.println("Button 1 click.");
  if (loadSet.change_bit < 2)
  {
    loadSet.change_bit++;
    if (loadSet.change_bit == 0)
    {
      loadSet.change_bit = 1;
    }
  }
  else
  {
    loadSet.change_bit = -2;
  }
}

// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick_k()
{
  Serial.println("Button 1 doubleclick.");
}

// This function will be called once, when the button1 is pressed for a long time.
void longPressStart_k()
{
  Serial.println("Button 1 longPress start");
} // longPressStart1

// This function will be called often, while the button1 is pressed for a long time.
void longPress_k()
{
  Serial.println("Button 1 longPress...");
}

// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop_k()
{
  Serial.println("Button 1 longPress stop");
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
  attachInterrupt(ENCORD_A_PIN, pin_A_ISR, FALLING);

  button_k.attachClick(click_k);
  button_k.attachDoubleClick(doubleclick_k);
  button_k.attachLongPressStart(longPressStart_k);
  button_k.attachLongPressStop(longPressStop_k);
  button_k.attachDuringLongPress(longPress_k);
}

void gpio_loop(void)
{
  button_k.tick();
  encoder_change_current(encoder);
  // You can implement other code in here or just wait a while
  // delay(10);
}