#include <xc.h>
#define _XTAL_FREQ 4000000
void Write_chr(unsigned char chr)
{
    while(!TXIF);
     TXREG=chr;
}
void Write_str(const unsigned char *str)
{
 for (int i=0;str[i]!='\0';i++)
 {
     Write_chr(str[i]);
 }
}
unsigned char Read_chr(void)
{
     while(!RCIF);
     return RCREG;
}

void USART_init(float Fosc,float BaudRate)
{
    TRISC6=0;//RC6 as an output for transmission
    TRISC7=1;//RC7 as an intput for reception
    SPEN=1;// enable serial communication
    SYNC=0;//choisir le mode asynchrone
    TXEN=1;// enable transmission
    CREN=1;// enable reception   
     // Baud_rate setting
    BRGH=1;
    float x=Fosc/(BaudRate*16.0)-1;
    SPBRG=(char)x;
}

