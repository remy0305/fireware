/**
 @page USBD_HID_DemoVendorReport

 @verbatim
 * @file    USBD/HID_DemoVendorReport/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of USB Device HID example.
 @endverbatim

@par Example Description:

The USB Device HID example code which shows how to use the HT32 USB Device Library, enumeration, Endpoint
transfer (INTERRUPT Transfer), and HID Get/Set Report (CONTROL Transfer). This example defines 6 reports
including Input, Output, and Feature Report. The example simply loopback n bytes data from the HID Output
report to the Input report. The default setting of the reports and data flow is as below. The report size
large than 64 Bytes is also shown in this example (which can be used only in the CONTROL Transfer).

The HID Demo UI can be used to test all the reports. Please rename the file, "HID_Demo_UI.e_x_e" as
"HID_Demo_UI.exe" and execute it. The default setting can be found in the screenshot,
"HID_Demo_UI_setting.png".

Notice that some OS will ask the USB device to enter the suspend mode if no communication is ongoing between
the USB host and USB device (no opened handler by UI). The device will be resume automatically once the UI
connects to the USB device (open a handler).

<PRE>

  Default Report Settings:

  Report ID (RPT_ID_n)     Type (RPT_TYPE_n)       Length in Byte (RPT_LEN_n)
  =====================    ==================      ============================
    0x1                      INPUT                   768
    0x2                      INPUT                   32
    0x3                      OUTPUT                  768
    0x4                      OUTPUT                  32
    0x5                      FEATURE                 63
    0x6                      FEATURE                 32

  Data Flow:

  Host                             Dir     Device
  ==========                       ====    ==========
  CONTROL Transfer
    Set Output Report   (ID=3)      ->       Save to gRPT_Buffer3[] and copy to gRPT_Buffer1[] (By "USBDClass_ReportProcess()")
    Set Output Report   (ID=4)      ->       Save to gRPT_Buffer4[] and copy to gRPT_Buffer2[] (By "USBDClass_ReportProcess()")
    Get Input Report    (ID=1)      <-       Transmit data from gRPT_Buffer1[]
    Get Input Report    (ID=2)      <-       Transmit data from gRPT_Buffer2[]
    Set Feature Report  (ID=5)      ->       Save to gRPT_Buffer5[]
    Set Feature Report  (ID=6)      ->       Save to gRPT_Buffer6[]
    Get Feature Report  (ID=5)      <-       Transmit data from gRPT_Buffer5[]
    Get Feature Report  (ID=6)      <-       Transmit data from gRPT_Buffer6[]

  INTERRUPT Transfer (Report length must <= 64 Bytes)
    Write Output Report (ID=4)      ->       Save to gRPT_Buffer4[] and copy to gRPT_Buffer2[] (By "USBDClass_EPT1INProcess()")
    Read Input Report   (ID=2)      <-       Transmit data from gRPT_Buffer2[]

</PRE>

The related settings can be found in the file, "ht32_usbd_class.h" and shown as below.

<PRE>

  1. Usage Page: USAGE_PAGE_L
     The low byte of the Usage page located at "USB_HID_ReportDesc[]". The PC UI use this parameter to find
     the interface of the HID device.

  2. Report Enable Control: RPT_EN_n
     Control the Report Descriptor of each report is included in the "USB_HID_ReportDesc[]" or not. Notice
     that it simply changes the content of the "USB_HID_ReportDesc[]", the control logic/code is not affected
     by the "RPT_EN_n".

  3. Report ID: RPT_ID_n
     The report ID of each report. It is used by the "USB_HID_ReportDesc[]".

  4. Report Length: RPT_LEN_n
     The report length of each report.

  5. Report Type: RPT_TYPE_n
     The report type of each report. It is used by the "USB_HID_ReportDesc[]". Notice that it simply changes
     the content of the "USB_HID_ReportDesc[]", you shall modify the "USBDClass_GetReport()",
     "USBDClass_SetReport()" if you change the type.
       RPT_TYPE_n = 0x81: INPUT Report
       RPT_TYPE_n = 0x91: OUTPUT Report
       RPT_TYPE_n = 0xb1: FEATURE Report

</PRE>

@par Directory Contents:

- USBD/HID_DemoVendorReport/main.c                          Main program
- USBD/HID_DemoVendorReport/ht32fxxxxx_nn_it.c              Interrupt handlers
- USBD/HID_DemoVendorReport/ht32fxxxxx_nn_usbdconf.h        USB Device Library configuration file
- USBD/HID_DemoVendorReport/ht32_usbd_class.c               USB Device Class related function
- USBD/HID_DemoVendorReport/ht32_usbd_class.h               Header file of the USB Device Class
- USBD/HID_DemoVendorReport/ht32_usbd_descriptor.c          Descriptor of USB Device
- USBD/HID_DemoVendorReport/ht32_usbd_descriptor.h          Header file of the USB Device Descriptor
- USBD/HID_DemoVendorReport/HID_Demo_UI.e_x_e               HID Demo UI
- USBD/HID_DemoVendorReport/HID_Demo_UI_setting.png         Settings screenshot of HID Demo UI

@par Hardware and Software Environment:

- This example can be run on HT32 Series development kit.
- This example uses the following endpoints.
<PRE>
  Endpoint    Transfer Type         Buffer Length
  ========    ====================  ==============
  0           Control               64 bytes
  1           Interrupt IN          64 bytes
  2           Interrupt OUT         64 bytes
</PRE>

Please create a project according to the project_template and add the following extra source files into it.
- ht32_usbd_class.c
- ht32_usbd_descriptor.c

@par Low Power mode:

For the convenient during debugging and evaluation stage, the USBDCore_LowPower() in the main.c is map to
a null function by default. In the real product, you must map this function to the low power function of
firmware library by setting USBDCORE_ENABLE_LOW_POWER as 1 (in the ht32fxxxx_usbdconf.h file).

@par USB Library debug mode:

For debug purpose, your can turn on the USB Library debug mode by setting "USBDCORE_DEBUG" definition
value as 1 (which located at ht32_usbd_core.h). The debug message will be shown via the printf function
to the UART or ITM interface according to the retarget setting of firmware library.

NOTE THAT USB DEBUG MODE DEGRADES THE PERFORMANCE AND MAY CAUSE USB ERROR UNDER SOME CONDITIONS.

You shall turn off the USB debug mode on your final application. We strongly recommend turn off the
"Dump USB Debug data (USBDCORE_DEBUG_DATA)" option when you enable the USB debug mode and retarget the
message to UART.

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
