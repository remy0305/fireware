REM @ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _ProjectSource.bat
REM * @version $Rev:: 9172         $
REM * @date    $Date:: 2025-06-23 #$
REM * @brief   Add source file into project.
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
SETLOCAL ENABLEDELAYEDEXPANSION

SET PSRC_CONFIG_FILE=_ProjectSource_ht32ide.ini

IF NOT EXIST %PSRC_CONFIG_FILE% GOTO NOUSERFILE

IF NOT EXIST gsar.exe COPY "..\..\..\gsar.e_x_e" "." 1> nul 2>&1
IF EXIST gsar.e_x_e RENAME gsar.e_x_e gsar.exe


REM =======================
REM Add into "User" group
REM =======================
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1

gsar.exe -s"SOURCE_NAME_PATH += ../main.c" -r"SOURCE_NAME_PATH += ../main.c:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1

REM TO-DO GNU .mk OT WORK
gsar.exe -s"(LINK_OPTION) *.o" -r"(LINK_OPTION) *.o<HTGSARCONT_LIBA>" GNU_ARM\*.mk -o 1> nul 2>&1

gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a    </file>" -r"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a        </file>" -r"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_*.ewp -o 1> nul 2>&1

gsar.exe -s"<file file_name=:x22../ht32f5xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f5xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s"<file file_name=:x22../ht32f1xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f1xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s"<file file_name=:x22../ht32f4xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f4xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s"<file file_name=:x22../ht32l5xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32l5xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o 1> nul 2>&1

FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"<locationURI>PARENT-2-PROJECT_LOC/ht32f5xxxx_01_it.c</locationURI>:x0a		</link>" -r"<locationURI>PARENT-2-PROJECT_LOC/ht32f5xxxx_01_it.c</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
gsar.exe -s"<locationURI>PARENT-2-PROJECT_LOC/ht32f1xxxx_01_it.c</locationURI>:x0a		</link>" -r"<locationURI>PARENT-2-PROJECT_LOC/ht32f1xxxx_01_it.c</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
gsar.exe -s"<locationURI>PARENT-2-PROJECT_LOC/ht32f4xxxx_01_it.c</locationURI>:x0a		</link>" -r"<locationURI>PARENT-2-PROJECT_LOC/ht32f4xxxx_01_it.c</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
gsar.exe -s"<locationURI>PARENT-2-PROJECT_LOC/ht32l5xxxx_01_it.c</locationURI>:x0a		</link>" -r"<locationURI>PARENT-2-PROJECT_LOC/ht32l5xxxx_01_it.c</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
)

