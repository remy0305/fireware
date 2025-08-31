rem @ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _CreateProjectScript.bat
REM * @version $Rev:: 9171         $
REM * @date    $Date:: 2025-06-23 #$
REM * @brief   Create Project Script.
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

TITLE HT32 Create Project

SETLOCAL ENABLEDELAYEDEXPANSION
SET CREATE_CONF_FILE=..\..\..\_CreateProjectConfig.bat
SET IC_NAME_FILE=..\..\..\project_template\Script\_ht32_ic_name.ini

REM Copy The Clear Batch from Script Folder
REM  ===========================================================================
COPY /Y "..\..\..\project_template\Script\_ClearProject.bat"  "." 1> nul 2>&1
START /b CALL ".\_ClearProject.bat" make_original_file
timeout /t 1 >nul
COPY /Y "..\..\..\project_template\Script\_ClearTarget.bat"  "." 1> nul 2>&1

REM Try to Start Create Project Config
REM  ===========================================================================
IF NOT EXIST "%CREATE_CONF_FILE%" (
COPY /Y "..\..\..\project_template\Script\_CreateProjectConfScript.bat"  "." 1> nul 2>&1
IF EXIST "_CreateProjectConfScript.bat" CALL _CreateProjectConfScript.bat
DEL /Q _CreateProjectConfScript.bat 1> nul 2>&1
)


REM Show Create Project Settings
REM  ===========================================================================
IF EXIST %CREATE_CONF_FILE% (
ECHO.
ECHO Load configuration file, "%CREATE_CONF_FILE%" ....
ECHO You can reset the create project IDE/IC configuration anytime by deleting the configuration file.
CALL %CREATE_CONF_FILE%
)

SET IDE1=-
SET IDE2=-
SET IDE3=-
SET IDE4=-
SET IDE5=-
SET IDE6=-
SET IDE7=-
SET IDE8=-

IF (%IDE_KEILv5%) == (Y) SET IDE1=Y
IF (%IDE_KEIL%) == (Y) SET IDE2=Y
IF (%IDE_IARv8%) == (Y) SET IDE3=Y
IF (%IDE_IAR%) == (Y) SET IDE4=Y
IF (%IDE_SES%) == (Y) SET IDE5=Y
IF (%IDE_GNU%) == (Y) SET IDE6=Y
IF (%IDE_SGPP%) == (Y) SET IDE7=Y
SET CHECK_HT32IDE=%IDE_HT32%
IF "%CHECK_HT32IDE%"=="" GOTO SKIP_HT32_IDE1
IF (%IDE_HT32%) == (Y) SET IDE8=Y

:SKIP_HT32_IDE1
IF EXIST %CREATE_CONF_FILE% (
ECHO.
ECHO Create Project Settings:
ECHO   [%IDE1%] Keil MDK-ARM v5
ECHO   [%IDE2%] Keil MDK-ARM v4
ECHO   [%IDE3%] IAR EWARM v8
ECHO   [%IDE4%] IAR EWARM v6/v7
ECHO   [%IDE5%] SEGGER Embedded Studio
ECHO   [%IDE6%] GNU [with Keil and GNU make]
ECHO   [%IDE7%] SourceryG++Lite [with Keil]
ECHO   [%IDE8%] HT32-IDE
ECHO   Y: Enable, -: Disable
ECHO.
ECHO   IC Name: %IC_NAME% [* for all models, XXX* for series]
)


REM Start Copy Files
REM  ===========================================================================
ECHO.
ECHO Creating project. Please wait....
COPY /Y "..\..\..\utilities\gsar\gsar.e_x_e"  "..\..\..\" 1> nul 2>&1
COPY /Y "..\..\..\project_template\Script\gsar.e_x_e"  "..\..\..\" 1> nul 2>&1
IF NOT EXIST "..\..\..\gsar.e_x_e" (
ECHO.
ECHO ERROR: The "..\..\..\gsar.e_x_e" tool is not exist! Please check it and try again!
ECHO.
DEL /Q _CreateProjectScript.bat 1> nul 2>&1
GOTO CREATE_PROJECT_FAIL
)

