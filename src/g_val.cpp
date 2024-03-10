#include "g_val.h"

int temputer;

LoadStatusTypeDef loadStatus = {
    0.0,
    0.0,
    0.0,
    0.0,

    0.0031336839,
    0.000327868852,

    85,
    -38};

LoadSetTypeDef loadSet = {
    0.0,
    0.01,
    0,
    -1};

/*
Step1:
voltage_sum = 0.01
current_sum = 0.01
voltage_base = 0
current_base = 0
不外接电源查看oled显示电压电流
将其x100后赋值给 voltage_base current_base

Setep2:
外接电源输出40V
voltage_mul = 40.0/oled显示电压x0.01

Setp3:
外接电10V 2A
设置输出DAC 4095
current_mul = 2.0/oled显示电流x0.01
*/