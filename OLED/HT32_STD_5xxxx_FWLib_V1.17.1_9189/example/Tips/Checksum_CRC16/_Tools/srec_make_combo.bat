@ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    srec_make_combo.bat
REM * @version $Rev:: 439          $
REM * @date    $Date:: 2025-06-18 #$
REM * @brief   Add CRC checksum into hex and binary and encrypt AP image.
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
REM                         %1   %2          %3      %4
REM     srec_make_combo.bat MODE OUTPUT_NAME IC_NAME "KEIL_PATH"
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
REM     ..\Tools\srec_make_combo.bat keil @L $D "$J"
REM     ..\Tools\srec_make_combo.bat keilgnu @L $D "$J"
REM     ..\Tools\srec_make_combo.bat keil HT32 HT32F52352 "$J"
REM     ..\Tools\srec_make_combo.bat keil IAP_AP 52352 "$J"
REM
REM   Start Path:
REM     example\GPIO\Input\GNU_ARM\
REM     example\GPIO\Input\MDK_ARMv5\
REM     application\IAP_HID\IAP_HID_III\MDK_ARMv537\
REM
REM [Example - HT32-IDE]
REM   Command:
REM     ..\..\..\Tools\srec_make_combo.bat ht32ide ${BuildArtifactFileBaseName} ${IC_NAME}
REM     ..\..\..\Tools\srec_make_combo.bat ht32ide HT32 HT32F52352
REM     ..\..\..\Tools\srec_make_combo.bat ht32ide IAP_AP 52352
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
SET APSEQ=1
SET APSAVE_ENDADDR=0
SET BIN_OFFSET=0
SET CMP_RESULT=0
SET SHOW_CRC_CHECK_MSG=0
SET HEX_ENCODE=0
SET AP_ENCRYPT=0

IF %VAR_MODE% EQU keil (
SET IN_PROJECT_PATH=
SET IN_OBJ_PATH=Obj
SET TOOL_PATH=..\_Tools

SET IN_FILE_AXFELF=%VAR_OUTPUT_NAME%.axf
SET IN_FILE_HEX=%VAR_OUTPUT_NAME%.hex
SET IN_FILE_BIN=%VAR_OUTPUT_NAME%.axf.bin

SET OUT_FILE_CRC_HEX=%VAR_OUTPUT_NAME%_CRC.hex
SET OUT_FILE_CRC_BIN=%VAR_OUTPUT_NAME%_CRC.bin

SET LOAD_IAP_FILE=NULL
)

IF %VAR_MODE% EQU ht32ide (
SET IN_PROJECT_PATH=
SET IN_OBJ_PATH=HT32
SET TOOL_PATH=..\..\..\_Tools

SET IN_FILE_AXFELF=%VAR_OUTPUT_NAME%.elf
SET IN_FILE_HEX=%VAR_OUTPUT_NAME%.hex
SET IN_FILE_BIN=%VAR_OUTPUT_NAME%.bin

SET OUT_FILE_CRC_HEX=%VAR_OUTPUT_NAME%_CRC.hex
SET OUT_FILE_CRC_BIN=%VAR_OUTPUT_NAME%_CRC.bin
)


REM Find the correct IC Name
REM ==================================================================================================
SET ICNAME=%VAR_IC_NAME%
IF %VAR_MODE% EQU keil (
SET IN_FULL_HEX=.\HT32\%ICNAME%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)
IF %VAR_MODE% EQU ht32ide (
SET IN_FULL_HEX=..\..\Project_%ICNAME%%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)

IF EXIST %IN_FULL_HEX% GOTO SKIP_NAME_PRCESS1
SET "ICNAME=%ICNAME:~-5%"
IF %VAR_MODE% EQU keil (
SET IN_FULL_HEX=.\HT32\%ICNAME%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)
IF %VAR_MODE% EQU ht32ide (
SET IN_FULL_HEX=..\..\Project_%ICNAME%%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)
IF EXIST %IN_FULL_HEX% GOTO SKIP_NAME_PRCESS1
SET "ICNAME=%ICNAME:~-4%"
IF %VAR_MODE% EQU keil (
SET IN_FULL_HEX=.\HT32\%ICNAME%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)
IF %VAR_MODE% EQU ht32ide (
SET IN_FULL_HEX=..\..\Project_%ICNAME%%IN_PROJECT_PATH%\%IN_OBJ_PATH%\%IN_FILE_HEX%
)
IF EXIST %IN_FULL_HEX% GOTO SKIP_NAME_PRCESS1
ECHO --------------------------------------------------------------------------------
ECHO   !!!  ERROR:
ECHO   !!!    Cannot find the correct IC Name, please check the IC_NAME parameter.
ECHO --------------------------------------------------------------------------------
REM exit will stop following script
exit
:SKIP_NAME_PRCESS1