SET "CoIDE_DIR=%cd%"
:1
SET "CoIDE_DIR=%CoIDE_DIR:*\=%"&set "b=%CoIDE_DIR:\=%"
IF "%b%" NEQ "%CoIDE_DIR%" GOTO 1
SET "CoIDE_DIR=CoIDE_%CoIDE_DIR%"

SET PRO_TYPE=%1

IF %PRO_TYPE% == AUTO (
SET PRO_TYPE=Template
IF EXIST "ht32_usbd_descriptor.c" SET PRO_TYPE=Template_USB
)

REM Prepare not override input
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt

REM No Create Project Config File, default copy all files
IF NOT EXIST %CREATE_CONF_FILE% (
SET IC_NAME=*
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\*"  "." < dummyn.txt 1> nul 2>&1
GOTO COPY_FINISH
) 

REM Copy files according to the Create Project Config File

REM For IC_NAME=*
SET SYSTEM_C_FILE=system_ht32*

REM Read system/startup settings
IF NOT (%IC_NAME%) == (*) (
SET NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE=0
FOR /F "tokens=1,2,3,4 delims=, " %%i IN (%IC_NAME_FILE%) DO (
  IF "%%i" == "%IC_NAME%" (
    SET /A NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE+=1
    SET SYSTEM_C_FILE!NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE!=%%j
    SET STARTUP_FILE_PREFIX!NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE!=%%k
    SET STARTUP_FILE_NUM!NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE!=%%l
  )
)
  REM Copy "system.c" for IC_NAME!=*
  FOR /L %%x IN (1, 1, !NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE!) DO (
  XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\!SYSTEM_C_FILE%%x!.c" "." >> dummyn.txt 1> nul 2>&1
  )
) ELSE (
  REM Copy "system.c" for IC_NAME=*
  XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\!SYSTEM_C_FILE!.c"  "." < dummyn.txt 1> nul 2>&1
)

REM COPY .h files
XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\*.h"  "." < dummyn.txt 1> nul 2>&1

REM For ".mk" files of GNU
SET IC_NAME2=%IC_NAME%

REM Prepare exclude file type for XCOPY *
ECHO .uvprojx>Exclude.txt
ECHO .uvproj>>Exclude.txt
ECHO .dep>>Exclude.txt
ECHO .mk>>Exclude.txt
ECHO .ewd>>Exclude.txt
ECHO .ewp>>Exclude.txt
ECHO .eww>>Exclude.txt
ECHO .emProject>>Exclude.txt
ECHO .bat>>Exclude.txt
ECHO .s>>Exclude.txt

REM IC_NAME != *, not all IC model, XCOPY %IC_NAME% only copy Project_xxxxx.* files
IF NOT %IC_NAME% == * SET IC_NAME=Project_%IC_NAME%

IF %IDE_KEILv5% == Y (
REM MDK_ARMv5 (Arm Compiler Version 5)
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\*"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\%IC_NAME%.*"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\!STARTUP_FILE_PREFIX%%x!!STARTUP_FILE_NUM%%x!.s"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\ht32_op.s"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1

REM MDK_ARMv537 (Arm Compiler Version 6)
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv537\*"  ".\MDK_ARMv537\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv537\%IC_NAME%.*"  ".\MDK_ARMv537\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv537\!STARTUP_FILE_PREFIX%%x!!STARTUP_FILE_NUM%%x!.s"  ".\MDK_ARMv537\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv537\ht32_op.s"  ".\MDK_ARMv537\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_KEIL% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\*"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\%IC_NAME%.*"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\!STARTUP_FILE_PREFIX%%x!!STARTUP_FILE_NUM%%x!.s"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\ht32_op.s"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_IARv8% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\*"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\%IC_NAME%.*"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\!STARTUP_FILE_PREFIX%%x!iar_!STARTUP_FILE_NUM%%x!.s"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
)
)

IF %IDE_IAR% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\*"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\%IC_NAME%.*"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\!STARTUP_FILE_PREFIX%%x!iar_!STARTUP_FILE_NUM%%x!.s"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
)
)

