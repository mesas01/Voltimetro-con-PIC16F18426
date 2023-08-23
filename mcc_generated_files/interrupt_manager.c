/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18426
        Driver Version    :  2.04
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above or later
        MPLAB 	          :  MPLAB X 6.00
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

#include "interrupt_manager.h"
#include "mcc.h"
#include <stdio.h>
#include <pic16f18426.h>
#include "C:\Users\mesas\MPLABXProjects\VoltimetroFuncional.X\utilities.h"
bool bandseg = 0;
int bandera = 0;

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else if(INTCONbits.PEIE == 1)
    {
        // Interrupción del Timer 2 (TMR2)
        if(PIE4bits.TMR2IE == 1 && PIR4bits.TMR2IF == 1)
        {
            WDTCON0bits.SEN = 1;
            //IO_RC5_SetHigh();//pin para medir tiempos
            
            // Código personalizado para manejar la interrupción del Timer 2
            // Actualiza la visualización de los displays
            updateDisplay();       
            
            // Se ejecuta cada vez que pasa 1 segundo del TMR0
            if (bandseg){
                //espera a que se haga la conversion del adc para seguir
                while(!TX1STAbits.TRMT){
                }
//                IO_RC5_SetHigh();
                // Lee el valor del ADC y realiza las conversiones necesarias
                readADC();
//                IO_RC5_SetLow();
                
                // si voltaje es menor que 0.1 activa la bandera para modo sleep
                if(voltage <= 0.1){
                    bandera = 1;
                }
                if(bandera == 1){
                    modoBajoConsumo();
                }
                
//                IO_RC5_SetHigh();
                //Crea un buffer para almacenar el valor de voltaje
                char buffer[10];
                //activar la siguiente linea para mandar el voltaje en miles y no con punto
                //uint16_t temp = (uint16_t)(voltage * 1000 +0.5);
                //imprime el estado de la bandera
                //sprintf(buffer,"%d", bandera);
                sprintf(buffer, "%.3f\n", voltage);
//                IO_RC5_SetLow();
                
                //Envía el valor de voltaje a través de EUSART1
                EUSART1_Write_String(buffer);
                
                bandseg = 0;
            }
            
            // Limpia la bandera de interrupción del Timer 2
            PIR4bits.TMR2IF = 0;
            //IO_RC5_SetLow();            
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