setlocal EnableDelayedExpansion

REM Prepare related settings
REM ==================================================================================================
IF %VAR_MODE% EQU keil (
SET IN_FULL_PATH=.\HT32\%ICNAME%\%IN_OBJ_PATH%
SET LOAD_IAP_FILE=.\HT32\%ICNAME%\IAP\Obj\%LOAD_IAP_FILE%

REM Generate text file
REM ==================================================================================================
%VAR_KEIL_PATH%\..\bin\fromelf --text -c -o "!IN_FULL_PATH!\%IN_FILE_AXFELF%.text" "!IN_FULL_PATH!\%IN_FILE_AXFELF%"


REM Write ini files for Keil
REM ==================================================================================================
ECHO LOAD !IN_FULL_PATH!\%OUT_FILE_CRC_HEX% > CRC_LOAD.ini
IF !LOAD_IAP_FILE! NEQ NULL ECHO LOAD !LOAD_IAP_FILE! INCREMENTAL > IAP_LOAD.ini
)

IF %VAR_MODE% EQU ht32ide (
SET IN_FULL_PATH=.
)

REM Prepare the SREC tools
REM ==================================================================================================
SET TMP_SIZE_FILE=srec_size.txt
SET TMP_ADDR1=srec_make_addr1.txt
SET TMP_ADDR2=srec_make_addr2.txt
SET TMP_CRC=srec_make_crc.txt

SET SREC_INFO=%TOOL_PATH%\SRecord\srec_info.exe
SET SREC_CAT=%TOOL_PATH%\SRecord\srec_cat.exe
SET SREC_CMP=%TOOL_PATH%\SRecord\srec_cmp.exe

REM Find the Image address
REM ==================================================================================================
REM -----------------------------------------------
REM srec_info.exe output Example:
REM Data:   0000 - 18AF    APSEQ=1, IAP or Dual Image AP     tokens=2 & 4
REM         2800 - 280B    APSEQ=2, VER
REM         2A00 - 45CF    APSEQ=3, AP                       tokens=1 & 3
REM -----------------------------------------------
REM ==================================================================================================
%SREC_INFO% %IN_FULL_PATH%\%IN_FILE_HEX% -intel > %TMP_SIZE_FILE%
FINDSTR /R /C:" - " %TMP_SIZE_FILE%>%TMP_ADDR1%

set strOld=Data:
set strNew=

setlocal enabledelayedexpansion

REM Remove "Data:"
for /f "tokens=*" %%j in (%TMP_ADDR1%) do (
  set "tmp1=%%j"
  if not !tmp1!.==. (
    set "tmp1=!tmp1:%strOld%=%strNew%!"
    echo !tmp1!>>%TMP_ADDR2%
  )
)

SET AP_ADR_TMP=0

SET cnt=0
FOR /F "tokens=1 delims= " %%a in (%TMP_ADDR2%) do call :GETADR %%a
SET AP_ST_ADDR=%AP_ADR_TMP%
SET AP_ST2=%AP_ST_ADDR:~0,-2%
SET "AP_ST_ADDR=0000000%AP_ST_ADDR%"
SET "AP_ST_ADDR=%AP_ST_ADDR:~-8%"
SET AP_STA=0x%AP_ST_ADDR%

SET cnt=0
FOR /F "tokens=3 delims= " %%a in (%TMP_ADDR2%) do call :GETADR %%a
SET AP_END_ADDR=%AP_ADR_TMP%
SET "AP_END=0000000%AP_END_ADDR%"
SET "AP_END=%AP_END:~-8%"

SET AP_END1=0x%AP_END_ADDR%
SET /A AP_END1=%AP_END1%+1
SET /A AP_LEN=%AP_END1%-%AP_STA%

SET Input=%AP_LEN%
CALL :DEC2HEX
SET AP_LEN_HEX=%retvalue%

SET "AP_LEN_HEX=0000000%AP_LEN_HEX%"
SET "AP_LEN_HEX=%AP_LEN_HEX:~-8%"

IF %APSAVE_ENDADDR% EQU 1 (
SET AP_SAVE=%AP_END%
GOTO SAVE_SKIP
)
SET AP_SAVE=%AP_LEN_HEX%