IF %IDE_SES% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\*"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\%IC_NAME%.*"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\!STARTUP_FILE_PREFIX%%x!es_!STARTUP_FILE_NUM%%x!.s"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\_MassErase.bat"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\Use Project_xxxxx.bat to open project" ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_GNU% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\*"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%IC_NAME%.*"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%IC_NAME2%.mk"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\!STARTUP_FILE_PREFIX%%x!gcc_!STARTUP_FILE_NUM%%x!.s"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\afterbuild.bat"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_SGPP% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\*"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\%IC_NAME%.*"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\!STARTUP_FILE_PREFIX%%x!cs3_!STARTUP_FILE_NUM%%x!.s"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
)
)
SET CHECK_HT32IDE=%IDE_HT32%
IF "%CHECK_HT32IDE%"=="" GOTO SKIP_HT32_IDE2
IF %IDE_HT32% == Y (
FOR /d %%d IN ("..\..\..\project_template\IP\%PRO_TYPE%\HT32-IDE\%IC_NAME%") DO (
  XCOPY /E /I /Y /Q "%%d" ".\HT32-IDE\%%~nxd\" < dummyn.txt 1> nul 2>&1
)
FOR /L %%x IN (1, 1, %NUM_OF_SYSTEM_STARTUP_SERIES_COMBINE%) DO (
  XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\HT32-IDE\GNU_ARM\!STARTUP_FILE_PREFIX%%x!gcc_!STARTUP_FILE_NUM%%x!.s"  ".\HT32-IDE\GNU_ARM\" < dummyn.txt 1> nul 2>&1
)
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\HT32-IDE\GNU_ARM\ht32_op.c"  ".\HT32-IDE\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\HT32-IDE\GNU_ARM\linker.ld"  ".\HT32-IDE\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\HT32-IDE\afterbuild.bat"  ".\HT32-IDE\" < dummyn.txt 1> nul 2>&1
)
:SKIP_HT32_IDE2

SETLOCAL DISABLEDELAYEDEXPANSION

:COPY_FINISH
DEL Exclude.txt /Q 1> nul 2>&1
DEL dummyn.txt /Q 1> nul 2>&1

RENAME "CoIDE_Template\CoIDE_Template.cob" "%CoIDE_DIR%.cob" 1> nul 2>&1
RENAME CoIDE_Template %CoIDE_DIR% 1> nul 2>&1

COPY "..\..\..\gsar.e_x_e" "." 1> nul 2>&1
RENAME gsar.e_x_e gsar.exe 1> nul 2>&1


SETLOCAL ENABLEDELAYEDEXPANSION

FOR %%I IN ("%CD%") DO SET "full=%%~fI"
SET "tmpname=!full:\= !"
SET count=0
FOR %%x IN (!tmpname!) DO (
    SET /a count+=1
    SET "dir!count!=%%x"
)

SET /a idx1=count-1
SET /a idx2=count
SET "HT32IDE_PNAME=!dir%idx1%!_!dir%idx2%!"

FOR /d %%d IN (".\HT32-IDE\*") DO (
gsar.exe -s"project_template_" -r"!HT32IDE_PNAME!_" HT32-IDE\%%~nxd\*.project -o 1> nul 2>&1
)

COPY /Y "..\..\..\project_template\Script\_ProjectConfigScript.bat"  "." 1> nul 2>&1

REM Process "_ProjectConfig.bat"
REM  ===========================================================================
IF EXIST _ProjectConfig.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM4.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM0pl.bat GOTO PROJECT_CONFIG
GOTO CREATE_PROJECT_END

:PROJECT_CONFIG
IF EXIST MDK_ARM\HT32F5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0P
IF EXIST MDK_ARMv5\HT32F5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0P
IF EXIST MDK_ARMv537\HT32F5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0P
IF EXIST MDK_ARM\HT32F1xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CFG_M3
IF EXIST MDK_ARMv5\HT32F1xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CFG_M3
IF EXIST MDK_ARMv537\HT32F1xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CFG_M3
IF EXIST MDK_ARM\HT32F4xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM4.bat GOTO PROJECT_CFG_M4
IF EXIST MDK_ARMv5\HT32F4xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM4.bat GOTO PROJECT_CFG_M4
IF EXIST MDK_ARMv537\HT32F4xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM4.bat GOTO PROJECT_CFG_M4
IF EXIST MDK_ARM\HT32L5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0PL
IF EXIST MDK_ARMv5\HT32L5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0PL
IF EXIST MDK_ARMv537\HT32L5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0PL
GOTO PROJECT_CFG_ALL

