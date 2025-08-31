REM @ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _ProjectSource.bat
REM * @version $Rev:: 7608         $
REM * @date    $Date:: 2024-02-24 #$
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

SET PSRC_CONFIG_FILE=_ProjectSource.ini

IF NOT EXIST %PSRC_CONFIG_FILE% GOTO NOUSERFILE

IF NOT EXIST gsar.exe COPY "..\..\..\gsar.e_x_e" "."
RENAME gsar.e_x_e gsar.exe


REM =======================
REM Add into "User" group
REM =======================
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_*.uvproj -o
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_*.uvprojx -o

gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s"SOURCE_NAME_PATH += ../main.c" -r"SOURCE_NAME_PATH += ../main.c:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o
gsar.exe -s"(LINK_OPTION) *.o" -r"(LINK_OPTION) *.o<HTGSARCONT_LIBA>" GNU_ARM\*.mk -o

gsar.exe -s"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f1xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32f4xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o
gsar.exe -s"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>" -r"<FilePath>..\ht32l5xxxx_01_it.c</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_*.uvprojx -o

gsar.exe -s"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a    </file>" -r"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_*.ewp -o
gsar.exe -s"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a        </file>" -r"<name>$PROJ_DIR$\..\main.c</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_*.ewp -o

gsar.exe -s"<file file_name=:x22../ht32f5xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f5xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o
gsar.exe -s"<file file_name=:x22../ht32f1xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f1xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o
gsar.exe -s"<file file_name=:x22../ht32f4xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32f4xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o
gsar.exe -s"<file file_name=:x22../ht32l5xxxx_01_it.c:x22 />" -r"<file file_name=:x22../ht32l5xxxx_01_it.c:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_*.emProject -o

