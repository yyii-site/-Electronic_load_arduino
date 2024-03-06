#ifndef __USER_GPIO_H_
#define __USER_GPIO_H_

#include <stdint.h>

void gpio_init(void);
bool enc_get_key_pressed();
int16_t enc_get_new_moves();


#endif