:PROJECT_CFG_M0P
CALL _ProjectConfigM0p.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_M3
CALL _ProjectConfigM3.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_M4
CALL _ProjectConfigM4.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_M0PL
CALL _ProjectConfigM0pl.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_ALL
CALL _ProjectConfig.bat 1> nul 2>&1

:PROJECT_CFG_END

IF EXIST "_ProjectConfigScript.bat" CALL _ProjectConfigScript.bat
DEL /Q _ProjectConfigScript.bat 1> nul 2>&1

REM Change RO, RW Based address
REM  ===========================================================================
IF %HT_CHANGE_RO_RW%==1 GOTO BaseSET
GOTO BaseSET_End
:BaseSET
gsar.exe -s"<TextAddressRange>0x00000000</TextAddressRange>" -r"<TextAddressRange>%HT_RO_ADDR%</TextAddressRange>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<TextAddressRange>0x00000000</TextAddressRange>" -r"<TextAddressRange>%HT_RO_ADDR%</TextAddressRange>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<TextAddressRange>0x00000000</TextAddressRange>" -r"<TextAddressRange>%HT_RO_ADDR%</TextAddressRange>" MDK_ARMv537\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<DataAddressRange>0x20000000</DataAddressRange>" -r"<DataAddressRange>%HT_RW_ADDR%</DataAddressRange>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<DataAddressRange>0x20000000</DataAddressRange>" -r"<DataAddressRange>%HT_RW_ADDR%</DataAddressRange>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<DataAddressRange>0x20000000</DataAddressRange>" -r"<DataAddressRange>%HT_RW_ADDR%</DataAddressRange>" MDK_ARMv537\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_region_ROM_start__ = 0x00000000;" -r"define symbol __ICFEDIT_region_ROM_start__ = %HT_RO_ADDR%;" EWARM\*.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_region_ROM_start__ = 0x00000000;" -r"define symbol __ICFEDIT_region_ROM_start__ = %HT_RO_ADDR%;" EWARMv8\*.icf -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_region_RAM_start__ = 0x20000000;" -r"define symbol __ICFEDIT_region_RAM_start__ = %HT_RW_ADDR%;" EWARM\*.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_region_RAM_start__ = 0x20000000;" -r"define symbol __ICFEDIT_region_RAM_start__ = %HT_RW_ADDR%;" EWARMv8\*.icf -o 1> nul 2>&1

gsar.exe -s"ORIGIN = 0x00000000" -r"ORIGIN = %HT_RO_ADDR%" GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x00000000" -r"ORIGIN = %HT_RO_ADDR%" HT32-IDE\GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x00000000" -r"ORIGIN = %HT_RO_ADDR%" SourceryG++Lite\*.ld -o 1> nul 2>&1

gsar.exe -s"ORIGIN = 0x20000000" -r"ORIGIN = %HT_RW_ADDR%" GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x20000000" -r"ORIGIN = %HT_RW_ADDR%" HT32-IDE\GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x20000000" -r"ORIGIN = %HT_RW_ADDR%" SourceryG++Lite\*.ld -o 1> nul 2>&1

gsar.exe -s"RAM RWX 0x20000000" -r"RAM RWX %HT_RW_ADDR%" emStudiov4\Project_*.emProject -o 1> nul 2>&1

SETLOCAL ENABLEDELAYEDEXPANSION
SET HT_RO_ORG_HEX_LENGTH=0x00000000
SET HT_RO_ORG_DEC_LENGTH=0
SET HT_RO_NEW_LENGTH=0

