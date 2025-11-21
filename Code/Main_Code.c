
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "USART_lib.h"

#define _XTAL_FREQ 4000000  

// Variables globales pour l'interruption
volatile uint16_t t1 = 0;
volatile uint16_t t2 = 0;
volatile uint16_t period = 0;  
volatile uint8_t newMeasure = 0;
volatile uint8_t firstCapture = 1;

// Prototypes des fonctions
void lcd_intial_4bits(void);
unsigned int ADC_Read1(void);
unsigned int ADC_Read2(void);
void Timer1_Init(void);
void USART_Write_Char(char c);
void USART_Write_Text(const char *str);

//test

void main(void) {
    USART_init(_XTAL_FREQ, 9600);

    unsigned int ADC_value1;
    unsigned int ADC_value2;
    int16_t voltage_mV1, voltage_mV2;
    int16_t temp_mC, pot_percent;
    char str_buffer[10]; // 

    TRISB0 = 1;  
    Timer1_Init();  // Initialisation du Timer1
    OPTION_REGbits.INTEDG = 1 ;  // Rising_edge Interruption 
    INTCONbits.INTE = 1;    // activation de l'inteription externe
    INTCONbits.GIE = 1; //activation des interruptions globales
    INTCONbits.T0IE = 0; //    pas d?interruption Timer0
    
    //    Configuration capture CCP1 
     TRISC2 = 1;  // RC2 = CCP1 en entre (signal  mesurer)
     
     
     CCP1CON = 0b00000101;  // CCPxM3:CCPxM0 => 0101 => Capture mode, every rising edge

    // --Activation des interruptions
    PIE1bits.CCP1IE = 1;  // interruption capture active
    INTCONbits.PEIE = 1;  // interruptions peripheriques
    INTCONbits.GIE = 1;   // interruptions globales

    while (1) {
        // --- Lecture et affichage ADC1 -- Capteur de température ---
        ADC_value1 = ADC_Read1();  
        sprintf(str_buffer, "%4u", ADC_value1);
        USART_Write_Text("ADC1(AN4)=");
        USART_Write_Text(str_buffer);
        USART_Write_Char('\r');

        voltage_mV1 = ((uint32_t)ADC_value1 * 2050) / 1023 - 550;
        temp_mC = voltage_mV1 * 100;  // ?? Ici, temperature = tension * 100 (en milli-degrs)

        // Affichage tension avec signe
        char sign_v = (voltage_mV1 < 0) ? '-' : ' ';
        int16_t abs_v = (voltage_mV1 < 0) ? -voltage_mV1 : voltage_mV1; // calcule de la valeur absolu 
        sprintf(str_buffer, "%c%d.%02d", sign_v, abs_v / 1000, (abs_v % 1000) / 10);
        USART_Write_Text("V=");
        USART_Write_Text(str_buffer);
        USART_Write_Char('V');
        USART_Write_Char('\r');
        voltage_mV1 = ((uint32_t)ADC_value1 * 2050) / 1023 - 550; 
        // Affichage tempErature avec signe (3 chiffres aprEs virgule)
        char sign_t = (voltage_mV1 < 0) ? '-' : ' ';
        int16_t abs_t = (voltage_mV1 < 0) ? -voltage_mV1 : voltage_mV1; 
        sprintf(str_buffer, "%c%d", sign_t, abs_t / 10);  // ex: -1230 => "-1.230"
        USART_Write_Text("temp=");
        USART_Write_Text(str_buffer);
        USART_Write_Char('C');
        USART_Write_Char('\r');
        USART_Write_Text("----------------");
        USART_Write_Char('\r');

        // --- Lecture et affichage ADC2 ---
        ADC_value2 = ADC_Read2();
        sprintf(str_buffer, "%4u", ADC_value2);
        USART_Write_Text("ADC2(AN0)=");
        USART_Write_Text(str_buffer);
        USART_Write_Char('\r');

        voltage_mV2 = ((uint32_t)ADC_value2 * 5000) / 1023;
        pot_percent = ((voltage_mV2/1000) * 100) / 5;

        sprintf(str_buffer, "%d.%02d", voltage_mV2 / 1000, (voltage_mV2 % 1000) / 10);
        USART_Write_Text("V=");
        USART_Write_Text(str_buffer);
        USART_Write_Char(' V');
        USART_Write_Char('\r');

        //sprintf(str_buffer, "%d",(voltage_mV2*2)*10);
        sprintf(str_buffer, "%d", pot_percent);
        USART_Write_Text("pot=");
        USART_Write_Text(str_buffer);
        USART_Write_Char(' %');
        USART_Write_Char('\r');

        USART_Write_Text("----------------");
        USART_Write_Char('\r');

        // --- Affichage fréquence ---
        if (newMeasure) {
            newMeasure = 0;

            if (period > 0) {
                //uint32_t freq = 1000000UL / period;
                uint32_t freq = 1000000 / period ; // ici  1 tick = 1 us
                sprintf(str_buffer, "%lu", freq);
                USART_Write_Text("freq = ");
                USART_Write_Text(str_buffer);
                USART_Write_Text(" Hz");
                USART_Write_Char('\r');

                sprintf(str_buffer, "%u", period);
                USART_Write_Text("periode = ");
                USART_Write_Text(str_buffer);
                USART_Write_Text(" us");
                USART_Write_Char('\r');
                
                uint32_t freqRot = freq/48 ; // 48 sont le nombre des dent de la roue -- 48 dents = 1 tour
                // Tr/S ->> rad/s ->> vitess lineare  Km/h
                uint32_t vitess = freqRot*6.785840138; //((((freqRot/(2*3.1416))*0.3)*0.001)*3600) | 30cm le rayon de la roue 
                //vitess = freqRot / 10000000;
                sprintf(str_buffer, "%d", vitess);
                USART_Write_Text("Vitesse = ");
                USART_Write_Text(str_buffer);
                USART_Write_Text(" Km/h");
                USART_Write_Char('\r');

                USART_Write_Text("----------------");
                USART_Write_Char('\r');
            }
        }
       // __delay_ms(1);
        
    }
}


void __interrupt() ISR(void) {
    if (PIR1bits.CCP1IF) {  // Interruption CCP1
        PIR1bits.CCP1IF = 0;

        uint16_t timer_value = ((uint16_t)CCPR1H << 8) | CCPR1L;

        if (firstCapture) {  // 
            t1 = timer_value;
            firstCapture = 0;
        } else {
            t2 = timer_value;
            period = (t2 >= t1) ? (t2 - t1) : ((0xFFFF - t1) + t2 + 1);
            t1 = t2;  // préparation pour prochaine mesure
            firstCapture = 1;
            newMeasure = 1;
        }
    }
}

void Timer1_Init(void) {
    // Configuration du Timer1 : Prescaler 1:1, horloge interne (Fosc/4)
    T1CONbits.T1CKPS = 0b00;  //  Prescaler = 1:1
    T1CONbits.TMR1CS = 0;     //  Horloge interne (Fosc/4)
    T1CONbits.T1OSCEN = 0;    //   Oscillateur externe desactivé

    // Reinitialisation du compteur
    TMR1H = 0;
    TMR1L = 0;

    
    T1CONbits.TMR1ON = 1; // Activation du Timer1
}

void USART_Write_Char(char c) {
    while (!PIR1bits.TXIF);
    TXREG = c;
}

void USART_Write_Text(const char *str) {
    while (*str) {
        USART_Write_Char(*str++);
    }
}

