#include <xc.h>
#define _XTAL_FREQ 4000000

unsigned int ADC_Read1() {  
    TRISA=0xFF;
    //ADCON1=0x80;
    //ADCON0=0x41;
    ADCON1=0x88;
    ADCON0=0x61;
    __delay_us(20);
    ADCON0bits.GO=1;
    while (ADCON0bits.GO){}
    unsigned int adc_value=(ADRESH<<8)+ADRESL;
    return adc_value;
}

unsigned int ADC_Read2() {  
    TRISA=0xFF;
    ADCON1=0x80;
    ADCON0=0x41;
    __delay_us(20);
    ADCON0bits.GO=1;
    while (ADCON0bits.GO){}
    return (ADRESH<<8)+ADRESL;
}
