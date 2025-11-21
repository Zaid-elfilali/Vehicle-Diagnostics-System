#include <xc.h>
#define _XTAL_FREQ 4000000
#define RS PORTBbits.RB4
#define RW PORTBbits.RB6
#define EN PORTBbits.RB5
#define LCD PORTB
void enable(void)
{
    EN=1;
    __delay_us(100);
    EN=0; 
}
void lcd_chr(unsigned char chr)
{  
    LCD&=0xF0;
    LCD|=((chr>>4) & 0x0F);////Send higher nibble
    RS=1;//mode data
    RW=0;//activation de l'écriture sur LCD
    enable(); 
    __delay_ms(1);
    LCD&=0xF0;
    LCD|=(chr & 0x0F);////Send higher nibble
    RS=1;//mode data
    RW=0;//activation de l'écriture sur LCD
    enable(); 
    
}
void lcd_cmd(unsigned char cmd)
{
    LCD&=0xF0;
    LCD|=((cmd>>4) & 0x0F);//charger la donnée dans le port C
    RS=0;//mode data
    RW=0;//activation de l'écriture sur LCD
    enable();
    __delay_ms(5);
    LCD&=0xF0;
    LCD|=(cmd & 0x0F);////Send higher nibble
    RS=0;//mode data
    RW=0;//activation de l'écriture sur LCD
    enable(); 
    __delay_ms(5);
}
void lcd_str(const unsigned char *str)
{
    unsigned char i=0;
    for (i=0;str[i]!='\0';i++)
    {
        lcd_chr(str[i]);
    }
}
void lcd_intial_4bits()
{
    TRISB=0x00; 
    PORTB=0x00;
    __delay_ms(20);
  lcd_cmd(0x33);
  lcd_cmd(0x32);
  lcd_cmd(0x28);
  lcd_cmd(0x0C);
  lcd_cmd(0x06);
  lcd_cmd(0x01);
  lcd_cmd(0x80);
}

