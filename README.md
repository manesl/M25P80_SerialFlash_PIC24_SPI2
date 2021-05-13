# M25P80_SerialFlash_PIC24_SPI2
Using SPI2 of PIC24 to access onboard 1MB Serial Flash (M25P80)

The SPI2 uses PIN C2 to select the serial flash as a slave. 
The other pins like SCK, MOSI, MISO are handled by the module.
When we pull C2 as low, we can send commands and data to M25P80 (1MB serial flash).

Things to Note: 
1) ANSELC and ANSELG registers must be set to digital output.
2) CKE=0, CKP=0 and CKE=1, CKP=1 do not work.
3) There is upper limit on the speed of SPI for all configurations of CKE, CKP, and SMP bits (check technical referenc manaul). 
4) There is a protocol or steps to send data to the serail flash. This is mentioned neatly in the M25P80 manaul. For example, writing to a memory location requires following steps:
  -Chip select line must be low
  -WEL bit in the status register must be set (Write Enable)
  -3 bytes of address must be sent
  -1 data byte must be sent
  -Chip select line must be high
  
