//==================================================================================
//|| PROYECTO FINAL DE MICROCONTROLADORES                                         ||
//||                                                                              ||
//|| Proyecto: Clave SHAVO                                                        ||
//|| Clase: Teclado Matricial                                                     ||
//|| Profesor: Dr. Rodolfo Castelló                                               ||
//|| Integrantes: Jonathan Torres, Dilan Coss, Yamil Elías                        ||
//|| Escuela: Instituto Tecnológico de Estudios Superiores de Monterrey           ||
//==================================================================================

#include <xc.h>
#include "functions.h" // Include our functions header file

unsigned char oneShotFlag = 0; //  One-shot flag.

unsigned char DDRAMAddress = 0; // This is too watch out for pointer position

//rows of the keyboard matrix
#define row1 PORTBbits.RB0
#define row2 PORTBbits.RB1
#define row3 PORTBbits.RB2
#define row4 PORTBbits.RB3

//columns of the keyboard matrix
#define col1 PORTBbits.RB4
#define col2 PORTBbits.RB5
#define col3 PORTBbits.RB6
#define col4 PORTBbits.RB7

#define LED1 PORTDbits.RD0
#define LED2 PORTDbits.RD1
#define LED3 PORTDbits.RD2
#define LED4 PORTDbits.RD3
#define LED5 PORTDbits.RD4
#define LED6 PORTDbits.RD5
#define LED7 PORTDbits.RD6
#define LED8 PORTDbits.RD7

unsigned char columnSelected;
unsigned char rowSelected;
unsigned char keyCode;

void groundAllRows(){    
    row1 = 0;
    row2 = 0;
    row3 = 0;
    row4 = 0;
}

void oneShot(){     
    if (oneShotFlag == 1)    //IF One-Shot has been triggered THEN EXIT.
        return;
    delay();                 //Eliminate Bouncing.
    if (PORTB  != 0xF0){     //IF a button is still pressed
        pressedKey();       //a key was pressed, determine which key and act accordingly
        oneShotFlag = 1;            //Turn-ON one-shot flag.
    }
}

void resetOneShot(){
    if (PORTB  == 0xF0)      //IF RB0 OFF THEN Eliminate Bouncing
        delay();
    else                    //ELSE EXIT
        return;
    if (PORTB  == 0XF0){      //IF RB0 OFF THEN reset one-shot flag
        //turnOffAllLeds();
        oneShotFlag = 0;
    }
        
}

//10 ms delay
void delay(){
    unsigned char L1REG = 0;
    unsigned char L2REG;
    while(L1REG++ < 13){
        L2REG = 0;
        while(L2REG++ < 255);
    }
}

void turnOnAllRows(){
    row1 = 1;
    row2 = 1;
    row3 = 1;
    row4 = 1;
}

void determinePressedRow(){
    char i;
    for(i=0; i<4; i++){
        turnOnAllRows();
        switch(i){
            case 0: {
                
                row1 = 0;
                if( (columnSelected == 1) && (col1 == 0)){
                    rowSelected = 1;
                    return;
                }
                if( (columnSelected == 2) && (col2 == 0)){
                    rowSelected = 1;
                    return;
                }
                if( (columnSelected == 3) && (col3 == 0)){
                    rowSelected = 1;
                    return;
                }
                if( (columnSelected == 4) && (col4 == 0)){
                    rowSelected = 1;
                    return;
                }
            }break;
            case 1: {
                row2 = 0;
                if( (columnSelected == 1) && (col1 == 0)){
                    rowSelected = 2;
                    return;
                }
                if( (columnSelected == 2) && (col2 == 0)){
                    rowSelected = 2;
                    return;
                }
                if( (columnSelected == 3) && (col3 == 0)){
                    rowSelected = 2;
                    return;
                }
                if( (columnSelected == 4) && (col4 == 0)){
                    rowSelected = 2;
                    return;
                }
            }break;
            case 2: {
                row3 = 0;
                if( (columnSelected == 1) && (col1 == 0)){
                    rowSelected = 3;
                    return;
                }
                if( (columnSelected == 2) && (col2 == 0)){
                    rowSelected = 3;
                    return;
                }
                if( (columnSelected == 3) && (col3 == 0)){
                    rowSelected = 3;
                    return;
                }
                if( (columnSelected == 4) && (col4 == 0)){
                    rowSelected = 3;
                    return;
                }
            }break;
            case 3: {
                
                row4 = 0;
                if( (columnSelected == 1) && (col1 == 0)){
                    rowSelected = 4;
                    return;
                }
                if( (columnSelected == 2) && (col2 == 0)){
                    rowSelected = 4;
                    return;
                }
                if( (columnSelected == 3) && (col3 == 0)){
                    rowSelected = 4;
                    return;
                }
                if( (columnSelected == 4) && (col4 == 0)){
                    rowSelected = 4;
                    return;
                }
            }break;
        }
        
    }    
}

unsigned char getKeyCode(){
    if(rowSelected == 1){
        switch(columnSelected){
            case 1: return '1';
            case 2: return '2';
            case 3: return '3';
            case 4: return 'A';
        }
    }
    else if(rowSelected == 2){
        switch(columnSelected){
            case 1: return '4';
            case 2: return '5';
            case 3: return '6';
            case 4: return 'B';
        }
    }
    else if(rowSelected == 3){
        switch(columnSelected){
            case 1: return '7';
            case 2: return '8';
            case 3: return '9';
            case 4: return 'C';
        }
    }
    else if(rowSelected == 4){
        switch(columnSelected){
            case 1: return '*';
            case 2: return '0';
            case 3: return '#';
            case 4: return 'D';
        }
    }
    return -1;
}

void pressedKeyAction(unsigned char keyCode){
    switch(keyCode){
        case '1': displayOne(); break;
        case '2': displayTwo(); break;
        case '3': displayThree(); break;
        case '4': displayFour(); break;
        case '5': displayFive(); break;
        case '6': displaySix(); break;
        case '7': displaySeven(); break;
        case '8': displayEight(); break;
        case '9': displayNine(); break;
        case '0': displayZero(); break;
        case '*': command(0x01); isReady(); DDRAMAddress=0; break;
        case '#': displaySOS(); break;
                
        //case '*': displayLineOnLCD(GREETING,11); break;
        //case '#': displayLineOnLCD(CASTELLO,11); break;
        default: displayCharOnLCD(keyCode);
    }
}

void pressedKey(){
    switch(PORTB){      //obtain the selected column
            case 0xE0: columnSelected = 1; break;
            case 0xD0: columnSelected = 2; break;
            case 0xB0: columnSelected = 3; break;
            case 0x70: columnSelected = 4; break;
        default: columnSelected = 100;
        }
        determinePressedRow();
        keyCode = getKeyCode();
        pressedKeyAction(keyCode);
    //pressedKeyAction(columnSelected);
}
