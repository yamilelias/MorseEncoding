//==================================================================================
//|| PROYECTO FINAL DE MICROCONTROLADORES                                         ||
//||                                                                              ||
//|| Proyecto: Clave SHAVO                                                        ||
//|| Clase: Buzzer                                                                ||
//|| Profesor: Dr. Rodolfo Castelló                                               ||
//|| Integrantes: Jonathan Torres, Dilan Coss, Yamil Elías                        ||
//|| Escuela: Instituto Tecnológico de Estudios Superiores de Monterrey           ||
//==================================================================================

#include <xc.h>
#include "functions.h" // Include our functions header file

#define _XTAL_FREQ 4000000
#define BUZZER PORTCbits.RC7
#define GATE PORTCbits.RC3

void buzzerShort(void){
    BUZZER = 1;
    shortBuzzerDelay();
    BUZZER = 0;
    shortBuzzerDelay();
}

void buzzerLong(void){
    BUZZER = 1;
    longBuzzerDelay();
    BUZZER = 0;
    shortBuzzerDelay();
}

void shortBuzzerDelay(void){
    unsigned char  L3REG = 0;
    unsigned char  L1REG = 0;
    unsigned char  L2REG = 0;
    
    while(L3REG++ < 2)
    {
        L1REG = 0;
        while(L1REG++ < 200){
            L2REG = 0;
            while(L2REG++ < 250);
        }
    }
}

void longBuzzerDelay(void){
    unsigned char  L3REG = 0;
    unsigned char  L1REG = 0;
    unsigned char  L2REG = 0;
    
    while(L3REG++ < 4)
    {
        L1REG = 0;
        while(L1REG++ < 200){
            L2REG = 0;
            while(L2REG++ < 250);
        }
    }
}