@ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    afterbuild.bat
REM * @version $Rev:: 435          $
REM * @date    $Date:: 2025-06-17 #$
REM * @brief   After build script.
REM *************************************************************************************************************
REM * @attention
REM *
REM * Firmware Disclaimer Information
REM *
REM * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
REM *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
REM *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
REM *    other intellectual property laws.
REM *
REM * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
REM *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
REM *    other than HOLTEK and the customer.
REM *
REM * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
REM *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
REM *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
REM *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
REM *
REM * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
REM ************************************************************************************************************/

REM [Usage]
REM   Command:
REM                    %1   %2          %3      %4
REM     afterbuild.bat MODE OUTPUT_NAME IC_NAME "KEIL_PATH"
REM
REM   Parameter:      Keil Symbol HT32-IDE Symbol              Example         Description
REM                   =========== ============================ =============== ===============                 
REM     MODE        : -           -                            (*1)            Script Mode for Keil, Keil + GNU, or HT32-IDE 
REM     OUTPUT_NAME : @L          ${BuildArtifactFileBaseName} (*2)            Build output name
REM     IC_NAME     : $D          ${IC_NAME}                   (*3)            IC name
REM     KEIL_PATH   : "$J"        -                            (*4)            Keil include path for locate fromelf 
REM
REM     Note:
REM     *1. keil, keilgnu, ht32ide 
REM     *2. HT32, IAP, or IAP_AP
REM     *3. HT32F52352 or 52352
REM     *4. C:\Keil\ARM\ARMCC\include" or "C:\Keil\ARM\ARMCLANG\include" or "C:\Keil\ARM\Inc"  
REM
REM   Start Path:
REM     Keil       : __CODE_TYPE__\__APP_NAME__\__CODE_NAME__\__MDK_ARMTYPE__\
REM     Keil + GNU : __CODE_TYPE__\__APP_NAME__\__CODE_NAME__\GNU_ARM\
REM     HT32-IDE   : __CODE_TYPE__\__APP_NAME__\__CODE_NAME__\HT32-IDE\__PROJECT_NAME__\HT32\
REM
REM [Example - Keil]
REM   Command:
REM     .\afterbuild.bat keil @L $D "$J"
REM     .\afterbuild.bat keilgnu @L $D "$J"
REM     .\afterbuild.bat keil HT32 HT32F52352 "$J"
REM     .\afterbuild.bat keil IAP_AP 52352 "$J"
REM
REM   Start Path:
REM     example\GPIO\Input\GNU_ARM\
REM     example\GPIO\Input\MDK_ARMv5\
REM     application\IAP_HID\IAP_HID_III\MDK_ARMv537\
REM
REM [Example - HT32-IDE]
REM   Command:
REM     ..\..\afterbuild.bat ht32ide ${BuildArtifactFileBaseName} ${IC_NAME}
REM     ..\..\afterbuild.bat ht32ide HT32 HT32F52352
REM     ..\..\afterbuild.bat ht32ide IAP_AP 52352
REM 
REM   Start Path:
REM     example\GPIO\Input\HT32-IDE\Project_52352\HT32
REM     application\IAP_HID\IAP_HID_III\HT32-IDE\Project_52352_AP\HT32


REM Prepare Variable
REM ==================================================================================================
SET VAR_MODE=%1
SET VAR_OUTPUT_NAME=%2
SET VAR_IC_NAME=%3
SET VAR_KEIL_PATH=%4


REM Settings
REM ==================================================================================================
IF %VAR_MODE% EQU keil (
SET IN_PROJECT_PATH=
SET IN_OBJ_PATH=Obj
SET MID_NAME=.axf
SET TOOL_PATH=
SET DESC_PATH=
)
IF %VAR_MODE% EQU keilgnu (
SET IN_PROJECT_PATH=
SET IN_OBJ_PATH=Obj
SET MID_NAME=.axf
SET TOOL_PATH=
SET DESC_PATH=
SET GNU_PATH="C:\Program Files (x86)\Holtek HT32 Series\HT32-IDE\xPack\arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi\bin"
)
IF %VAR_MODE% EQU ht32ide (
SET IN_PROJECT_PATH=
SET IN_OBJ_PATH=HT32
SET MID_NAME=
SET TOOL_PATH=
SET DESC_PATH=
)


