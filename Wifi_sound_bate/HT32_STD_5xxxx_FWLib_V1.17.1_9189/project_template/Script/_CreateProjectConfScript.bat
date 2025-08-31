REM @ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _CreateProjectConfScript.bat
REM * @version $Rev:: 9070         $
REM * @date    $Date:: 2025-06-16 #$
REM * @brief   Create Project Configure Script.
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

TITLE HT32 Create Project Configuration

SET DISABLE_CONFIG_MENU=N
SET CREATE_CONF_FILE=..\..\..\_CreateProjectConfig.bat
SET IC_NAME_FILE=..\..\..\project_template\Script\_ht32_ic_name.ini

REM IF %DISABLE_CONFIG_MENU% == Y SET IDEALL=*
IF %DISABLE_CONFIG_MENU% == Y GOTO CONFIG_MENU_FINISH

SET IDE1=-
SET IDE2=-
SET IDE3=-
SET IDE4=-
SET IDE5=-
SET IDE6=-
SET IDE7=-
SET IDE8=-
REM SET IDEALL=-

IF EXIST %CREATE_CONF_FILE% GOTO CONFIG_MENU_FINISH
:CONF_MENU
CLS
ECHO ===========================================
ECHO =   HT32 Firmware Library Configuration   =
ECHO ===========================================
ECHO This is the first time you use create project script. Now start the confiuration....
ECHO.The following operations will be saved to "%CREATE_CONF_FILE%".
ECHO You can reset the configuration anytime by deleting the "%CREATE_CONF_FILE%".
ECHO.
ECHO Please choose the Compiler/IDE you are using for create project script (N for next step):
ECHO  # %IDE1% [1] Keil MDK-ARM v5
ECHO  # %IDE2% [2] Keil MDK-ARM v4
ECHO  # %IDE3% [3] IAR EWARM v8
ECHO  # %IDE4% [4] IAR EWARM v6/v7
ECHO  # %IDE5% [5] SEGGER Embedded Studio
ECHO  # %IDE6% [6] GNU (with Keil and GNU make)
ECHO  # %IDE7% [7] SourceryG++Lite (with Keil)
ECHO  # %IDE8% [8] HT32-IDE
ECHO  #   [A] All Compiler/IDE
ECHO  #   [N] OK, go next step
ECHO ?
choice /C 12345678AN /N

IF %errorlevel% == 1 (
  IF %IDE1% == - (
    SET IDE1=*
  ) ELSE (
    SET IDE1=-
  )
)
IF %errorlevel% == 2 (
  IF %IDE2% == - (
    SET IDE2=*
  ) ELSE (
    SET IDE2=-
  )
)
IF %errorlevel% == 3 (
  IF %IDE3% == - (
    SET IDE3=*
  ) ELSE (
    SET IDE3=-
  )
)
IF %errorlevel% == 4 (
  IF %IDE4% == - (
    SET IDE4=*
  ) ELSE (
    SET IDE4=-
  )
)
IF %errorlevel% == 5 (
  IF %IDE5% == - (
    SET IDE5=*
  ) ELSE (
    SET IDE5=-
  )
)
IF %errorlevel% == 6 (
  IF %IDE6% == - (
    SET IDE6=*
  ) ELSE (
    SET IDE6=-
  )
)
IF %errorlevel% == 7 (
  IF %IDE7% == - (
    SET IDE7=*
  ) ELSE (
    SET IDE7=-
  )
)
IF %errorlevel% == 8 (
  IF %IDE8% == - (
    SET IDE8=*
  ) ELSE (
    SET IDE8=-
  )
)
IF %errorlevel% == 9 (
  REM SET IDEALL=*
  SET IDE1=*
  SET IDE2=*
  SET IDE3=*
  SET IDE4=*
  SET IDE5=*
  SET IDE6=*
  SET IDE7=*
  SET IDE8=*
  GOTO CONFIG_MENU_NEXT
)

IF %errorlevel% == 10 (
  GOTO CONFIG_MENU_NEXT
)

GOTO CONF_MENU

)

