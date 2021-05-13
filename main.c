/*
 * File:   main.c
 * Author: mane2
 *
 * Created on May 12, 2021, 2:58 PM
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
#include <stdlib.h>
#include <stdbool.h>

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

//	Function Prototypes
//int main(void);

int main(void) {
    uint32_t i;
    bool flag=true;
    //uint8_t* sData = (uint8_t*) malloc(sizeof(uint8_t)*256);
    //uint8_t* rData = (uint8_t*) malloc(sizeof(uint8_t)*256);
    uint8_t sData[256];
    uint8_t rData[256];
    
    InitSEE();
    
    //sector erase
    SectorErase(0x000000);
    
    for(i=0; i<256; i++){
        sData[i]=65;
    }
    
    for(i=0; i<256; i++){
        iWriteSEE(i, sData[i]); //starts at even addresses only 0, 2, 4, ...
    }
    
    for(i=0; i<256; i++){
        rData[i]=iReadSEE(i);
        
        if(rData[i]!=sData[i]){
            flag=false;
            break;
        }
    }
    while (1);
}



