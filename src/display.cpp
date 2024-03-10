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
	u8g2.print(u8x8_utoa(value));
}

void page_main_demo(void)
{
	u8g2_uint_t x, y;
	u8g2.setFontMode(1);

	// CC CV CW CR
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
}

void Draw3Float(u8g2_uint_t x, u8g2_uint_t y, float value)
{
	char str_tmp[7];
	if (value > 999.99)
	{
		value = 999.99;
	}

	dtostrf(value, 6, 2, str_tmp);
	u8g2.setCursor(x, y);
	u8g2.print(str_tmp);
}

void Draw2Float(u8g2_uint_t x, u8g2_uint_t y, float value)
{
	char str_tmp[6];
	if (value > 99.99)
	{
		value = 99.99;
	}

	dtostrf(value, 5, 2, str_tmp);
	u8g2.setCursor(x, y);
	u8g2.print(str_tmp);
}

void DrawUpTime(u8g2_uint_t x, u8g2_uint_t y)
{
	u8g2_uint_t b = 4;
	char str_tmp[3];

	uint64_t t = millis() / 1000;
	// 计算小时、分钟和秒
	unsigned long hours = t / 3600;
	unsigned long minutes = (t % 3600) / 60;
	unsigned long seconds = (t % 3600) % 60;
	if (hours > 99)
	{
		hours = 99;
	}
	ultoa(hours, str_tmp, 10);
	u8g2.setCursor(x, y);
	u8g2.print(str_tmp);
	u8g2.setCursor(x + b * 2, y);
	u8g2.print(F(":"));
	ultoa(minutes, str_tmp, 10);
	u8g2.setCursor(x + b * 3, y);
	u8g2.print(str_tmp);
	u8g2.setCursor(x + b * 5, y);
	u8g2.print(F(":"));
	ultoa(seconds, str_tmp, 10);
	u8g2.setCursor(x + b * 6, y);
	u8g2.print(str_tmp);
}

void DrawTemputer(u8g2_uint_t x, u8g2_uint_t y, int value)
{
	u8g2_uint_t b = 4;

	char str_tmp[3];
	if (value > 99)
	{
		value = 99;
	}

	u8g2.setCursor(x, y);
	u8g2.print(F("T:"));
	u8g2.setCursor(x + b * 2, y);
	ultoa(value, str_tmp, 10);
	u8g2.print(str_tmp);
}

// u8g2.print(F("[CC]  CV  CW  CR"));
void DrawSetCurrent(u8g2_uint_t x, u8g2_uint_t y, float value)
{
	u8g2_uint_t j;
	char str_tmp[6];
	bool blink;

	if (millis() / 100 % 10 > 4)
	{
		blink = true;
	}
	else
	{
		blink = false;
	}

	if (value > 99.99)
	{
		value = 99.99;
	}

	dtostrf(value, 5, 2, str_tmp);
	for (uint8_t i = 0; i < sizeof(str_tmp); i++)
	{
		if (str_tmp[i] == ' ')
		{
			str_tmp[i] = '0';
		}
	}
	if (blink)
	{
		// switch (loadSet.change_bit)
		// {
		// case 2:
		// 	str_tmp[0] = '_';
		// 	break;
		// case 1:
		// case 0:
		// 	str_tmp[1] = '_';
		// 	break;
		// case -1:
		// 	str_tmp[3] = '_';
		// 	break;
		// case -2:
		// 	str_tmp[4] = '_';
		// 	break;
		// default:
		// 	break;
		// }
		j = y-1;
		switch (loadSet.change_bit)
		{
		case 2:
			u8g2.drawLine(x+0, j, x+6, j);
			break;
		case 1:
		case 0:
			u8g2.drawLine(x+8, j, x+14, j);
			break;
		case -1:
			u8g2.drawLine(x+24, j, x+30, j);
			break;
		case -2:
			u8g2.drawLine(x+32, j, x+38, j);
			break;
		default:
			break;
		}
	}
	u8g2.setCursor(x, y);
	u8g2.print(str_tmp);
}

void page_main(void)
{
	u8g2_uint_t x, y;
	u8g2.setFontMode(1);

	u8g2.setFont(u8g2_font_amstrad_cpc_extended_8u);
	y = 8;
	u8g2.setCursor(20, y);
	u8g2.print(F("CC"));
	DrawSetCurrent(80, y, loadSet.current);

	u8g2.setFont(u8g2_font_pxplustandynewtv_8_all);
	x = 0;
	Draw3Float(x, 16, loadStatus.voltage);
	Draw3Float(x, 24, loadStatus.power);
	Draw3Float(x, 32, loadStatus.resistance);

	x = 50;
	u8g2.setCursor(x, 16);
	u8g2.print(F("V"));
	u8g2.setCursor(x, 24);
	u8g2.print(F("W"));
	u8g2.setCursor(x, 32);
	u8g2.print(F("R"));

	u8g2.setFont(u8g2_font_tenfatguys_t_all);
	Draw2Float(64, 18, loadStatus.current);
	u8g2.setCursor(115, 18);
	u8g2.print(F("A"));

	u8g2.setFont(u8g2_font_trixel_square_tr);
	DrawUpTime(64, 25);
	DrawTemputer(100, 25, temputer);
	u8g2.setCursor(64, 32);
	u8g2.print(F("012.45Wh"));
	u8g2.setCursor(100, 32);
	u8g2.print(F("F: 100%"));
}
