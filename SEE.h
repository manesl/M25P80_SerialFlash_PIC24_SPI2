/* 
 * File:   SEE.h
 * Author: mane2
 *
 * Created on May 12, 2021, 2:53 PM
 */

#ifndef SEE_H
#define	SEE_H

#ifdef	__cplusplus
extern "C" {
#endif

// Constants
#define SPI_MASTER 0x007C//0x007C//0x0078//0x013C
#define SPI_ENABLE 0x8000
#define CSEE _LATC2
#define TCSEE _TRISC2

// M25P80 command set
#define SEE_WRSR (unsigned)0x01 //write status reg
#define SEE_WRITE (unsigned)0x02 //write command
#define SEE_READ (unsigned)0x03 //read command
#define SEE_WDI (unsigned)0x04 //write disable
#define SEE_RDSR (unsigned)0x05 //read status reg
#define SEE_WEN (unsigned)0x06 //write enable
#define SEE_ERASE_SEC (unsigned)0xD8
// Functions
void InitSEE (void);
//int WriteSPI2(int data);
//int ReadSR();
uint8_t iReadSEE(uint32_t address);
//void WriteEnable(void);
void iWriteSEE(uint32_t address, uint8_t data);

void SectorErase(uint32_t address);

#ifdef	__cplusplus
}
#endif

#endif	/* SEE_H */
