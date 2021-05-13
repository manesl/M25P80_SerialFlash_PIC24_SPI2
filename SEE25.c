/*
 * File:   main.c
 * Author: mane2
 *
 * Created on May 9, 2021, 10:22 PM
 */

/******************************************************************************
 * Software License Agreement
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED Ã¬AS ISÃ® WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/


#if defined(__PIC24E__) 
#include <p24Exxxx.h>
#include "SEE.h"
#elif defined (__PIC24F__) 
#include <p24Fxxxx.h>

#elif defined(__PIC24H__)
#include <p24Hxxxx.h>

#elif defined(__dsPIC30F__)
#include <p30Fxxxx.h>

#elif defined (__dsPIC33E__) 
#include <p33Exxxx.h>

#elif defined(__dsPIC33F__) 
#include <p33Fxxxx.h>

#endif

void InitSEE (void){
    ANSELC = 0; //making all digital
    ANSELG = 0;
    TCSEE = 0; //making the pin as output
    CSEE = 1;
    SPI2CON1 = SPI_MASTER;
    SPI2STAT = SPI_ENABLE; //enabling the module
}

uint8_t WriteSPI2(uint8_t data){
    SPI2BUF = data; 
    while(!SPI2STATbits.SPIRBF); //wait until receive is complete
    return SPI2BUF;
}

uint8_t ReadSR(){
    int i;
    CSEE = 0;
    WriteSPI2(SEE_RDSR);
    i = WriteSPI2(0);
    CSEE = 1;
    return i;
}

uint8_t iReadSEE(uint32_t address){
    uint8_t data;
    while(ReadSR() & 0x1); //to check previous WIP is complete
    CSEE = 0;
    WriteSPI2(SEE_READ);
    WriteSPI2(address>>16);
    WriteSPI2(address>>8);
    WriteSPI2(address);
    data = WriteSPI2(0);
    CSEE = 1;
    return data;
}

void WriteEnable(void){
    CSEE = 0;
    WriteSPI2(SEE_WEN);
    CSEE = 1;
}

void iWriteSEE(uint32_t address, uint8_t data){
    while(ReadSR() & 0x1); //to check previous WIP is complete
    WriteEnable();
    CSEE = 0;
    WriteSPI2(SEE_WRITE);
    WriteSPI2(address>>16);
    WriteSPI2(address>>8);
    WriteSPI2(address);
    WriteSPI2(data);
    CSEE = 1;
}

void SectorErase(uint32_t address){
    while(ReadSR() & 0x1); //to check previous WIP is complete
    WriteEnable();
    CSEE = 0;
    WriteSPI2(SEE_ERASE_SEC);
    WriteSPI2(address>>16);
    WriteSPI2(address>>8);
    WriteSPI2(address);
    CSEE = 1;
}


