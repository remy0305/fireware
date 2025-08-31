
#include "ht32.h"
#include "usb/ht32_usbd_class.h"
#include "usb/usb_init.h"
#include "usb/USB_VCP.h"



bool USBSerialisConnect;
static bool _hasBegun = false;
static bool _isBlocking = false;



//Roger Clark. Two new begin functions has been added so that normal Arduino Sketches that use Serial.begin(xxx) will compile.
void USBSerial_begin(unsigned long ignoreBaud)
{
volatile unsigned long removeCompilerWarningsIgnoreBaud = ignoreBaud;

  ignoreBaud = removeCompilerWarningsIgnoreBaud;
     if (_hasBegun)
        return;
    _hasBegun = true;
     USB_Serial();
}

void USBSerial_end(void) {
    _hasBegun = false;
}

int USBSerial_available(void)
{
     return USB_CDC_avilable();
}


uint32_t USBSerial_readBytes(uint8_t * buf, uint32_t len) {
    uint32_t rxed = 0;
    while (rxed < len) {
        rxed += USB_Serial_rx(buf + rxed, len - rxed);
    }

    return rxed;
}



size_t USBSerial_write_byte(uint8_t ch) {

    return USBSerial_write(&ch, 1);
}



size_t USBSerial_write(const uint8_t *buf, size_t len)
{
	 uint32_t txed; 
  if (!buf| !(USB_Connected() && USB_Configured()))
  {
    return 0;
  }
      txed = USBDClass_CDC_Tx((u8 *)buf , len);
  if (txed > 0) {
    return txed;
  } else {

    return 0;
  }
}
