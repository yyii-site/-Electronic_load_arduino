#include <Arduino.h>
#include <U8g2lib.h>
#include "g_val.h"

enum
{
	pageStart,
	pageMain,
	pageEnd
};
uint16_t pageNum;

// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C2_SCL_PIN, I2C2_SDA_PIN);  //I2C1
U8G2_SSD1306_128X32_UNIVISION_F_2ND_HW_I2C u8g2(U8G2_R0); // I2C2  第二条i2c总线需要在platformio.ini中定义U8X8_HAVE_2ND_HW_I2C启用

void page_main(void);

void oled_init(void)
{
	// u8g2.setI2CAddress(0x3C);
	u8g2.begin();
}

void oled_loop(void)
{
	u8g2.clearBuffer();
	if (pageNum >= pageEnd)
	{
		pageNum = pageMain;
	}
	switch (pageNum)
	{
	case pageStart:
		pageNum = pageMain;
		break;
	case pageMain:
		page_main();
		break;

	default:
		pageNum = pageMain;
		break;
	}
	u8g2.sendBuffer();
}

void DrawNum(u8g2_uint_t x, u8g2_uint_t y, int value)
{
	if (value < 0)
	{
		u8g2.setCursor(x, y);
		value = abs(value);
		u8g2.print(F("-"));
	}
	u8g2.setCursor(x + 10, y);
	u8g2.print(F(u8x8_utoa(value)));
}

void page_main(void)
{
	u8g2_uint_t x, y;
	u8g2.setFontMode(1);

	//CC CV CW CR
	u8g2.setFont(u8g2_font_amstrad_cpc_extended_8u);
	y = 8;
	u8g2.setCursor(0, y);
	u8g2.print(F("[CC]  CV  CW  CR"));

	u8g2.setFont(u8g2_font_pxplustandynewtv_8_all);
	x = 0;
	u8g2.setCursor(x, 16);
	u8g2.print(F("123.45"));
	u8g2.setCursor(x, 24);
	u8g2.print(F("345.67"));
	u8g2.setCursor(x, 32);
	u8g2.print(F("456.78"));
	x = 50;
	u8g2.setCursor(x, 16);
	u8g2.print(F("V"));
	u8g2.setCursor(x, 24);
	u8g2.print(F("W"));
	u8g2.setCursor(x, 32);
	u8g2.print(F("R"));

	u8g2.setFont(u8g2_font_tenfatguys_t_all);
	u8g2.setCursor(64, 18);
	u8g2.print(F("56.78"));
	u8g2.setCursor(115, 18);
	u8g2.print(F("A"));

	u8g2.setFont(u8g2_font_trixel_square_tr);
	u8g2.setCursor(64, 25);
	u8g2.print(F("00:00:00"));
	u8g2.setCursor(100, 25);
	u8g2.print(F("T: 35C"));
	u8g2.setCursor(64, 32);
	u8g2.print(F("012.45Wh"));
	u8g2.setCursor(100, 32);
	u8g2.print(F("F: 100%"));

	// DrawNum(10, 15, load.voltage);
	// DrawNum(74, 15, load.current);
	// DrawNum(10, 33, load.set_current);
}
