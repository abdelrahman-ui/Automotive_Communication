#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H


void SPI_VidMasterInit(void);
void SPI_VidSlaveInit(void);
void SPI_VidChipSelect(u8);
u8 SPI_U8MasterTransmit(u8 Local_U8Data);
u8 SPI_U8SlaveReceive(void);


#endif /* SPI_INTERFACE_H */
