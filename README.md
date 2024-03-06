## 项目说明

[Electronic_load_idf](https://github.com/yyii-site/Electronic_load_idf)项目的硬件重新使用Arduino编写程序

## platformio.ini

u8g2库的I2C默认使用Wire,需增加此参数用以启用Wire1总线.

`build_flags = -D U8X8_HAVE_2ND_HW_I2C` 

之后即可使用:

`U8G2_SSD1306_128X32_UNIVISION_F_2ND_HW_I2C u8g2(U8G2_R0);`