:SAVE_SKIP
SET AP_3=%AP_SAVE:~0,2%
SET AP_2=%AP_SAVE:~2,2%
SET AP_1=%AP_SAVE:~4,2%
SET AP_0=%AP_SAVE:~6,2%

ECHO --------------------------------------------------------------------------------
ECHO   AP Start/End Address  = %AP_STA% ~ 0x%AP_END% (Length = %AP_LEN%, 0x%AP_LEN_HEX%)
ECHO   Input Hex file        = %IN_FULL_PATH%\%IN_FILE_HEX%
ECHO   Input Binary file     = %IN_FULL_PATH%\%IN_FILE_BIN%
ECHO --------------------------------------------------------------------------------

IF %BIN_OFFSET% EQU 1 SET AP_STB=%AP_ST2%

REM Use SREC CAT to get CRC value, and write to output files
REM ==================================================================================================
%SREC_CAT% %IN_FULL_PATH%\%IN_FILE_HEX% -intel -crop %AP_STA% %AP_END1% ^
-exclude 0x%AP_ST2%28 0x%AP_ST2%2C 0x%AP_ST2%34 0x%AP_ST2%38 ^
-fill 0xFF 0x%AP_ST2%28 0x%AP_ST2%29 ^
-fill 0xFF 0x%AP_ST2%29 0x%AP_ST2%2a ^
-fill 0xFF 0x%AP_ST2%2a 0x%AP_ST2%2b ^
-fill 0xFF 0x%AP_ST2%2b 0x%AP_ST2%2c ^
-fill 0xFF 0x%AP_ST2%34 0x%AP_ST2%35 ^
-fill 0xFF 0x%AP_ST2%35 0x%AP_ST2%36 ^
-fill 0xFF 0x%AP_ST2%36 0x%AP_ST2%37 ^
-fill 0xFF 0x%AP_ST2%37 0x%AP_ST2%38 ^
-CRC16_Little_Endian 0x10000000 -XMODEM -crop 0x10000000 0x10000004 -byte-swap 4 -o -hex-dump > %TMP_CRC%
FOR /F "tokens=2 delims= " %%a in (%TMP_CRC%) do set CRCV1=%%a
FOR /F "tokens=3 delims= " %%a in (%TMP_CRC%) do set CRCV2=%%a
ECHO   CRC value             = 0x%CRCV1%%CRCV2%

%SREC_CAT% %IN_FULL_PATH%\%IN_FILE_HEX% -intel -crop 0x0 0 ^
-exclude 0x%AP_ST2%28 0x%AP_ST2%2C 0x%AP_ST2%34 0x%AP_ST2%38 ^
-fill 0x%CRCV2% 0x%AP_ST2%28 0x%AP_ST2%29 ^
-fill 0x%CRCV1% 0x%AP_ST2%29 0x%AP_ST2%2a ^
-fill 0x0C      0x%AP_ST2%2a 0x%AP_ST2%2b ^
-fill 0x1A      0x%AP_ST2%2b 0x%AP_ST2%2c ^
-fill 0x%AP_0%  0x%AP_ST2%34 0x%AP_ST2%35 ^
-fill 0x%AP_1%  0x%AP_ST2%35 0x%AP_ST2%36 ^
-fill 0x%AP_2%  0x%AP_ST2%36 0x%AP_ST2%37 ^
-fill 0x%AP_3%  0x%AP_ST2%37 0x%AP_ST2%38 ^
-o %IN_FULL_PATH%\%OUT_FILE_CRC_HEX% -intel

%SREC_CAT% %IN_FULL_PATH%\%IN_FILE_BIN% -binary ^
-exclude 0x%AP_STB%28 0x%AP_STB%2C 0x%AP_STB%34 0x%AP_STB%38 ^
-fill 0x%CRCV2% 0x%AP_STB%28 0x%AP_STB%29 ^
-fill 0x%CRCV1% 0x%AP_STB%29 0x%AP_STB%2a ^
-fill 0x0C      0x%AP_STB%2a 0x%AP_STB%2b ^
-fill 0x1A      0x%AP_STB%2b 0x%AP_STB%2c ^
-fill 0x%AP_0%  0x%AP_STB%34 0x%AP_STB%35 ^
-fill 0x%AP_1%  0x%AP_STB%35 0x%AP_STB%36 ^
-fill 0x%AP_2%  0x%AP_STB%36 0x%AP_STB%37 ^
-fill 0x%AP_3%  0x%AP_STB%37 0x%AP_STB%38 ^
-o %IN_FULL_PATH%\%OUT_FILE_CRC_BIN% -binary

