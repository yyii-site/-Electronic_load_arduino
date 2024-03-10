#ifndef __G_VAL_H_
#define __G_VAL_H_

typedef struct
{
    float voltage;    // V
    float current;    // A
    float power;      // W
    float resistance; // R

    float voltage_mul;
    float current_mul;

    int voltage_base;
    int current_base;
} LoadStatusTypeDef;
extern LoadStatusTypeDef loadStatus;

typedef struct
{
    float current; // A
    float current_mul;
    int current_base;

    int change_bit; // 2 = x10   1 = x1   0 = x1  -1 = x0.1   -2 = x0.01

    int fan_duty;
} LoadSetTypeDef;
extern LoadSetTypeDef loadSet;

extern float temperature;

#endif
