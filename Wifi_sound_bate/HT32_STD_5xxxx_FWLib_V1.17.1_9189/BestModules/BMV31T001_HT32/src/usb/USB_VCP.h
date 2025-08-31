#ifndef  _USB_Serial_H_
#define _USB_Serial_H_

#include <stdio.h>
//#include "ring_buffer.h"
#include "ht32_usbd_class.h"

void USBSerial_begin(unsigned long ignoreBaud);
void USBSerial_end(void) ;
int USBSerial_peek(void);
uint32_t USBSerial_read(uint8_t * buf, uint32_t len);
void USBSerial_flush(void);
int USBSerial_available(void);
size_t USBSerial_write(const uint8_t *buf, size_t len);
size_t USBSerial_write_byte(uint8_t ch);
uint32_t USBSerial_readBytes(uint8_t * buf, uint32_t len);
int USBSerial_available(void);
#endif