REM Modify RO Data of emStudiov4
REM Search all .emProject files for lines containing "arm_simulator_memory_simulation_parameter"
FOR /F "delims=" %%a IN ('FINDSTR /s /n /c:"arm_simulator_memory_simulation_parameter" *.emProject') DO (
    SET "line=%%a"

    REM Extract full filename and content from the result line
    FOR /F "tokens=1* delims=:" %%i IN ("!line!") DO (
        SET "fullpath=%%i"
        SET "content=%%j"

        REM Extract filename only (strip path)
        FOR %%F IN ("!fullpath!") DO SET "filename=%%~nxF"

        REM Get the second field (hex value) from the line
        FOR /F "tokens=2 delims=," %%h IN ("!content!") DO (
            SET "HT_RO_ORG_HEX_LENGTH=%%h"
            SET /A HT_RO_ORG_DEC_LENGTH=0x%%h
            SET /A HT_RO_ADDR_DEC=%HT_RO_ADDR%
            SET /A HT_RO_NEW_LENGTH=HT_RO_ORG_DEC_LENGTH - HT_RO_ADDR_DEC

            REM Use PowerShell to format the result as lowercase hex with 0x prefix and 4 digits
            FOR /F %%z IN ('powershell -nologo -command "[string]::Format(\"0x{0:x8}\", !HT_RO_NEW_LENGTH!)"') DO (
                SET HT_RO_NEW_HEX_LENGTH=%%z
            )

            REM Output the result
            REM ECHO Filename: !filename!
            REM ECHO Original Hex Length: !HT_RO_ORG_HEX_LENGTH!
            REM ECHO Original Dec Length: !HT_RO_ORG_DEC_LENGTH!
            REM ECHO New Dec Length: !HT_RO_NEW_LENGTH!
            REM ECHO New Hex Length: !HT_RO_NEW_HEX_LENGTH!
            REM ECHO ------------------------
            gsar.exe -s"FLASH RX 0x00000000 0x!HT_RO_ORG_HEX_LENGTH!" -r"FLASH RX %HT_RO_ADDR% !HT_RO_NEW_HEX_LENGTH!" emStudiov4\!filename! -o 1> nul 2>&1
        )
    )
)

:BaseSET_End


REM Change Stack, Heap size
REM  ===========================================================================
IF %HT_CHANGE_STACK_HEAP%==1 GOTO MemSET
GOTO MemSET_End
:MemSET
gsar.exe -s"Stack_Size          EQU     512" -r"Stack_Size          EQU     %HT_STACK_SIZE%" MDK_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Stack_Size          EQU     512" -r"Stack_Size          EQU     %HT_STACK_SIZE%" MDK_ARMv5\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Stack_Size          EQU     512" -r"Stack_Size          EQU     %HT_STACK_SIZE%" MDK_ARMv537\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Heap_Size           EQU     0"   -r"Heap_Size           EQU     %HT_HEAP_SIZE%"  MDK_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Heap_Size           EQU     0"   -r"Heap_Size           EQU     %HT_HEAP_SIZE%"  MDK_ARMv5\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Heap_Size           EQU     0"   -r"Heap_Size           EQU     %HT_HEAP_SIZE%"  MDK_ARMv537\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_size_cstack__ = 0x200;" -r"define symbol __ICFEDIT_size_cstack__ = %HT_STACK_SIZE%;" EWARM\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_cstack__ = 0x200;" -r"define symbol __ICFEDIT_size_cstack__ = %HT_STACK_SIZE%;" EWARMv8\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_heap__   = 0x0;" -r"define symbol __ICFEDIT_size_heap__   = %HT_HEAP_SIZE%;" EWARM\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_heap__   = 0x0;" -r"define symbol __ICFEDIT_size_heap__   = %HT_HEAP_SIZE%;" EWARMv8\linker.icf -o 1> nul 2>&1

gsar.exe -s".equ    Stack_Size, 512" -r".equ    Stack_Size, %HT_STACK_SIZE%"    GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s".equ    Heap_Size, 0"    -r".equ    Heap_Size, %HT_HEAP_SIZE%"      GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s".equ    Stack_Size, 512" -r".equ    Stack_Size, %HT_STACK_SIZE%"    HT32-IDE\GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s".equ    Heap_Size, 0"    -r".equ    Heap_Size, %HT_HEAP_SIZE%"      HT32-IDE\GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s".equ    Stack_Size, 512" -r".equ    Stack_Size, %HT_STACK_SIZE%"    SourceryG++Lite\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s".equ    Heap_Size, 0"    -r".equ    Heap_Size, %HT_HEAP_SIZE%"      SourceryG++Lite\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s"arm_linker_stack_size=:x22512:x22" -r"arm_linker_stack_size=:x22%HT_STACK_SIZE%:x22"    emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s"arm_linker_heap_size=:x220:x22" -r"arm_linker_heap_size=:x22%HT_HEAP_SIZE%:x22"    emStudiov4\Project_*.emProject -o 1> nul 2>&1
:MemSET_End


