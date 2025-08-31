/*----------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                                */
/*                                                                                                          */
/* Copyright (C) Holtek Semiconductor Inc.                                                                  */
/* All rights reserved.                                                                                     */
/*                                                                                                          */
/*------------------------------------------------------------------------------------------------------------
  File Name        : readme e-Link32 Pro.txt
  Version          : V1.00
  Date             : 2020-08-07
  Description      : Description about how to use e-Link32 Pro with SEGGER Embedded Studio.
------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------*/
/* Requirements                                                                                             */
/*----------------------------------------------------------------------------------------------------------*/
  + SEGGER Embedded Studio 4.22 or later
    !!! NOTICE !!!
    SEGGER Embedded Studio 5.44 ~ 5.50d has some issues with pyOCD which causes the programming not to work.
    Please do not use those versions or upgrade to the latest version of SEGGER Embedded Studio.
  + Python 3.6.0 or later (preferred), or Python 2.7.9 or later
  + Windows 7 or newer (Windows 10 preferred)
  + pyOCD
  + e-Link32 Pro or e-Link32 Lite (Starter Kit on board debug adapter)
  + HT32 Starter Kit or any HT32 target board

/*----------------------------------------------------------------------------------------------------------*/
/* How to Use                                                                                               */
/*----------------------------------------------------------------------------------------------------------*/
  1. Install Python

     Download Python 3.6.0 or later from the Web site and install it.
     https://www.python.org/downloads/

     Notice
     1. Please enable "Add Python x.x to PATH" option.
     2. We recommended to use the default install setting, do not enable "Install for all users" to
        prevent windows PATH issue.


  2. Install pyOCD

     Open a Windows Command Prompt by "Start -> typing cmd -> Command Prompt" (for Win 10),
     then input the below command.

     "pip install -U pyocd"


  3. Open Project and Test

     Open the project file of SEGGER Embedded Studio by executing the batch file, "Project_xxxxx.bat" below.

     "\\HT32_STD_xxxxx_FWLib_vnnn_mmm\project_template\IP\Example\emStudiov4\Project_xxxxx.bat"

     Notice
     1. You must use the batch file, "Project_xxxxx.bat" to open the Project since it helps to start the
        GDB Server for debugging and Flash programming.

     If everything is OK, build and enter the debug mode, the Flash will be programmed automatically and
     then you can start debugging your application. You can also see the GDB Server message like below to
     confirm everything is fine.

     ---------------------------------------------------------------------------------------------------------
     0000659:INFO:board:Target type is ht32f12366
     0000799:INFO:dap:DP IDR = 0x2ba01477 (v1 rev2)
     0000809:INFO:ap:AHB-AP#0 IDR = 0x24770011 (AHB-AP var1 rev2)
     0000840:INFO:rom_table:AHB-AP#0 Class 0x1 ROM table #0 @ 0xe00ff000 (designer = 000 part = 000)
     0000853:INFO:rom_table:[0] < e000e000:SCS-M3 class = 14 designer = 43b part = 000>
     0000859:INFO:rom_table:[1] < e0001000:DWT class = 14 designer = 43b part = 002>
     0000869:INFO:rom_table:[2] < e0002000:FPB class = 14 designer = 43b part = 003>
     0000869:INFO:rom_table:[3] < e0000000:ITM class = 14 designer = 43b part = 001>
     0000879:INFO:rom_table:[4] < e0040000:TPIU-M3 class = 9 designer = 43b part = 923 devtype = 11 archid = 0000 devid = ca0:0:0>
     0000879:INFO:cortex_m:CPU core #0 is Cortex-M3 r2p0
     0000899:INFO:dwt:4 hardware watchpoints
     0000899:INFO:fpb:6 hardware breakpoints, 4 literal comparators
     0000929:INFO:server:Semihost server started on port 4444 (core 0)
     0000929:INFO:gdbserver:GDB server started on port 3333 (core 0)
     0013520:INFO:gdbserver:One client connected!
     [====================] 100%
     0014460:INFO:loader:Erased 3584 bytes (7 sectors), programmed 3584 bytes (7 pages), skipped 0 bytes (0 pages) at 4.86 kB/s
     ---------------------------------------------------------------------------------------------------------
