#include <xc.h>
#pragma config OSC = IRCIO67
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDT = OFF

#define _XTAL_FREQ 4000000
#define BUZZER PORTCbits.RC7
#define GATE PORTCbits.RC3

void sonarCorto(void);
void sonarLargo(void);
void cortoDelay(void);
void largoDelay(void);

unsigned char unoMorse[] = "1 .---- ";
unsigned char unoSize = 9;
unsigned char tresMorse[] = "3 ...-- ";
unsigned char tresSize = 9;

void main(void){
    
    OSCCON = 0x60;  //4 MHz
    ADCON1 = 0x0F; //ALL PORTS
    CVRCONbits.CVREN = 0;//PORTA
    //PORTB
    PORTB = 0x00;
    LATB = 0x00;
    TRISB = 0xF0;
    //PORTC
    PORTC = 0x00;
    LATC = 0x00;
    TRISCbits.RC0 = 0;//RS
    TRISCbits.RC1 = 0;//R/W
    TRISCbits.RC2 = 0;//E
    TRISCbits.RC3 = 1;//Gate
    TRISCbits.RC7 = 0;//Buzzer
    //PORTD
    CMCON = 0x07;
    PORTD = 0x00;
    LATD = 0x00;
    TRISD = 0x00;
    
    //PULL UP RESISTORS
    INTCON2bits.RBPU = 0;
    
    while(1)
    {
    sonarCorto();
    sonarCorto();
    sonarLargo();
    sonarCorto();
    }
}

void sonarCorto(void)
{
    BUZZER = 1;
    cortoDelay();
    BUZZER = 0;
    cortoDelay();
}

void sonarLargo(void)
{
    BUZZER = 1;
    largoDelay();
    BUZZER = 0;
    cortoDelay();
}

void cortoDelay(void)
{
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

void largoDelay(void)
{
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