SET "AP_ST_A=0000000%AP_ST2%28"
SET "AP_ST_A=%AP_ST_A:~-8%"
SET "AP_ST_B=0000000%AP_ST2%34"
SET "AP_ST_B=%AP_ST_B:~-8%"
ECHO   0x%AP_ST_A%            = 0x1A0C%CRCV1%%CRCV2%
ECHO   0x%AP_ST_B%            = 0x%AP_SAVE%
ECHO   Output HEX file       = %IN_FULL_PATH%\%OUT_FILE_CRC_HEX%
ECHO   Output Binary file    = %IN_FULL_PATH%\%OUT_FILE_CRC_BIN%


IF %VAR_MODE% NEQ ht32ide GOTO SKIP_ELF_MODIFY
REM Modify ELF file, add CRC
REM ==================================================================================================
SET READELF=arm-none-eabi-readelf.exe

for /f "tokens=5,6" %%a in ('%READELF% -S %IN_FILE_AXFELF% ^| findstr /r "\.isr_vector"') do (
    set ADDR=%%a
    set OFFSET=%%b
)

REM echo [.isr_vector] File Offset: 0x%OFFSET%, Addr: 0x%ADDR%

set /a FILE_OFFSET=0x%OFFSET%
set /a PATCH1=%FILE_OFFSET%+0x28
set /a PATCH2=%FILE_OFFSET%+0x34

COPY %IN_FILE_AXFELF% %IN_FILE_AXFELF%.bak >nul

REM Watch out that PowerShell using the 'tmp' variable,  any use of the "set tmp=" may cause issues
powershell -nologo -command ^
    "$f1 = '%IN_FILE_AXFELF%';" ^
    "$b = [System.IO.File]::ReadAllBytes($f1);" ^
    "$b[%PATCH1%+0] = 0x%CRCV2%;" ^
    "$b[%PATCH1%+1] = 0x%CRCV1%;" ^
    "$b[%PATCH1%+2] = 0x0C;" ^
    "$b[%PATCH1%+3] = 0x1A;" ^
    "$b[%PATCH2%+0] = 0x%AP_0%;" ^
    "$b[%PATCH2%+1] = 0x%AP_1%;" ^
    "$b[%PATCH2%+2] = 0x%AP_2%;" ^
    "$b[%PATCH2%+3] = 0x%AP_3%;" ^
    "[System.IO.File]::WriteAllBytes($f1, $b)"

ECHO --------------------------------------------------------------------------------
ECHO Add CRC to %IN_FILE_AXFELF% OK. Backup file: %IN_FILE_AXFELF%.bak

:SKIP_ELF_MODIFY


REM Compare the CRC address by SREC CMP if CMP_RESULT=1
REM ==================================================================================================
IF %CMP_RESULT% EQU 0 GOTO SKIP_CMP

ECHO Compare HEX file to confirm....
%SREC_CMP% %IN_FULL_PATH%\%IN_FILE_HEX% -intel %IN_FULL_PATH%\%OUT_FILE_CRC_HEX% -intel -v
ECHO Expect   :      (0x%AP_ST2%28 - 0x%AP_ST2%2b, 0x%AP_ST2%34 - 0x%AP_ST2%37)
ECHO.
ECHO Compare BIN file to confirm.....
%SREC_CMP% %IN_FULL_PATH%\%IN_FILE_BIN% -binary %IN_FULL_PATH%\%OUT_FILE_CRC_BIN% -binary -v
ECHO Expect   :      (0x%AP_STB%28 - 0x%AP_STB%2b, 0x%AP_STB%34 - 0x%AP_STB%37)

:SKIP_CMP

setlocal disabledelayedexpansion
ECHO --------------------------------------------------------------------------------
ECHO   !!!  IMPORTANT:
ECHO   !!!    Check if the AP Start/End Address (%AP_STA% ~ 0x%AP_END%) is reasonable.
IF %SHOW_CRC_CHECK_MSG% EQU 1 ECHO   !!!    Search and set "#define IAP_CRC_CHECK_EN" as 1 to enable IAP CRC checking on boot (before start AP).

DEL %TMP_SIZE_FILE% 1>> nul 2>&1
DEL %TMP_ADDR1% 1>> nul 2>&1
DEL %TMP_ADDR2% 1>> nul 2>&1
DEL %TMP_CRC% 1>> nul 2>&1
DEL CRC.hex 1>> nul 2>&1

