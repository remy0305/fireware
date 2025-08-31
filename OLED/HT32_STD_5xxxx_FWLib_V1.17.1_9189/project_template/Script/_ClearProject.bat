@ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _ClearProject.bat
REM * @version $Rev:: 9171         $
REM * @date    $Date:: 2025-06-23 #$
REM * @brief   Clear Project Script.
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

TITLE HT32 Clear Project


SET "CurrentDir=."
SET "CurrentFile=%~f0"
SET "SYSTEM_FILE=system_ht32??xxxx_??.c"
SET "OriginalFile=original_file.txt"
SET "USBDCONF_ORI=0"

REM Remove _ClearProject.bat
REM ===========================================================================
IF "%1"=="remove_self" (
  del %2 /s /Q /F >nul
  ECHO.
  ECHO ====================FINISH====================
  GOTO ClearEnd
)

REM Record USBDCONF_ORI flag for detection before deletion.
REM ===========================================================================
IF "%1"=="make_original_file" (
  ECHO. >>"%CurrentFile%"
  FOR /r "%CurrentDir%" %%f IN (ht32??xxxx_??_usbdconf.h) DO (
    ECHO SET "USBDCONF_ORI=1" >>"%CurrentFile%"
    GOTO WriteGOTOClearMain
  )
:WriteGOTOClearMain
  ECHO GOTO ClearMain >>"%CurrentFile%"
  EXIT
) ELSE (
  GOTO RecordFile
)

:ClearMain
REM Delete All IDEs and Project Files
REM ===========================================================================
ECHO The following folders and files will be deleted.
ECHO.
ECHO .\emStudiov4
ECHO .\EWARM
ECHO .\EWARMv8
ECHO .\GNU_ARM
ECHO .\HT32-IDE
ECHO .\MDK_ARM
ECHO .\MDK_ARMv5
ECHO .\MDK_ARMv537
ECHO .\SourceryG++Lite
ECHO _ClearProject.bat
ECHO _ClearTarget.bat
ECHO _CreateProjectScript.bat
REM Check the ht32fxxxxx_nn_usbdconf.h is original or not.
REM ===========================================================================
REM NOT Original
IF %USBDCONF_ORI%==0 (
  ECHO ht32??xxxx_nn_usbdconf.h
)
REM ===========================================================================
ECHO ht32??xxxx_conf.h
ECHO system_ht32??xxxx_nn.c

ECHO.

REM Confirm to delete.
REM ===========================================================================
ECHO Please confirm that folders and files has been backup.
SET /p iscon=Are you sure you want to continue?(yes)
IF %iscon%==yes ( 
  GOTO ClearStart
) ELSE (
  EXIT
)

:ClearStart
REM Delete System Files
FOR /r "%CurrentDir%" %%f IN (%SYSTEM_FILE%) DO (
  del "%%f" /s /Q /F >nul
)
REM Delete Library Configuration File
del .\ht32??xxxx_conf.h /s /Q /F >nul
REM Delete IDEs Folder
FOR /d %%d IN ("%CurrentDir%\*") DO (
  IF "%%~nxd"=="emStudiov4" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="EWARM" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="EWARMv8" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="GNU_ARM" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="HT32-IDE" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="MDK_ARM" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="MDK_ARMv5" (
    RD /s /q %%d
  ) ELSE IF "%%~nxd"=="MDK_ARMv537" (
    RD /s /q %%d
  )ELSE IF "%%~nxd"=="SourceryG++Lite" (
    RD /s /q %%d
  )
)
REM Delete USBDCONF File
IF %USBDCONF_ORI%==0 (
  FOR /r "%CurrentDir%" %%f IN (ht32??xxxx_??_usbdconf.h) DO (
    del "%%f" /s /Q /F >nul
  )
)
REM Delete Batch File
del .\_CreateProjectScript.bat /s /Q /F 1> nul 2>&1
del .\_ProjectSource.bat /s /Q /F 1> nul 2>&1
del .\_ProjectSource_ht32ide.bat /s /Q /F 1> nul 2>&1
del .\_ClearTarget.bat /s /Q /F 1> nul 2>&1
CALL "..\..\..\project_template\Script\_ClearProject.bat" remove_self "%CurrentFile%"
EXIT

:ClearEnd
PAUSE
EXIT

REM record FLAG
REM ===========================================================================
:RecordFile 