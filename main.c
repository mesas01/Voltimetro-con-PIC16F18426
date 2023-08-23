/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18426
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/device_config.h"
#include "utilities.h"
#include <math.h>

int currentDisplayDigit = 0;
uint16_t adc_value = 0;
float voltage = 0.000;
uint8_t digits[4] = {0, 0, 0, 0};
bool correccion;



void readADC(){
    // 1. Lectura del valor del ADC desde el canal/pin específico (0x05)
    adc_value = ADCC_GetSingleConversion(channel_ANA5);

    // 2. Conversión del valor crudo del ADC a un valor de voltaje.
    // La escala máxima es de 10V (asumido por el factor 10.0) y el ADC es de 12 bits (4095)
    voltage = (float)(adc_value * 10.00f) / 4095.0f; 
    
    // 3. Conversión del valor de voltaje a milivoltios para manejar valores enteros.
    uint16_t temp = (uint16_t)(voltage * 1000 + 0.5); 
  

    // 4. Descomposición del valor entero en dígitos individuales y almacenamiento en el array 'digits'
    for (int i = 0; i < 4; i++){
        digits[i] = temp % 10;  // Extrae el dígito más a la derecha
        temp /= 10;             // Desplaza los dígitos a la derecha
    }
}


void elegirNumero(int current_digit){
    //casos para elegir que numero se va a desplegar
    switch(digits[current_digit]){
        case 0:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetLow();// BIT A
            break;
        case 1:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetHigh();//BIT A
            break;
        case 2:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetHigh();// BIT B
            IO_RC0_SetLow();// BIT A
            break;
        case 3:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetHigh();// BIT B
            IO_RC0_SetHigh();// BIT A
            break;
        case 4:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetHigh();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetLow();// BIT A
            break;
        case 5:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetHigh();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetHigh();// BIT A
            break;
        case 6:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetHigh();// BIT C
            IO_RA0_SetHigh();// BIT B
            IO_RC0_SetLow();// BIT A
            break;
        case 7:
            IO_RA2_SetLow();// BIT D
            IO_RA1_SetHigh();// BIT C
            IO_RA0_SetHigh();// BIT B
            IO_RC0_SetHigh();// BIT A
            break;
        case 8:
            IO_RA2_SetHigh();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetLow();// BIT A
            break;
        case 9:
            IO_RA2_SetHigh();// BIT D
            IO_RA1_SetLow();// BIT C
            IO_RA0_SetLow();// BIT B
            IO_RC0_SetHigh();// BIT A
            break;            
    }
}


void elegirDisplay(int current_digit){
    switch(current_digit){
        case 0:
//            IO_RC5_SetHigh();
            IO_RC2_SetLow();// Apaga Q4
            elegirNumero(3);
            IO_RC1_SetHigh();  // Enciende Q1
//            IO_RC5_SetLow();
            break;
        case 1:
//            IO_RC5_SetHigh();
            IO_RC1_SetLow();// Apaga Q1
            elegirNumero(2);
            IO_RA4_SetHigh();  // Enciende Q2
//            IO_RC5_SetLow();
            break;
        case 2:
//            IO_RC5_SetHigh();
            IO_RA4_SetLow();// Apaga Q2
            elegirNumero(1);
            IO_RC3_SetHigh();  // Enciende Q3                        
//            IO_RC5_SetLow();
            break;
        case 3:
//            IO_RC5_SetHigh();
            IO_RC3_SetLow();// Apaga Q3
            elegirNumero(0);
            IO_RC2_SetHigh();  // Enciende Q4
//            IO_RC5_SetLow();
            break;
    }
}


void updateDisplay(){
    
    IO_RC1_SetLow();//d
    IO_RC2_SetLow();//c
    IO_RC3_SetLow();//b
    IO_RA4_SetLow();//a
    
    // Obten el valor BCD del dígito actual
    
//    IO_RC5_SetHigh();
    
    elegirDisplay(currentDisplayDigit); 
    
    //Avanzar al siguiente digito actual
    currentDisplayDigit++;
    if(currentDisplayDigit > 3){
        currentDisplayDigit = 0;
//        IO_RC5_SetLow();
    }
}


void EUSART1_Write_String(const char* str) {
    while (*str) {            // Mientras el carácter no sea el terminador de cadena (0)
        EUSART1_Write(*str);  // Envía el carácter actual
        str++;               // Avanza al siguiente carácter en la cadena
    }
}


void modoBajoConsumo(){
        
    IO_RC1_SetLow();//BJT D
    IO_RC2_SetLow();//BJT C
    IO_RC3_SetLow();//BJT B
    IO_RA4_SetLow();//BJT A
    
//    Encender para comprobar que se entra a la funcion y mandar por eusart
//    char buffer[10];
//    sprintf(buffer, "%.3f\n", voltage);
//    EUSART1_Write_String(buffer);
    
    while(!TX1STAbits.TRMT){}    
    //configura el watchdog timer
    WDTCON0bits.SEN = 1;
    //entra en modo sleep
    SLEEP();
    if(STATUSbits.nTO == 0){
        WDTCON0bits.SEN = 0;
    }
    bandera = 0;
}


void main() {

    // initialize the device
    SYSTEM_Initialize();
    /*ADCC_Initialize();
    EUSART1_Initialize();*/
    TMR2_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) {
        // El código principal simplemente se queda en este bucle.
        // Toda la lógica se maneja a través de la interrupción.
    }
}