IF %HEX_ENCODE% EQU 0 GOTO SKIP_HEX_ENCODE

REM Setting
REM ==================================================================================================
SET HEX_ENCODE_TOOL=%TOOL_PATH%\HexEncode\hex_encode.exe
SET TABLE=Table.ini
SET INPUT_FILE=%OUT_FILE_CRC_HEX%
SET OUTPUT_FILE=%VAR_OUTPUT_NAME%_CRC.bin
SET AP_FILE_BIN=AP_%ICNAME%_Encrypt.bin
SET AP_FILE_BIN2=AP_Encrypt.bin

REM Create AP Image
REM ==================================================================================================
ECHO --------------------------------------------------------------------------------
ECHO Start Encode AP ...

COPY /Y "%TOOL_PATH%\%TABLE%" "." 1>> nul 2>&1
%HEX_ENCODE_TOOL% -i %AP_STA% "%IN_FULL_PATH%\%INPUT_FILE%"
IF ERRORLEVEL 1 (
ECHO --------------------------------------------------------------------------------
ECHO   !!!  ERROR:
ECHO   !!!    Both "hex_encode.exe" and "Table.ini" must exist!
ECHO --------------------------------------------------------------------------------
DEL /Q ".\%TABLE%" 1>> nul 2>&1
GOTO SKIP_HEX_ENCODE
)

ECHO --------------------------------------------------------------------------------
ECHO   Input Hex file        = %IN_FULL_PATH%\%INPUT_FILE%
ECHO   AP Start Address      = %AP_STA%
ECHO --------------------------------------------------------------------------------
ECHO   Output Encrypted file = %IN_FULL_PATH%\%OUTPUT_FILE%
ECHO   Copy to %IN_FULL_PATH%
ECHO                         = %IN_FULL_PATH%\%AP_FILE_BIN2%
ECHO                         = %IN_FULL_PATH%\%AP_FILE_BIN%
ECHO --------------------------------------------------------------------------------

COPY /Y "%IN_FULL_PATH%\%OUTPUT_FILE%" "%IN_FULL_PATH%\%AP_FILE_BIN%"  1>> nul 2>&1
COPY /Y "%IN_FULL_PATH%\%OUTPUT_FILE%" "%IN_FULL_PATH%\%AP_FILE_BIN2%"  1>> nul 2>&1

DEL /Q ".\%TABLE%" 1>> nul 2>&1

:SKIP_HEX_ENCODE

IF %AP_ENCRYPT% EQU 0 GOTO :eof

REM Check HTEncrypt32.exe is installed or not by confirm the PATH
REM ==================================================================================================
ECHO %PATH%>TPM_PATH_CHECK.txt
FIND /i "HT32 TinyProgrammer Maker III" TPM_PATH_CHECK.txt 1>> nul 2>&1
IF ERRORLEVEL 1 (
ECHO --------------------------------------------------------------------------------
ECHO   !!!  ERROR:
ECHO   !!!    "HTEncrypt32.exe" is not exist! Please install latest HT32 Tiny Programmer Maker.
ECHO          https://mcu.holtek.com.tw/ht32/tools/TPMakerIII
ECHO --------------------------------------------------------------------------------
DEL /Q .\TPM_PATH_CHECK.txt
exit /b 3
)
DEL /Q .\TPM_PATH_CHECK.txt


REM Settings
REM ==================================================================================================
SET HOST_PATH=%TOOL_PATH%
SET MAKER_PATH=NULL
SET ENCRYPT_KEY_PATH=%TOOL_PATH%

IF %VAR_MODE% EQU keil (
SET IN_FULL_PATH_BIN=%IN_FULL_PATH%\IAP_AP.axf.bin
)

IF %VAR_MODE% EQU ht32ide (
SET IN_FULL_PATH_BIN=%IN_FULL_PATH%
)

SET IN_FILE_BIN=AP_CRC.bin

SET P_FILE_BIN=AP_%ICNAME%_Plaintext.bin
SET E_FILE_BIN=AP_%ICNAME%_Encrypt.bin
SET D_FILE_BIN=AP_%ICNAME%_Encrypt_digest.bin

SET P_FILE_BIN2=AP_Plaintext.bin
SET E_FILE_BIN2=AP_Encrypt.bin
SET D_FILE_BIN2=AP_Encrypt_digest.bin