REM Change include path
REM  ===========================================================================
SETLOCAL ENABLEDELAYEDEXPANSION
IF %HT_CHANGE_INCLUDE%==0 GOTO IncludeSET_End

SET "LASTCHAR=!HT_EXTRA_INCLUDE:~-1!"

IF "!LASTCHAR!"==";" (
    SET "HT_EXTRA_INCLUDE=!HT_EXTRA_INCLUDE:~0,-1!"
)
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" MDK_ARMv537\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" GNU_ARM\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" SourceryG++Lite\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a_IAR_INCLUDE_REPLACE_" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a_IAR_INCLUDE_REPLACE_" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"INCLUDE_PATH += -I./../../../../utilities" -r"INCLUDE_PATH += -I./../../../../utilities:x0d:x0a_IAR_INCLUDE_REPLACE_" GNU_ARM\*.mk -o 1> nul 2>&1

FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"<listOptionValue builtIn=:x22false:x22 value=:x22../../../../../../utilities:x22/>" -r"<listOptionValue builtIn=:x22false:x22 value=:x22../../../../../../utilities:x22/>:x0a_IAR_INCLUDE_REPLACE_" %%D\*.cproject  -o 1> nul 2>&1
)

SET "HT_EXTRA_INCLUDE2=!HT_EXTRA_INCLUDE:;= !"
for %%I in (!HT_EXTRA_INCLUDE2!) do (
gsar.exe -s"_IAR_INCLUDE_REPLACE_" -r"          <state>$PROJ_DIR$\%%I</state>:x0d:x0a_IAR_INCLUDE_REPLACE_" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_INCLUDE_REPLACE_" -r"                    <state>$PROJ_DIR$\%%I</state>:x0d:x0a_IAR_INCLUDE_REPLACE_" EWARMv8\*.ewp -o 1> nul 2>&1
SET "UNIX_PATH=%%I"
SET "UNIX_PATH=!UNIX_PATH:\=/!"
gsar.exe -s"_IAR_INCLUDE_REPLACE_" -r"INCLUDE_PATH += -I./!UNIX_PATH!:x0d:x0a_IAR_INCLUDE_REPLACE_" GNU_ARM\*.mk -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"_IAR_INCLUDE_REPLACE_" -r"									<listOptionValue builtIn=:x22false:x22 value=:x22../../!UNIX_PATH!:x22/>:x0a_IAR_INCLUDE_REPLACE_" %%D\*.cproject  -o 1> nul 2>&1
)
)
gsar.exe -s"_IAR_INCLUDE_REPLACE_:x0d:x0a" -r"" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_INCLUDE_REPLACE_:x0d:x0a" -r"" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_INCLUDE_REPLACE_:x0d:x0a" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"_IAR_INCLUDE_REPLACE_:x0a" -r"" %%D\*.cproject  -o 1> nul 2>&1
)

SETLOCAL ENABLEDELAYEDEXPANSION
SET TMPVAL=%HT_EXTRA_INCLUDE%
SET TMPVAL=!TMPVAL:\=\\!
gsar.exe -s"..\\..\\..\\..\\utilities:x22" -r"..\\..\\..\\..\\utilities;%TMPVAL%:x22" emStudiov4\Project_*.emProject -o 1> nul 2>&1
:IncludeSET_End


REM Change C define
REM  ===========================================================================
IF %HT_CHANGE_CDEFINE%==0 GOTO CdefineSET_End

SET "CHECK_END=!HT_EXTRA_CDEFINE:~-2!"
SET "CHECK_END2=!HT_EXTRA_CDEFINE:~-1!"