FOR /F "tokens=1,2,3,4,5 delims=, " %%i IN (%PSRC_CONFIG_FILE%) DO (

  IF NOT "%%i" == "REM" (

  IF "%%i" == "User" (
    SET l=%%l
    IF "%%l"=="" (
    SET l=%%k
    SET k=""
    )
    SET m=%%m
    IF "%%m" == "" (
    SET m="*"
    )

    IF "%%j" == "4" (
      REM Keil .lib
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "6" (
      REM IAR .a
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "7" (
      REM GNU .a
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o

      gsar.exe -s"<HTGSARCONT_LIBA>" -r" %%k%%l<HTGSARCONT_LIBA>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "8" (
      REM SES .a
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "11" (
      REM Keil .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "12" (
      REM Keil .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "13" (
      REM Keil .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "21" (
      REM IAR .c
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "22" (
      REM IAR .s
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "23" (
      REM IAR .cpp
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "31" (
      REM GNU .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "32" (
      REM GNU .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "33" (
      REM GNU .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "41" (
      REM SES .c
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "42" (
      REM SES .s
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "43" (
      REM SES .cpp
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else (
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      if "%%j" == "3" (
        REM Keil_GNU .cpp
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      ) else (
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      )
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o

      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o

      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    )

  )

  )

)

gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o

gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o

gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o

REM =======================
REM Add into user defined group
REM =======================
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARM\Project_*.uvproj -o
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s"        <Group>:x0a          <GroupName>Config</GroupName>" -r"<HTGSARCONT_GROUP>:x0a        <Group>:x0a          <GroupName>Config</GroupName>" SourceryG++Lite\Project_*.uvprojx -o

gsar.exe -s"  <group>:x0d:x0a    <name>Utilities</name>" -r"<HTGSARCONT_GROUP>:x0d:x0a  <group>:x0d:x0a    <name>Utilities</name>" EWARM\Project_*.ewp -o
gsar.exe -s"    <group>:x0d:x0a        <name>Utilities</name>" -r"<HTGSARCONT_GROUP>:x0d:x0a    <group>:x0d:x0a        <name>Utilities</name>" EWARMv8\Project_*.ewp -o

gsar.exe -s"    <folder Name=:x22Config:x22>" -r"<HTGSARCONT_GROUP>:x0a    <folder Name=:x22Config:x22>" emStudiov4\Project_*.emProject -o

SET CURRENT_GROUP=0

FOR /F "tokens=1,2,3,4,5 delims=, " %%i IN (%PSRC_CONFIG_FILE%) DO (

  IF NOT "%%i" == "REM" (
  
  IF NOT "%%i" == "User" (

    IF NOT !CURRENT_GROUP! == %%i (
      SET CURRENT_GROUP=%%i
      gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o
      gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o
      gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o
      gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o
      gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o
      gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o
      gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o
      gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o

      gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARM\Project_*.uvproj -o
      gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv5\Project_*.uvprojx -o
      gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" MDK_ARMv537\Project_*.uvprojx -o
      gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" GNU_ARM\Project_*.uvprojx -o
      gsar.exe -s"<HTGSARCONT_GROUP>" -r"        <Group>:x0a          <GroupName>%%i</GroupName>:x0a          <Files>:x0a<HTGSARCONT>:x0a          </Files>:x0a        </Group>:x0a<HTGSARCONT_GROUP>" SourceryG++Lite\Project_*.uvprojx -o

      gsar.exe -s"<HTGSARCONT_GROUP>" -r"  <group>:x0d:x0a    <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a  </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARM\Project_*.ewp -o
      gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <group>:x0d:x0a        <name>%%i</name>:x0d:x0a<HTGSARCONT>:x0d:x0a    </group>:x0d:x0a<HTGSARCONT_GROUP>" EWARMv8\Project_*.ewp -o

      gsar.exe -s"<HTGSARCONT_GROUP>" -r"    <folder Name=:x22%%i:x22>:x0a<HTGSARCONT>:x0a    </folder>:x0a<HTGSARCONT_GROUP>" emStudiov4\Project_*.emProject -o
    )
    SET l=%%l
    IF "%%l"=="" (
    SET l=%%k
    SET k=""
    )
    SET m=%%m
    IF "%%m" == "" (
    SET m="*"
    )

    IF "%%j" == "4" (
      REM Keil .lib
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "6" (
      REM IAR .a
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "7" (
      REM GNU .a
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>4</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o

      gsar.exe -s"<HTGSARCONT_LIBA>" -r" %%k%%l<HTGSARCONT_LIBA>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "8" (
      REM SES .a
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "11" (
      REM Keil .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "12" (
      REM Keil .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "13" (
      REM Keil .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
    ) else if "%%j" == "21" (
      REM IAR .c
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "22" (
      REM IAR .s
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "23" (
      REM IAR .cpp
      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o
    ) else if "%%j" == "31" (
      REM GNU .c
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>1</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "32" (
      REM GNU .s
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>2</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "33" (
      REM GNU .cpp
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o
    ) else if "%%j" == "41" (
      REM SES .c
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "42" (
      REM SES .s
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else if "%%j" == "43" (
      REM SES .cpp
      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    ) else (
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
      gsar.exe -s"<HTGSARCONT>" -r"            <File>:x0a              <FileName>!l!</FileName>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      if "%%j" == "3" (
        REM Keil_GNU .cpp
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>8</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      ) else (
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARM\Project_!m!.uvproj -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv5\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" MDK_ARMv537\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" GNU_ARM\Project_!m!.uvprojx -o
        gsar.exe -s"<HTGSARCONT>" -r"              <FileType>%%j</FileType>:x0a              <FilePath>%%k%%l</FilePath>:x0a            </File>:x0a<HTGSARCONT>" SourceryG++Lite\Project_!m!.uvprojx -o
      )

      gsar.exe -s"<HTGSARCONT>" -r"SOURCE_NAME_PATH += %%k%%l:x0d:x0a<HTGSARCONT>" GNU_ARM\!m!.mk -o

      gsar.exe -s"<HTGSARCONT>" -r"    <file>:x0d:x0a      <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a    </file>:x0d:x0a<HTGSARCONT>" EWARM\Project_!m!.ewp -o
      gsar.exe -s"<HTGSARCONT>" -r"        <file>:x0d:x0a            <name>$PROJ_DIR$\%%k%%l</name>:x0d:x0a        </file>:x0d:x0a<HTGSARCONT>" EWARMv8\Project_!m!.ewp -o

      gsar.exe -s"<HTGSARCONT>" -r"      <file file_name=:x22%%k%%l:x22 />:x0a<HTGSARCONT>" emStudiov4\Project_!m!.emProject -o
    )
  )

  )

)


gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARM\Project_*.uvproj -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" SourceryG++Lite\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT>" -r"" emStudiov4\Project_*.emProject -o
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" GNU_ARM\*.mk -o
gsar.exe -s"<HTGSARCONT_LIBA>" -r"" GNU_ARM\*.mk -o
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARM\Project_*.ewp -o
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" EWARMv8\Project_*.ewp -o

gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARM\Project_*.uvproj -o
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARMv5\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" MDK_ARMv537\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" GNU_ARM\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" SourceryG++Lite\Project_*.uvprojx -o
gsar.exe -s":x0a<HTGSARCONT_GROUP>" -r"" emStudiov4\Project_*.emProject -o
gsar.exe -s":x0d:x0a<HTGSARCONT_GROUP>" -r"" EWARM\Project_*.ewp -o
gsar.exe -s":x0d:x0a<HTGSARCONT_GROUP>" -r"" EWARMv8\Project_*.ewp -o


DEL gsar.exe /Q

:NOUSERFILE
