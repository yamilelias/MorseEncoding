//==================================================================================
//|| PROYECTO FINAL DE MICROCONTROLADORES                                         ||
//||                                                                              ||
//|| Proyecto: Clave SHAVO                                                        ||
//|| Clase: Main                                                                  ||
//|| Profesor: Dr. Rodolfo Castelló                                               ||
//|| Integrantes: Jonathan Torres, Dilan Coss, Yamil Elías                        ||
//|| Escuela: Instituto Tecnológico de Estudios Superiores de Monterrey           ||
//==================================================================================

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef functions_header
#define functions_header

//#include <xc.h> // include processor files - each processor file is guarded.  

// Matrix keyboard functions
void groundAllRows(void);
void oneShot(void);
void resetOneShot(void);
void delay(void);
void turnOnAllRows(void);
void determinePressedRow(void);
unsigned char getKeyCode(void);
void pressedKeyAction(unsigned char);
void pressedKey(void);
void command (unsigned char);

// Buzzer functions
void buzzerShort(void);
void buzzerLong(void);
void shortBuzzerDelay(void);
void longBuzzerDelay(void);
 
// Morse functions
void displayOne(void);
void displayTwo(void);
void displayThree(void);
void displayFour(void);
void displayFive(void);
void displaySix(void);
void displaySeven(void);
void displayEight(void);
void displayNine(void);
void displayZero(void);
void displaySOS(void);
void decode(unsigned char caracter[]);
void checkDDRAM(void);

void displayCharOnLCD(unsigned char character);
void displayLineOnLCD(unsigned char array[], unsigned char sizeOfArray);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