IF NOT "!CHECK_END!"==", " (
    IF "!CHECK_END2!"=="," (
      SET "HT_EXTRA_CDEFINE=!HT_EXTRA_CDEFINE! "
    ) ELSE (
      SET "HT_EXTRA_CDEFINE=!HT_EXTRA_CDEFINE!, "
    )
)
gsar.exe -s"<Define>USE_HT32_DRIVER, " -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER, " -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER, " -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" MDK_ARMv537\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER, " -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" GNU_ARM\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER, " -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" SourceryG++Lite\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<state>USE_HT32_DRIVER</state>" -r"<state>USE_HT32_DRIVER</state>:x0d:x0a_IAR_CDEFINE_REPLACE_" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>USE_HT32_DRIVER</state>" -r"<state>USE_HT32_DRIVER</state>:x0d:x0a_IAR_CDEFINE_REPLACE_" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"C_OPTION += -DUSE_HT32_DRIVER" -r"C_OPTION += -DUSE_HT32_DRIVER:x0d:x0a_IAR_CDEFINE_REPLACE_" GNU_ARM\*.mk -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"<listOptionValue builtIn=:x22false:x22 value=:x22USE_HT32_DRIVER:x22/>" -r"<listOptionValue builtIn=:x22false:x22 value=:x22USE_HT32_DRIVER:x22/>:x0a_IAR_CDEFINE_REPLACE_" %%D\*.cproject -o 1> nul 2>&1
)
SET "HT_EXTRA_CDEFINE2=!HT_EXTRA_CDEFINE: =!"
SET "HT_EXTRA_CDEFINE2=!HT_EXTRA_CDEFINE2:,= !"
for %%I in (!HT_EXTRA_CDEFINE2!) do (
gsar.exe -s"_IAR_CDEFINE_REPLACE_" -r"          <state>%%I</state>:x0d:x0a_IAR_CDEFINE_REPLACE_" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_CDEFINE_REPLACE_" -r"                    <state>%%I</state>:x0d:x0a_IAR_CDEFINE_REPLACE_" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_CDEFINE_REPLACE_" -r"C_OPTION += -D%%I:x0d:x0a_IAR_CDEFINE_REPLACE_" GNU_ARM\*.mk -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"_IAR_CDEFINE_REPLACE_" -r"									<listOptionValue builtIn=:x22false:x22 value=:x22%%I:x22/>:x0a_IAR_CDEFINE_REPLACE_" %%D\*.cproject -o 1> nul 2>&1
)
)

gsar.exe -s"_IAR_CDEFINE_REPLACE_:x0d:x0a" -r"" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_CDEFINE_REPLACE_:x0d:x0a" -r"" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"_IAR_CDEFINE_REPLACE_:x0d:x0a" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"_IAR_CDEFINE_REPLACE_:x0a" -r"" %%D\*.cproject -o 1> nul 2>&1
)

SETLOCAL ENABLEDELAYEDEXPANSION
SET TMPVAL=%HT_EXTRA_CDEFINE%
SET TMPVAL=!TMPVAL:,=;!
SET TMPVAL=!TMPVAL: =!
gsar.exe -s"USE_HT32_DRIVER;" -r"USE_HT32_DRIVER;%TMPVAL%" emStudiov4\Project_*.emProject -o 1> nul 2>&1
:CdefineSET_End


REM Change Linker Script file
REM  ===========================================================================
SET VAR2=%HT_CHANGE_LINKER_SCRIPT%
IF "%VAR2%"=="" GOTO LinkerScriptSET_End
IF %HT_CHANGE_LINKER_SCRIPT%==0 GOTO LinkerScriptSET_End

gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>%HT_LINKER_NAME_KEIL%</ScatterFile>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>%HT_LINKER_NAME_KEIL%</ScatterFile>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<ScatterFile></ScatterFile>" -r"<ScatterFile>%HT_LINKER_NAME_KEIL%</ScatterFile>" MDK_ARMv537\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<ScatterFile>.\linker.ld</ScatterFile>" -r"<ScatterFile>%HT_LINKER_NAME_SourceryG%</ScatterFile>" SourceryG++Lite\*.uvprojx -o 1> nul 2>&1

SET "HT_LINKER_NAME_SES2=%HT_LINKER_NAME_SES%"
SET "HT_LINKER_NAME_SES2=!HT_LINKER_NAME_SES2:\=/!"
gsar.exe -s"link_linker_script_file=:x22$(ProjectDir)/linker.icf:x22" -r"link_linker_script_file=:x22$(ProjectDir)/%HT_LINKER_NAME_SES2%:x22" emStudiov4\Project_*.emProject -o 1> nul 2>&1

gsar.exe -s"<state>$PROJ_DIR$\linker.icf</state>" -r"<state>$PROJ_DIR$\%HT_LINKER_NAME_IAR%</state>" EWARM\*.ewp -o 1> nul 2>&1 
gsar.exe -s"<state>$PROJ_DIR$\linker.icf</state>" -r"<state>$PROJ_DIR$\%HT_LINKER_NAME_IAR%</state>" EWARMv8\*.ewp -o 1> nul 2>&1 

