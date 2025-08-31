REM /*********************************************************************************************************//**
REM * @file    _ProjectConfig.bat
REM * @version $Rev:: 5906         $
REM * @date    $Date:: 2022-05-25 #$
REM * @brief   Project configure file.
REM *************************************************************************************************************

REM README
REM This file provides the function below. It shall be use with "_CreateProject.bat"
REM  1. Remove Project_xxxxx files that do not supported by the example/application code (xxxxx is model name).
REM  2. Change RO, RW Based address.
REM  3. Change Stack and Heap Size.
REM  4. Change include path.
REM  5. Apply specify modification by customer.
REM


REM Remove Project_xxxxx files that do not supported by the example/application code
REM ============================================================================
REM For device support, see _ProjectConfig.ini

rmdir /S /Q "emStudiov4"
rmdir /S /Q "EWARM"
rmdir /S /Q "EWARMv8"
rmdir /S /Q "GNU_ARM"
rmdir /S /Q "MDK_ARM"
rem rmdir /S /Q "MDK_ARMv5"
rem rmdir /S /Q "MDK_ARMv537"
rmdir /S /Q "SourceryG++Lite"
REM ============================================================================




REM !!! NOTICE: Do not put any space between the "=" !!!
REM !!!         "SET VAR=VALUE" is OK
REM !!!         "SET VAR = VALUE" is not allowed




REM Change RO, RW Based address
REM ============================================================================
SET HT_CHANGE_RO_RW=0
SET HT_RO_ADDR=0x00000000
SET HT_RW_ADDR=0x20000000
REM ============================================================================


REM Change Stack and Heap Size
REM ============================================================================
SET HT_CHANGE_STACK_HEAP=1
SET HT_STACK_SIZE=1024
SET HT_HEAP_SIZE=0
REM ============================================================================


REM Change include path
REM Note:
REM     1. HT_EXTRA_INCLUDE shall be separated by semicolons (;).
REM        Example HT_EXTRA_INCLUDE=..\Test1;..\Extra_Include;
REM     2. For IAR, support only 5 extra include path setting.
REM        (HT_EXTRA_INCLUDE_IAR1 ~ HT_EXTRA_INCLUDE_IAR5)
REM ============================================================================
SET HT_CHANGE_INCLUDE=1
SET HT_EXTRA_INCLUDE=..\..\src;
SET HT_EXTRA_INCLUDE_IAR1=..\..\src
SET HT_EXTRA_INCLUDE_IAR2=
SET HT_EXTRA_INCLUDE_IAR3=
SET HT_EXTRA_INCLUDE_IAR4=
SET HT_EXTRA_INCLUDE_IAR5=
REM ============================================================================


REM Change C define
REM Note:
REM     1. HT_EXTRA_CDEFINE shall be separated by comma (,).
REM        Example HT_EXTRA_CDEFINE=DEFINE1, DEFINE2
REM     2. For IAR, support only 5 extra C define setting.
REM        (HT_EXTRA_CDEFINE_IAR1 ~ HT_EXTRA_CDEFINE_IAR5)
REM ============================================================================
SET HT_CHANGE_CDEFINE=0
SET HT_EXTRA_CDEFINE=DEFINE1, DEFINE2
SET HT_EXTRA_CDEFINE_IAR1=DEFINE1
SET HT_EXTRA_CDEFINE_IAR2=DEFINE2
SET HT_EXTRA_CDEFINE_IAR3=
SET HT_EXTRA_CDEFINE_IAR4=
SET HT_EXTRA_CDEFINE_IAR5=
REM ============================================================================


REM Apply specify modification
REM Example: (":x0a" for newline "\n")
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARMv5\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" MDK_ARMv537\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" EWARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" EWARMv8\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" GNU_ARM\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
rem gsar.exe -s"SEARCH_STRING:x0a" -r"REPLACE_STRING:x0a" SourceryG++Lite\*_FILENAME_KEYWORD_*._ATTACHMENT_NAME_ -o
REM ============================================================================
rem Edit your code here....
REM ============================================================================