REM Echo related information
REM ==================================================================================================
ECHO --------------------------------------------------------------------------------
ECHO   Input Binary file     = %IN_FULL_PATH_BIN%\%IN_FILE_BIN%
ECHO --------------------------------------------------------------------------------
ECHO   Output Plaintext file = %IN_FULL_PATH_BIN%\%P_FILE_BIN2%
ECHO   Output Encrypted file = %IN_FULL_PATH_BIN%\%E_FILE_BIN2%
ECHO   Output Digest file    = %IN_FULL_PATH_BIN%\%D_FILE_BIN2%
IF %MAKER_PATH% EQU NULL GOTO SKIP_COPY_TO_MAKER
ECHO   Copy to %MAKER_PATH%
ECHO                         = %MAKER_PATH%\%P_FILE_BIN2%
:SKIP_COPY_TO_MAKER
ECHO   Copy to %HOST_PATH%
ECHO                         = %HOST_PATH%\%P_FILE_BIN2%
ECHO                         = %HOST_PATH%\%E_FILE_BIN2%
ECHO                         = %HOST_PATH%\%D_FILE_BIN2%
ECHO                         = %HOST_PATH%\%P_FILE_BIN%
ECHO                         = %HOST_PATH%\%E_FILE_BIN%
ECHO                         = %HOST_PATH%\%D_FILE_BIN%


REM Copy and Encrypt files
REM ==================================================================================================
COPY /Y %IN_FULL_PATH_BIN%\%IN_FILE_BIN% %IN_FULL_PATH_BIN%\%P_FILE_BIN% 1>> nul 2>&1
HTEncrypt32.exe /s %IN_FULL_PATH_BIN%\%P_FILE_BIN% %ENCRYPT_KEY_PATH%\Encrypt_Key.bin %IN_FULL_PATH_BIN%\%E_FILE_BIN% > digest.txt

FOR /F %%i in (.\digest.txt) do ECHO   Digest                = %%i
ECHO --------------------------------------------------------------------------------

COPY /Y "%IN_FULL_PATH_BIN%\%P_FILE_BIN%" "%MAKER_PATH%\%P_FILE_BIN2%" 1>> nul 2>&1

COPY /Y "%IN_FULL_PATH_BIN%\%P_FILE_BIN%" "%IN_FULL_PATH_BIN%\%P_FILE_BIN2%" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%E_FILE_BIN%" "%IN_FULL_PATH_BIN%\%E_FILE_BIN2%" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%D_FILE_BIN%" "%IN_FULL_PATH_BIN%\%D_FILE_BIN2%" 1>> nul 2>&1

COPY /Y "%IN_FULL_PATH_BIN%\%P_FILE_BIN%" "%HOST_PATH%\" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%E_FILE_BIN%" "%HOST_PATH%\" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%D_FILE_BIN%" "%HOST_PATH%\" 1>> nul 2>&1

COPY /Y "%IN_FULL_PATH_BIN%\%P_FILE_BIN%" "%HOST_PATH%\%P_FILE_BIN2%" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%E_FILE_BIN%" "%HOST_PATH%\%E_FILE_BIN2%" 1>> nul 2>&1
COPY /Y "%IN_FULL_PATH_BIN%\%D_FILE_BIN%" "%HOST_PATH%\%D_FILE_BIN2%" 1>> nul 2>&1

DEL /Q .\digest.txt 1>> nul 2>&1
DEL /Q  %IN_FULL_PATH_BIN%\%IN_FILE_BIN% 1>> nul 2>&1

REM ***************************************************************
REM Get Address
REM ***************************************************************
:GETADR
SET /A cnt=%cnt%+1
IF %cnt% EQU %APSEQ% (
set AP_ADR_TMP=%1
)
goto :eof


REM ***************************************************************
REM Dec to Hex function
REM ***************************************************************
:DEC2HEX
  set /a remainder = %Input% %% 16
  set /a Input /= 16
  call :Base10to16 %remainder%
  set remainder=%ret%
  set ret2=%remainder%%ret2%
  if %Input% lss 16 goto DEC2HEXEND
goto DEC2HEX

:Base10to16
  set ret=
  if "%1" == "10" set ret=A
  if "%1" == "11" set ret=B
  if "%1" == "12" set ret=C
  if "%1" == "13" set ret=D
  if "%1" == "14" set ret=E
  if "%1" == "15" set ret=F
  if %1 lss 10 set ret=%1
goto :eof

:DEC2HEXEND
  call :Base10to16 %Input%
  set Input=%ret%
  if "%Input%" == "0" set Input=
  set retvalue=%Input%%ret2%
  set ret=
  set Input=
  set remainder=
  set ret2=
goto :eof