SET "HT_LINKER_NAME_GNU2=%HT_LINKER_NAME_GNU%"
SET "HT_LINKER_NAME_GNU2=!HT_LINKER_NAME_GNU2:\=/!"
gsar.exe -s"LINK_NAME_PATH = linker.ld" -r"LINK_NAME_PATH = %HT_LINKER_NAME_GNU2%" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<ScatterFile>.\linker.ld</ScatterFile>" -r"<ScatterFile>%HT_LINKER_NAME_GNU%</ScatterFile>" GNU_ARM\*.uvprojx -o 1> nul 2>&1

SET "HT_LINKER_NAME_HT32_IDE2=%HT_LINKER_NAME_HT32_IDE%"
SET "HT_LINKER_NAME_HT32_IDE2=!HT_LINKER_NAME_HT32_IDE2:\=/!"

CALL :ProcessPath "%HT_LINKER_NAME_HT32_IDE%" DEPTH FOLDER

FOR %%F IN ("!FOLDER!") DO SET "FILENAME=%%~nxF"

FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"<name>Linker/linker.ld</name>" -r"<name>Linker/!FILENAME!</name>" %%D\*.project -o 1> nul 2>&1
gsar.exe -s"<locationURI>PARENT-1-PROJECT_LOC/GNU_ARM/linker.ld</locationURI>" -r"<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!</locationURI>" %%D\*.project -o 1> nul 2>&1
)

FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"<listOptionValue builtIn=:x22false:x22 value=:x22../../GNU_ARM/linker.ld:x22/>" -r"<listOptionValue builtIn=:x22false:x22 value=:x22../../%HT_LINKER_NAME_HT32_IDE2%:x22/>" %%D\*.cproject -o 1> nul 2>&1
)
:LinkerScriptSET_End

:CREATE_PROJECT_END
IF EXIST "_ProjectConfigScript.bat" CALL _ProjectConfigScript.bat
DEL /Q _ProjectConfigScript.bat 1> nul 2>&1

REM Process "_ProjectSource.ini"
REM  ===========================================================================
IF EXIST "_ProjectSource.ini" (
  ECHO Success!
  ECHO Processing "_ProjectSource.ini". It may take a while....
  ECHO N > dummyn.txt
  COPY /-Y "..\..\..\project_template\Script\_ProjectSource.bat"  "." <dummyn.txt 1> nul 2>&1
  DEL dummyn.txt /Q
  rem CALL _ProjectSource.bat 1> nul 2>&1
  CALL _ProjectSource.bat
  DEL _ProjectSource.bat /Q 1> nul 2>&1
)

REM Process "_ProjectSource_ht32ide.ini"
REM  ===========================================================================
IF EXIST "_ProjectSource_ht32ide.ini" (
  ECHO Success!
  ECHO Processing "_ProjectSource_ht32ide.ini". It may take a while....
  ECHO N > dummyn.txt
  COPY /-Y "..\..\..\project_template\Script\_ProjectSource_ht32ide.bat"  "." <dummyn.txt 1> nul 2>&1
  DEL dummyn.txt /Q
  rem CALL _ProjectSource.bat 1> nul 2>&1
  CALL _ProjectSource_ht32ide.bat
  DEL _ProjectSource_ht32ide.bat /Q 1> nul 2>&1
)

REM All finished
REM  ===========================================================================
DEL gsar.exe /Q 1> nul 2>&1
ECHO Success!
ECHO.

:CREATE_PROJECT_FAIL
exit /b

:ProcessPath
setlocal ENABLEDELAYEDEXPANSION
set "LINE=%~1"
set "COUNT=0"
SET "LINE=!LINE:\=/!"

IF "!LINE!" EQU "./" (
  SET "LINE="
  GOTO AfterCount
)

:CountLoop
if "!LINE:~0,3!" NEQ "../" goto AfterCount
set /a COUNT+=1
set "LINE=!LINE:~3!"
goto CountLoop

:AfterCount
set /a RESULT=!COUNT! + 1

endlocal & (
    set "%~2=%RESULT%"
    set "%~3=%LINE%"
)
exit /b
