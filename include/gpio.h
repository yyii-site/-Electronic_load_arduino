#ifndef __USER_GPIO_H_
#define __USER_GPIO_H_

#include <stdint.h>

extern int16_t encoder;

void gpio_init(void);
void gpio_loop(void);
int16_t enc_get_new_moves();
void voltage_source_change(bool val);
void fan_duty_change(uint8_t duty);


#endif