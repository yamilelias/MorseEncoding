/*
 * File:   morse.c
 * Author: Yamil Elías
 *
 * Created on 7 de mayo de 2016, 10:55 AM
 */


#include <xc.h>
#include "functions.h" // Include our functions header file
#include <string.h>

// CONSTANTS
//==========
unsigned char unoMorse[] = ".---- ";
unsigned char dosMorse[] = "..--- ";
unsigned char tresMorse[] = "...-- ";
unsigned char cuatroMorse[] = "....- ";
unsigned char cincoMorse[] = "..... ";
unsigned char seisMorse[] = "-.... ";
unsigned char sieteMorse[] = "--... ";
unsigned char ochoMorse[] = "---.. ";
unsigned char nueveMorse[] = "----. ";
unsigned char ceroMorse[] = "----- ";
unsigned char SOSMorse[] = "...---...";
unsigned char SOS[] = "SOS";

unsigned char DDRAMAddress = 0; // This is too watch out for pointer position

unsigned char keyCode;

void decode(unsigned char caracter[])
{
    shortDelay();
    displayCharOnLCD(' ');      //Space between numbers and Morse characters
    DDRAMAddress++;
    checkDDRAM();
    DDRAMAddress++;
    checkDDRAM();
    
    for (unsigned char i = 0; i < strlen(caracter); i++)
    {
        if (caracter[i] == '.')
        {
            buzzerShort();
            displayCharOnLCD('.');
            DDRAMAddress++; 
            checkDDRAM();
        }
        
        if (caracter[i] == '-')
        {
            buzzerLong();
            displayCharOnLCD('-');
            DDRAMAddress++;
            checkDDRAM();
        }
    }
}

void displayOne(void){
    displayCharOnLCD(keyCode);
    decode(unoMorse);
}

void displayTwo(void){
    displayCharOnLCD(keyCode);
    decode(dosMorse);
}

void displayThree(void){
    displayCharOnLCD(keyCode);
    decode(tresMorse);
}

void displayFour(void){
    displayCharOnLCD(keyCode);
    decode(cuatroMorse);
}

void displayFive(void){
    displayCharOnLCD(keyCode);
    decode(cincoMorse);
}

void displaySix(void){
    displayCharOnLCD(keyCode);
    decode(seisMorse);
}

void displaySeven(void){
    displayCharOnLCD(keyCode);
    decode(sieteMorse);
}

void displayEight(void){
    displayCharOnLCD(keyCode);
    decode(ochoMorse);
}

void displayNine(void){
    displayCharOnLCD(keyCode);
    decode(nueveMorse);
}

void displayZero(void){
    displayCharOnLCD(keyCode);
    decode(ceroMorse);
}

void displaySOS(void){
    displayLineOnLCD(SOS, 3);
    DDRAMAddress++;
    checkDDRAM();
    DDRAMAddress++;
    checkDDRAM();
    DDRAMAddress++;
    checkDDRAM();
    decode(SOSMorse);
    //command(0xC0);
}

void checkDDRAM(){
    if (DDRAMAddress == 14){
        command(0xC0);
    }
    if (DDRAMAddress >= 28){
        command(0x80);
        DDRAMAddress = 0;
    }
}