:CONFIG_MENU_NEXT
SETLOCAL ENABLEDELAYEDEXPANSION
SET DEV_NUM=0
CLS
:CONFIG_MENU_AGAIN
ECHO ===========================================
ECHO =   HT32 Firmware Library Configuration   =
ECHO ===========================================
ECHO This is the first time you use create project script. Now start the confiuration....
ECHO.The following operations will be saved to "%CREATE_CONF_FILE%".
ECHO You can reset the confiuration anytime by deleting the "%CREATE_CONF_FILE%".
ECHO.
CALL :SL "Supported Device List:"
FOR /F "tokens=1,2,3 delims=," %%i IN (%IC_NAME_FILE%) DO (
  SET REM_LINE=%%i
  SET REM_LINE2=!REM_LINE:~0,3!

  IF NOT "!REM_LINE2!" == "REM" (
    IF "%%i" == "\n" (
      ECHO.
      ECHO.
      ECHO %%j
      CALL :SL " -     "
      SET DEV_NUM=0
    ) ELSE (
      IF NOT "!REM_LINE_RECORD!" == "!REM_LINE!" (
        CALL :SL "%%i, "
        set /a DEV_NUM+=1
        IF !DEV_NUM! == 10 (
          SET DEV_NUM=0
          ECHO.
          CALL :SL " -     "
        )
      )
    )
  )
  REM Record the current REM_LINE value and compares it with the next REM_LINE value to avoid displaying the same IC series on the window.
  SET REM_LINE_RECORD=!REM_LINE!
)
ECHO.
ECHO.
SET /p IC_NAME=Please input the IC name (Example: 52352), "*" for all models:

SET IC_NAME_OK=0
FOR /F "tokens=1,2,3 delims=, " %%i IN (%IC_NAME_FILE%) DO (
  IF NOT "%%i" == "REM" (
    IF "%%i" == "%IC_NAME%" (
      SET IC_NAME_OK=1
    )
  )
)

REM Check the input IC name is correct or not (Does the input in the list?)
IF "%IC_NAME%" == "*" SET IC_NAME_OK=1

IF %IC_NAME_OK% == 0 (
  CLS
  ECHO.
  ECHO --- ERROR ---
  ECHO The IC name is not correct. Please input again.
  ECHO.
  GOTO CONFIG_MENU_AGAIN
)


ECHO REM ==== HT32 Create Project Config File ====> %CREATE_CONF_FILE%
ECHO REM   1. Change the value as "Y" or "N" to enable/disable the project file copy/create of each toolchain.>> %CREATE_CONF_FILE%
ECHO REM   2. Delete this file (_CreateProjectConfig.bat) to reset the setting.>> %CREATE_CONF_FILE%
ECHO.>> %CREATE_CONF_FILE%
ECHO.>> %CREATE_CONF_FILE%
REM IF %IDEALL% == * ECHO SET IDE_ALL=Y>> %CREATE_CONF_FILE%
REM IF %IDEALL% == - ECHO SET IDE_ALL=N>> %CREATE_CONF_FILE%
IF %IDE1% == * ECHO SET IDE_KEILv5=Y>> %CREATE_CONF_FILE%
IF %IDE1% == - ECHO SET IDE_KEILv5=N>> %CREATE_CONF_FILE%
IF %IDE2% == * ECHO SET IDE_KEIL=Y>> %CREATE_CONF_FILE%
IF %IDE2% == - ECHO SET IDE_KEIL=N>> %CREATE_CONF_FILE%
IF %IDE3% == * ECHO SET IDE_IARv8=Y>> %CREATE_CONF_FILE%
IF %IDE3% == - ECHO SET IDE_IARv8=N>> %CREATE_CONF_FILE%
IF %IDE4% == * ECHO SET IDE_IAR=Y>> %CREATE_CONF_FILE%
IF %IDE4% == - ECHO SET IDE_IAR=N>> %CREATE_CONF_FILE%
IF %IDE5% == * ECHO SET IDE_SES=Y>> %CREATE_CONF_FILE%
IF %IDE5% == - ECHO SET IDE_SES=N>> %CREATE_CONF_FILE%
IF %IDE6% == * ECHO SET IDE_GNU=Y>> %CREATE_CONF_FILE%
IF %IDE6% == - ECHO SET IDE_GNU=N>> %CREATE_CONF_FILE%
IF %IDE7% == * ECHO SET IDE_SGPP=Y>> %CREATE_CONF_FILE%
IF %IDE7% == - ECHO SET IDE_SGPP=N>> %CREATE_CONF_FILE%
IF %IDE8% == * ECHO SET IDE_HT32=Y>> %CREATE_CONF_FILE%
IF %IDE8% == - ECHO SET IDE_HT32=N>> %CREATE_CONF_FILE%
ECHO.>> %CREATE_CONF_FILE%
ECHO.>> %CREATE_CONF_FILE%

ECHO SET IC_NAME=%IC_NAME%>> %CREATE_CONF_FILE%


:CONFIG_MENU_FINISH
ECHO.
GOTO :EOF

:SL
echo|set /p=%1
exit /b