FOR /F "tokens=1,2,3,4,5 delims=, " %%i IN (%PSRC_CONFIG_FILE%) DO (

  IF NOT "%%i" == "REM" (

  IF "%%i" == "User" (
    SET k=%%k
    IF "%%k" == ".\" (
      SET k=
      SET Uk=
    ) ELSE (
      SET Uk=%%k
      SET "Uk=!Uk:\=/!"      
    )

    SET l=%%l
    SET m=%%m
    IF "%%m" == "" (
      SET m=*
    )

    CALL :ProcessPath "%%~k" DEPTH FOLDER
    REM ECHO %%i, %%j, !k!, !Uk!, !l!, !m!, !DEPTH!, !FOLDER!

    IF "%%j" == "4" (
      REM Keil .lib
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "6" (
      REM IAR .a
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "7" (
      REM GNU .a
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1

      REM !!! TO-DO add .a file to GNU .mk NOT WORK!!!
      gsar.exe -s"<HTGSARCONT_LIBA>" -r" !Uk!!l!<HTGSARCONT_LIBA>" GNU_ARM\!m!.mk -o 1> nul 2>&1

    ) else if "%%j" == "8" (
      REM SES .a
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "9" (
      REM HT32-IDE .a
      REM !!! NOT SUPPORT YET !!!

    ) else if "%%j" == "11" (
      REM Keil .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "12" (
      REM Keil .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "13" (
      REM Keil .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "21" (
      REM IAR .c
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "22" (
      REM IAR .s
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "23" (
      REM IAR .cpp
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "31" (
      REM GNU .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "32" (
      REM GNU .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "33" (
      REM GNU .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "41" (
      REM SES .c
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "42" (
      REM SES .s
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "43" (
      REM SES .cpp
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "51" (
      REM HT32-IDE .c
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!l!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!l!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else if "%%j" == "52" (
      REM HT32-IDE .s
      SET "FNAME=!l!"
      SET "FNAME=!FNAME:.s=.S!"
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!FNAME!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!FNAME!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else if "%%j" == "53" (
      REM HT32-IDE .cpp
      REM is type 1 correct?
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!l!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!l!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else (
      REM 1, 2, 3, 5
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      if "%%j" == "3" (
        REM Keil_GNU .cpp
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      ) else (
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      )
      if NOT "%%j" == "5" (
        gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
      )

      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1

      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1

      IF "%%j" == "2" (
      SET "FNAME=!l!"
      SET "FNAME=!FNAME:.s=.S!"
      ) ELSE (
      SET "FNAME=!l!"
      )
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!FNAME!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!FNAME!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    )
  )

  )
)

gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1

gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1

gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1

REM =======================
REM Add into user defined group
REM =======================
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1

gsar.exe -s"  <group>:x0d:x0a    <name>Utilities</name>" -r"<HTGSARCONT_GROUP>:x0d:x0a  <group>:x0d:x0a    <name>Utilities</name>" EWARM\Project_*.ewp -o 1> nul 2>&1
gsar.exe -s"    <group>:x0d:x0a        <name>Utilities</name>" -r"<HTGSARCONT_GROUP>:x0d:x0a    <group>:x0d:x0a        <name>Utilities</name>" EWARMv8\Project_*.ewp -o 1> nul 2>&1

gsar.exe -s"    <folder Name=:x22Config:x22>" -r"<HTGSARCONT_GROUP>:x0a    <folder Name=:x22Config:x22>" emStudiov4\Project_*.emProject -o 1> nul 2>&1

FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s"						<entry flags=:x22VALUE_WORKSPACE_PATH:x22 kind=:x22sourcePath:x22 name=:x22Config:x22/>" -r"<HTGSARCONT_GROUP>:x0a						<entry flags=:x22VALUE_WORKSPACE_PATH:x22 kind=:x22sourcePath:x22 name=:x22Config:x22/>" %%D\*.cproject -o 1> nul 2>&1
)

SET CURRENT_GROUP=0
SET CURRENT_GROUP_KEIL=0
SET CURRENT_GROUP_IAR=0
SET CURRENT_GROUP_GNU=0
SET CURRENT_GROUP_SES=0
SET CURRENT_GROUP_HT32IDE=0

FOR /F "tokens=1,2,3,4,5 delims=, " %%i IN (%PSRC_CONFIG_FILE%) DO (

  IF NOT "%%i" == "REM" (

  IF NOT "%%i" == "User" (

    REM ECHO ====%%i %%j %%k %%l %%m

      IF "%%j" == "4" (
        REM Keil .lib
        IF NOT !CURRENT_GROUP_KEIL! == %%i (
          SET CURRENT_GROUP_KEIL=%%i
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
        )
      ) else if "%%j" == "6" (
        REM IAR .a
        IF NOT !CURRENT_GROUP_IAR! == %%i (
          SET CURRENT_GROUP_IAR=%%i
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"  <group>:x0d:x0a    <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a  </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <group>:x0d:x0a        <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a    </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARMv8\Project_*.ewp -o 1> nul 2>&1
        )
      ) else if "%%j" == "7" (
        REM GNU .a
        IF NOT !CURRENT_GROUP_GNU! == %%i (
          SET CURRENT_GROUP_GNU=%%i
          gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
        )
      ) else if "%%j" == "8" (
        REM SES .a
        IF NOT !CURRENT_GROUP_SES! == %%i (
          SET CURRENT_GROUP_SES=%%i
          gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <folder Name=:x22%%i:x22>:x0a<HTGSARCONT>:x0a    </folder>:x0a<HTGSARCONT_GROUP>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
        )
      ) else if "%%j" == "9" (
        REM HT32-IDE .a
        IF NOT !CURRENT_GROUP_HT32IDE! == %%i (
          SET CURRENT_GROUP_HT32IDE=%%i
          FOR /D %%D IN (HT32-IDE\Project_*) DO (
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"						<entry flags=:x22VALUE_WORKSPACE_PATH:x22 kind=:x22sourcePath:x22 name=:x22%%i:x22/>:x0a<HTGSARCONT_GROUP>" %%D\*.cproject -o 1> nul 2>&1
          )
        )
      ) else if %%j LEQ 5 (
        REM , 1, 2, 3, 5
        IF NOT !CURRENT_GROUP! == %%i (
          SET CURRENT_GROUP=%%i
          SET CURRENT_GROUP_KEIL=%%i
          SET CURRENT_GROUP_IAR=%%i
          SET CURRENT_GROUP_GNU=%%i
          SET CURRENT_GROUP_SES=%%i
          SET CURRENT_GROUP_HT32IDE=%%i
          REM ECHO Create 1235 !CURRENT_GROUP!
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1

          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1

          gsar.exe -s"<HTGSARCONT_GROUP>" -r"  <group>:x0d:x0a    <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a  </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <group>:x0d:x0a        <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a    </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARMv8\Project_*.ewp -o 1> nul 2>&1

          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <folder Name=:x22%%i:x22>:x0a<HTGSARCONT>:x0a    </folder>:x0a<HTGSARCONT_GROUP>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
          FOR /D %%D IN (HT32-IDE\Project_*) DO (
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"						<entry flags=:x22VALUE_WORKSPACE_PATH:x22 kind=:x22sourcePath:x22 name=:x22%%i:x22/>:x0a<HTGSARCONT_GROUP>" %%D\*.cproject -o 1> nul 2>&1
          )
        )
      ) else if %%j LEQ 13 (
        REM Keil .c 11
        REM Keil .cpp 12
        REM Keil .cpp 13
        IF NOT !CURRENT_GROUP_KEIL! == %%i (
          SET CURRENT_GROUP_KEIL=%%i
          REM ECHO Create 13 !CURRENT_GROUP_KEIL!
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
        )
      ) else if %%j LEQ 23 (
        REM IAR .c 21
        REM IAR .cpp 22
        REM IAR .cpp 23
        REM ECHO CURRENT_GROUP_IAR=!CURRENT_GROUP_IAR!
        REM ECHO %%i
        IF NOT !CURRENT_GROUP_IAR! == %%i (
          SET CURRENT_GROUP_IAR=%%i
          REM ECHO Create 23 !CURRENT_GROUP_IAR!
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"  <group>:x0d:x0a    <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a  </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARM\Project_*.ewp -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <group>:x0d:x0a        <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a    </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARMv8\Project_*.ewp -o 1> nul 2>&1
        )
      ) else if %%j LEQ 33 (
        REM GNU .c 31
        REM GNU .cpp 32
        REM GNU .cpp 33
        REM ECHO CURRENT_GROUP_GNU=!CURRENT_GROUP_GNU!
        IF NOT !CURRENT_GROUP_GNU! == %%i (
          SET CURRENT_GROUP_GNU=%%i
          REM ECHO Create 33 !CURRENT_GROUP_GNU!
          gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
        )
      ) else if %%j LEQ 43 (
        REM SES .c 41
        REM SES .cpp 42
        REM SES .cpp 43
        IF NOT !CURRENT_GROUP_SES! == %%i (
          SET CURRENT_GROUP_SES=%%i
          gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <folder Name=:x22%%i:x22>:x0a<HTGSARCONT>:x0a    </folder>:x0a<HTGSARCONT_GROUP>" emStudiov4\Project_*.emProject -o 1> nul 2>&1
        )
      ) else if %%j LEQ 53 (
        REM HT32-IDE .c 51
        REM HT32-IDE .cpp 52
        REM HT32-IDE .cpp 53
        IF NOT !CURRENT_GROUP_HT32IDE! == %%i (
          SET CURRENT_GROUP_HT32IDE=%%i
          FOR /D %%D IN (HT32-IDE\Project_*) DO (
          gsar.exe -s"<HTGSARCONT_GROUP>" -r"						<entry flags=:x22VALUE_WORKSPACE_PATH:x22 kind=:x22sourcePath:x22 name=:x22%%i:x22/>:x0a<HTGSARCONT_GROUP>" %%D\*.cproject -o 1> nul 2>&1
          )
        )
      )

    SET k=%%k
    IF "%%k" == ".\" (
      SET k=
      SET Uk=
    ) ELSE (
      SET Uk=%%k
      SET "Uk=!Uk:\=/!"      
    )

    SET l=%%l
    SET m=%%m
    IF "%%m" == "" (
      SET m=*
    )

    CALL :ProcessPath "%%~k" DEPTH FOLDER
    REM ECHO %%i, %%j, !k!, !Uk!, !l!, !m!, !DEPTH!, !FOLDER!

    IF "%%j" == "4" (
      REM Keil .lib
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "6" (
      REM IAR .a
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "7" (
      REM GNU .a
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1

      REM !!! TO-DO add .a file to GNU .mk NOT WORK!!!
      gsar.exe -s"<HTGSARCONT_LIBA>" -r" !Uk!!l!<HTGSARCONT_LIBA>" GNU_ARM\!m!.mk -o 1> nul 2>&1

    ) else if "%%j" == "8" (
      REM SES .a
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "9" (
      REM HT32-IDE .a
      REM !!! NOT SUPPORT YET !!!

    ) else if "%%j" == "11" (
      REM Keil .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "12" (
      REM Keil .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "13" (
      REM Keil .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
    ) else if "%%j" == "21" (
      REM IAR .c
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "22" (
      REM IAR .s
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "23" (
      REM IAR .cpp
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1
    ) else if "%%j" == "31" (
      REM GNU .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "32" (
      REM GNU .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "33" (
      REM GNU .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
    ) else if "%%j" == "41" (
      REM SES .c
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "42" (
      REM SES .s
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "43" (
      REM SES .cpp
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1
    ) else if "%%j" == "51" (
      REM HT32-IDE .c
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!l!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!l!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else if "%%j" == "52" (
      REM HT32-IDE .s
      SET "FNAME=!l!"
      SET "FNAME=!FNAME:.s=.S!"
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!FNAME!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!FNAME!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else if "%%j" == "53" (
      REM HT32-IDE .cpp
      REM is type 1 correct?
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!l!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!l!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    ) else (
      REM 1, 2, 3, 5
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      if "%%j" == "3" (
        REM Keil_GNU .cpp
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      ) else (
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o 1> nul 2>&1
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>!k!!l!</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o 1> nul 2>&1
      )
      if NOT "%%j" == "5" (
        gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += !Uk!!l!:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o 1> nul 2>&1
      )

      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o 1> nul 2>&1
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\!k!!l!</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o 1> nul 2>&1

      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22!Uk!!l!:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o 1> nul 2>&1

      IF "%%j" == "2" (
      SET "FNAME=!l!"
      SET "FNAME=!FNAME:.s=.S!"
      ) ELSE (
      SET "FNAME=!l!"
      )
      FOR /D %%D IN (HT32-IDE\Project_!m!) DO (
      gsar.exe -s"<HTGSARCONT>" -r"		<link>:x0a			<name>%%i/!FNAME!</name>:x0a			<type>1</type>:x0a			<locationURI>PARENT-!DEPTH!-PROJECT_LOC/!FOLDER!!FNAME!</locationURI>:x0a		</link>:x0a<HTGSARCONT>"  %%D\*.project -o 1> nul 2>&1
      )
    )
  )

  )
)


gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT_LIBA>" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s":x0a<HTGSARCONT>" -r"" %%D\*.project -o 1> nul 2>&1
)

gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARM\Project_*.uvproj -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARMv5\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARMv537\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" GNU_ARM\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" SourceryG++Lite\Project_*.uvprojx -o 1> nul 2>&1
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT_GROUP>" -r"" EWARM\Project_*.ewp -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT_GROUP>" -r"" EWARMv8\Project_*.ewp -o 1> nul 2>&1
FOR /D %%D IN (HT32-IDE\Project_*) DO (
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" %%D\*.cproject -o 1> nul 2>&1
)

DEL gsar.exe /Q

:NOUSERFILE

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
