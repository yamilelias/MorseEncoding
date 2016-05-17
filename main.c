//==================================================================================
//|| PROYECTO FINAL DE MICROCONTROLADORES                                         ||
//||                                                                              ||
//|| Proyecto: Clave SHAVO                                                        ||
//|| Clase: Main                                                                  ||
//|| Profesor: Dr. Rodolfo Castelló                                               ||
//|| Integrantes: Jonathan Torres, Dilan Coss, Yamil Elías                        ||
//|| Escuela: Instituto Tecnológico de Estudios Superiores de Monterrey           ||
//==================================================================================

#include <xc.h>
#include "functions.h" // Include our custom header file
#include <string.h>

//OSCILLATOR SOURCE AND DIGITAL I/O CONFIGURATION BITS
//====================================================
#pragma config OSC = IRCIO67  // CONFIG1H (0-3) = 0010: INTIO2 oscillator
#pragma config MCLRE = ON        // CONFIG3H.7 = 1: Pin de RESET habilitado y Entrada RE3 desactivado.
#pragma config PBADEN = OFF      // CONFIG3H.1 = 0: PORTB.0 -- PORTB.4 as Digital I/O.
#pragma config LVP = OFF         // CONFIG3H.2 = 0: Single-Supply ICSP disabled  so that PORTB.5 works as Digital I/O.

//PICIT-3 DEBUGGER SETUP CONFIGURATION BITS
//=========================================
#pragma config WDT = OFF        // CONFIG2H (0) = 0: Watchdog Timer Disabled.

//get the length of an array
#define arrayLength(array) (unsigned char) (sizeof(array) / sizeof((array)[0]))

//special bits for the LCD
#define registerSelectBit PORTCbits.RC0
#define readWriteBit PORTCbits.RC1
#define enableBit PORTCbits.RC2

//constants
unsigned char GREETING[] = "Hello World";
unsigned char CASTELLO[] = "Castello <3";

unsigned char unoMorse[] = "1 .---- ";
unsigned char unoSize = 9;
unsigned char tresMorse[] = "3 ...-- ";
unsigned char tresSize = 9;

unsigned char oneShotFlag = 0; //  One-shot flag.

//Function declarations
void portDAsInput();
void portDAsOutput();
void LCDSetup();
void shortDelay();
void longDelay();
void command (unsigned char x);
void isReady();
void displayCharOnLCD(unsigned char character);
void displayLineOnLCD(unsigned char array[], unsigned char sizeOfArray);


void main(){
      //CLOCK FREQUENCY CONFIGURATION
    //============================
    OSCCON = 0x60;             // 4 MHz internal oscillator

    //DISABLE PORT's ANALOG FUNCTIONS
    //===============================
    CMCON = 0x07;              // Comparators OFF, to use PORT_Ds LSN
    CVRCONbits.CVREN = 0;      // Comparator Voltge Reference Module OFF
    ADCON1 = 0x0F;             // All ports as DIGITAL I/O

    //Activate PORTB's pull up resistors
    INTCON2bits.RBPU = 0;

    PORTB = 0X00;   //Clear PORTB
    LATB = 0X00;    //Clear LATB
    TRISB = 0XFF;   //Set PORTB as input 

    PORTC = 0X00;   //Clear PORTC
    LATC = 0X00;    //Clear LATC
    TRISC = 0X00;   //Set PORTC as output

    //LSb of PORTB as outputs
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    
    //set the portD as output
    portDAsOutput();
    
    //initial LCD Setup
    LCDSetup();
    
    //infinite loop to constantly be waiting for user input on the keyboard matrix
    while(1){
      groundAllRows();  //ground all rows so we can detect if a button is pressed
  
      if(PORTB != 0xF0){    //if PORTB is different from 0xF0, a button is being pressed, we must implement oneShot
          oneShot();
      }
      if(oneShotFlag == 1){ //if the oneShotFlag == 1, reset the oneShotFlag
          resetOneShot();
      }
    }
    
    
  
  
}

// LCD FUNCTIONS
//==============

void portDAsInput(){
    TRISD = 0xFF;
}

void portDAsOutput(){
    TRISD = 0x00;
}

void LCDSetup(){
    enableBit = 0;
    longDelay();
    command(0x38);
    longDelay();
    command(0x0F);
    isReady();
    command(0x01);
    isReady();
}

//450 ns delay
void shortDelay(){
    unsigned char L1REG = 2;
    while(L1REG-- > 0){}
}

//250 ms delay
void longDelay(){
    unsigned char L1REG = 2;
    unsigned char L2REG = 162;
    unsigned char L3REG = 255;
    
    while(L1REG-- > 0){
        L2REG = 162;
        while(L2REG-- > 0){
            L3REG = 255;
            while(L3REG-- > 0){}
        }
    }
}

void command(unsigned char x){
    PORTD = x;
    registerSelectBit = 0;
    readWriteBit = 0;
    enableBit = 1;
    shortDelay();
    enableBit = 0;
}

void isReady(){
    portDAsInput();
    registerSelectBit = 0;
    readWriteBit = 1;
    
    while(PORTDbits.RD7 == 1){
        enableBit = 1;
        shortDelay();
        enableBit = 0;
    }
    portDAsOutput();   
}

void displayCharOnLCD(unsigned char character){
    PORTD = character;
    registerSelectBit = 1;
    readWriteBit = 0;
    enableBit = 1;
    shortDelay();
    enableBit = 0;
}

void displayLineOnLCD(unsigned char array[], unsigned char sizeOfArray){
    unsigned char i;
    for(i=0; i<sizeOfArray; i++){
        displayCharOnLCD(array[i]);
    }
}