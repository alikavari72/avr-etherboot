#ifndef ETHERFLASH_H
#define ETHERFLASH_H

#include <avr/io.h>

struct UDP_SOCKET {
	unsigned long DestinationIP;
	unsigned int SourcePort;
	unsigned int DestinationPort;
	unsigned int Bufferfill;
	unsigned int DataStartOffset;
	uint8_t lineBufferIdx;
};

struct TFTP_RESPONSE
{
    uint16_t op;		//1		Message op code / message type
						//		1 = RRQ, 2 = WRQ, 3 = DATA, 4 = ACK, 5 = ERR
	union
	{
		uint16_t blockNumber;
		uint16_t errCode;
	};
	union
	{
		uint8_t *data;
		char *errMsg;
	};
};

void tftp_get (void) SEC_BOOTLOADER;
uint8_t hexToByte(uint8_t *buf, uint16_t idx) SEC_BOOTLOADER;
void writeFLASHPage(uint32_t currentAddress) SEC_BOOTLOADER;
void processLineBuffer(uint8_t bytes) SEC_BOOTLOADER;
void jumpToApplication(void) SEC_BOOTLOADER;



#define pApplication()     asm volatile ("call 0x00000"::)

#if defined (__AVR_ATmega2561__)
	#define pBootloader()      asm volatile ("call 0x3e000"::)
#endif
#if defined (__AVR_ATmega32__)
	#define pBootloader()      asm volatile ("call 0x7000"::)
#endif
#if defined (__AVR_ATmega644__)
	#define pBootloader()      asm volatile ("call 0xF000"::)
#endif


#endif