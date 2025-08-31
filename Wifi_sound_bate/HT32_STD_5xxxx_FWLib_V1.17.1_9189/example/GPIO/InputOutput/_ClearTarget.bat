@ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _ClearTarget.bat
REM * @version $Rev:: 9070         $
REM * @date    $Date:: 2025-06-16 #$
REM * @brief   Clear Target Script.
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

TITLE HT32 Clear Target

ECHO The following folders will be deleted.
ECHO.

ECHO .\emStudiov4\HT32
ECHO .\EWARM\HT32
ECHO .\EWARMv8\HT32
ECHO .\GNU_ARM\HT32
ECHO .\HT32-IDE\Project_*\HT32
ECHO .\MDK_ARM\HT32
ECHO .\MDK_ARMv5\HT32
ECHO .\MDK_ARMv537\HT32
ECHO .\SourceyG++Lite\HT32
ECHO.

ECHO Please confirm that the target file has been backup.
SET /p iscon=Are you sure you want to continue?(yes)
IF %iscon%==yes ( 
  GOTO ClearStart
) ELSE (
  EXIT
)

:ClearStart
REM Delete HT32 Folder
REM SET "CurrentDir=.%~1"
ECHO.
FOR /d %%d IN (".\*") DO (
  IF EXIST %%d\HT32 (
    ECHO %%d\HT32 had been delete.
    RD /s /q %%d\HT32
  )
)
FOR /d %%d IN (".\HT32-IDE\*") DO (
  IF EXIST %%d\Debug (
    ECHO %%d\Debug\* had been delete.
    DEL %%d\Debug\* /S /Q /F >nul
    FOR /D %%x IN ("%%d\Debug\*") DO RD /S /Q "%%x"
  )
)
ECHO.
ECHO ====================FINISH====================

:ClearEnd
PAUSE