/*
 * GccApplication1.cpp
 *
 * Created: 11/8/2022 9:04:55 PM
 * Author : Lahiru Shyamal
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <u8g2.h>
#include <stdio.h>
#include <u8x8_avr.h>
#include <string.h>
#define SSD1306_ADDR  0x78

u8g2_t u8g2;

int type = 8*60;
uint8_t minute ;
uint8_t second ;

void updateMenu();
void UV_light();
char res[100];

int main (void)
{
	
	DDRC = 0x00;
	DDRD = 0xfe;
	PORTC = 0xff;
	PORTD = 0x01;
	
	
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_avr_hw_i2c, u8x8_avr_delay);
	u8g2_SetI2CAddress(&u8g2, SSD1306_ADDR);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
	u8g2_SetFontRefHeightText(&u8g2);
	u8g2_SetFontPosTop(&u8g2);
	u8g2_DrawStr(&u8g2, 10, 20, "....The Squad....");
	u8g2_SendBuffer(&u8g2);
	_delay_ms(2000);
while (1)
	{
	
	
	if(~PINC& 0x01){ UV_light(); }
	
	if(~PINC& 0x02)
	{
		_delay_ms(500);
		type = type + 120;
		if(type > 60*10){type=60*10;}
		updateMenu();
		
	}
	
	if(~PINC& 0x08)
	{
		_delay_ms(500);
		type = type - 120;
		if(type < 60*6){type=60*6;}
		updateMenu();
	}
	updateMenu();
	PORTD &= ~(1<<PORTD3);
	
	}
}


void UV_light(){
	int temp = 0;

	while(temp <= type)
	{
		int i = 0;
		while (i<10){
			
			if ((~PIND & (1<<PIND1)))
			{
				PORTD &= ~(1<<PORTD3);
				
					// Sending information to LCD to print
					u8g2_ClearBuffer(&u8g2);
					u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
					u8g2_DrawStr(&u8g2, 30, 10, "Caution");
					u8g2_SendBuffer(&u8g2);
					// LCD ............
			}
			
			else if(~PINC& (1<<PINC2))
			{
					// Sending information to LCD to print
					u8g2_ClearBuffer(&u8g2);
					u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
					u8g2_DrawStr(&u8g2, 30, 10, "Force Stopped");
					u8g2_SendBuffer(&u8g2);
					// LCD ............
					_delay_ms(1000);
				return;
			}
			else
			{
				PORTD |= (1<<PORTD3);
				_delay_ms(100);
				i=i+1;
			}
		}
		temp = temp+1;
		minute = (type-temp)/60;
		second = (type-temp)%60;
		sprintf(res, "%d:%d", minute,second);
		
		
		// Sending information to LCD to print
			u8g2_ClearBuffer(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
			
			u8g2_DrawStr(&u8g2, 30, 10, "Time Left");
			u8g2_DrawStr(&u8g2, 40, 30, res);
			u8g2_SendBuffer(&u8g2);
	   // LCD ............
	}
	
	PORTD &= ~(1<<PORTD3);

	return;
	
}




void updateMenu(){
	switch(type){
		
		case 6*60:
			// Sending information to LCD to print
			u8g2_ClearBuffer(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
			u8g2_DrawStr(&u8g2, 30, 10, "Small Items");
			u8g2_DrawStr(&u8g2, 30, 40, "6 Minutes");
			u8g2_SendBuffer(&u8g2);
			// LCD ............
		break;
		
		case 8*60:							//Third display state
			// Sending information to LCD to print
			u8g2_ClearBuffer(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
			u8g2_DrawStr(&u8g2, 30, 10, "Medium Items");
			u8g2_DrawStr(&u8g2, 30, 40, "8 Minutes");
			u8g2_SendBuffer(&u8g2);
			// LCD ............
		break;
		
		
		case 10*60:
			// Sending information to LCD to print
			u8g2_ClearBuffer(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_smart_patrol_nbp_tr);
			u8g2_DrawStr(&u8g2, 30, 10, "Large Items");
			u8g2_DrawStr(&u8g2, 30, 40, "10 Minutes");
			u8g2_SendBuffer(&u8g2);
			// LCD ............;
		break;
		
	}
	return;
}