REM Find the correct IC Name (Example: HT32F52352 to 52352)
REM ==================================================================================================
setlocal EnableDelayedExpansion

IF %VAR_MODE% EQU keil (
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.axf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-5!"
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.axf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-4!"
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.axf GOTO SKIP_NAME_PRCESS1
)
IF %VAR_MODE% EQU keilgnu (
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-5!"
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-4!"
IF EXIST .\HT32\!VAR_IC_NAME!\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
)
IF %VAR_MODE% EQU ht32ide (
IF EXIST ..\..\Project_!VAR_IC_NAME!%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-5!"
IF EXIST ..\..\Project_!VAR_IC_NAME!%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
SET "VAR_IC_NAME=!VAR_IC_NAME:~-4!"
IF EXIST ..\..\Project_!VAR_IC_NAME!%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%VAR_OUTPUT_NAME%.elf GOTO SKIP_NAME_PRCESS1
)
setlocal DisableDelayedExpansion
ECHO --------------------------------------------------------------------------------
ECHO   !!!  ERROR:
ECHO   !!!    Cannot find the correct IC Name, please check the IC_NAME parameter.
ECHO --------------------------------------------------------------------------------
REM exit will stop following script
exit
:SKIP_NAME_PRCESS1

IF %VAR_MODE% EQU keil (
SET SRC_PATH=.\HT32\%VAR_IC_NAME%\%IN_OBJ_PATH%
)
IF %VAR_MODE% EQU keilgnu (
SET SRC_PATH=.\HT32\%VAR_IC_NAME%\%IN_OBJ_PATH%
)
IF %VAR_MODE% EQU ht32ide (
SET SRC_PATH=.
)
setlocal DisableDelayedExpansion

IF %VAR_MODE% EQU keil (
REM Generate text file
REM ==================================================================================================
%VAR_KEIL_PATH%\..\bin\fromelf --text -c -o "%SRC_PATH%\%2%MID_NAME%.text" "%SRC_PATH%\%VAR_OUTPUT_NAME%.axf"
)

IF %VAR_MODE% EQU keilgnu (
REM Generate binary
REM ==================================================================================================
ECHO Creating binary file...
%GNU_PATH%\arm-none-eabi-objcopy.exe -O binary %SRC_PATH%\%VAR_OUTPUT_NAME%.elf %SRC_PATH%\%VAR_OUTPUT_NAME%.bin

REM Generate text file
REM ==================================================================================================
ECHO Creating disassemble/text file...
IF EXIST "%VAR_KEIL_PATH%\..\ARMCC" (
%VAR_KEIL_PATH%\..\ARMCC\bin\fromelf --text -c -o "%SRC_PATH%\%2%MID_NAME%.text" "%SRC_PATH%\%VAR_OUTPUT_NAME%.elf"
) ELSE (
%VAR_KEIL_PATH%\..\ARMCLANG\bin\fromelf --text -c -o "%SRC_PATH%\%2%MID_NAME%.text" "%SRC_PATH%\%VAR_OUTPUT_NAME%.elf"
)

%GNU_PATH%\arm-none-eabi-objdump.exe -S "%SRC_PATH%\%VAR_OUTPUT_NAME%.elf"  > "%SRC_PATH%\%VAR_OUTPUT_NAME%.text"
REM %GNU_PATH%\arm-none-eabi-size.exe "%SRC_PATH%\%VAR_OUTPUT_NAME%.elf"
)

IF %VAR_MODE% EQU ht32ide (
REM Generate binary
REM ==================================================================================================
ECHO Creating binary file...
arm-none-eabi-objcopy.exe -O binary %VAR_OUTPUT_NAME%.elf %VAR_OUTPUT_NAME%.bin

REM Generate text file
REM ==================================================================================================
ECHO Creating disassemble/text file...
arm-none-eabi-objdump.exe -S "%VAR_OUTPUT_NAME%.elf"  > "%VAR_OUTPUT_NAME%.text"
)


REM Add your code or process here
REM ==================================================================================================
REM ADD_YOUR_CODE_HERE
