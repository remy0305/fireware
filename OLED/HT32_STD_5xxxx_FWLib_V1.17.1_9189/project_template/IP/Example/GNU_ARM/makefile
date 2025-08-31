#/*---------------------------------------------------------------------------------------------------------*/
#/* Holtek Semiconductor Inc.                                                                               */
#/*                                                                                                         */
#/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
#/* All rights reserved.                                                                                    */
#/*                                                                                                         */
#/*-----------------------------------------------------------------------------------------------------------
#  File Name        : makefile
#  Version          : V1.10
#  Date             : 2021-01-13
#  Description      : The makefile.
#-----------------------------------------------------------------------------------------------------------*/
#
#/*---------------------------------------------------------------------------------------------------------*/
#/* How to Use                                                                                              */
#/*---------------------------------------------------------------------------------------------------------*/
#  1. Download and install GNU make for windows.
#     http://gnuwin32.sourceforge.net/packages/make.htm
#     http://gnuwin32.sourceforge.net/downlinks/make.php
#
#  2. Add "make" execution path into system Path.
#     For example: "C:\Program Files (x86)\GnuWin32\bin"
#
#  3. How to Build
#     Use command line and change working directory into the "GNU_ARM" folder of the project.
#     And then typing following command to build the code. xxxxx is chip name.
#       "make IC=xxxxx" or "make -f xxxxx.mk" or "make xxxxx"
#     For example:
#     --------------------------------------------------------------------------------------------------
#     |C:\Users\Username>d:                                                                            |
#     |D:\>cd HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM                       |
#     |D:\HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM>make -f 52352.mk          |
#     |                                                                                                |
#     |     ......build message......                                                                  |
#     |                                                                                                |
#     |arm-none-eabi-size.exe HT32M\52352\Obj\HT32.elf                                                 |
#     |   text    data     bss     dec     hex filename                                                |
#     |   3192       8      32    3232     ca0 HT32M\52352\Obj\HT32.elf                                |
#     |========                                                                                        |
#     |BUILD SUCCESS                                                                                   |
#     |                                                                                                |
#     |D:\HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM>                          |
#     --------------------------------------------------------------------------------------------------
#
#  4. How to Download (e-Link32 Pro/Lite or Starter Kit required)
#     Follow the step3 to change the working directory, typing following command. The xxxxx is chip name.
#       Erase:   "make IC=xxxxx eraseall" or "make -f xxxxx.mk eraseall" (Note: It apply the mass erase of the Flash.)
#       Program: "make IC=xxxxx program"  or "make -f xxxxx.mk program"
#       Run:     "make IC=xxxxx run"      or "make -f xxxxx.mk run"
#     You can also combine the eraseall/program/run command such as:
#       "make IC=xxxxx program run"
#       "make -f xxxxx.mk all eraseall program run clean"
#
#  5. How to Clean
#     Follow the step3 to change the working directory and typing  following command to clean.
#       "make IC=xxxxx clean" or "make -f xxxxx.mk clean" or "make clean"
#


#/*---------------------------------------------------------------------------------------------------------*/
#/* Make Targets                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
all:
ifeq "$(IC)" ""
	@echo Use following command to build/clean target or download the code. Use "make help" for detailed.
	@echo   Build:   "make IC=xxxxx"          or "make -f xxxxx.mk"          or "make xxxxx"
	@echo   Clean:   "make IC=xxxxx clean"    or "make -f xxxxx.mk clean"    or "make clean"
	@echo   Erase:   "make IC=xxxxx eraseall" or "make -f xxxxx.mk eraseall"
	@echo   Program: "make IC=xxxxx program"  or "make -f xxxxx.mk program"
	@echo   Run:     "make IC=xxxxx run"      or "make -f xxxxx.mk run"
	@echo             where xxxxx is chip name.
	@echo For example: "make IC=52352", "make -f 52352.mk", "make -f 52352.mk clean"
	@echo You can also combine the eraseall/program/run/clean command such as:
	@echo   "make IC=52352 program run"
	@echo   "make -f 52352.mk all eraseall program run clean"
	@echo Enjoy it!
endif


ifneq "$(IC)" ""
	@echo -
	@make -f $(IC).mk
endif

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "eraseall"
ifneq "$(MAKECMDGOALS)" "program"
ifneq "$(MAKECMDGOALS)" "run"
ifneq "$(MAKECMDGOALS)" "all"
ifneq "$(MAKECMDGOALS)" "help"
$(MAKECMDGOALS):
	@echo -
	@make -f $(MAKECMDGOALS).mk
endif
endif
endif
endif
endif
endif


help:
	@echo /*----------------------------------------------------------------------------------------------------------*/
	@echo /* How to Use                                                                                               */
	@echo /*----------------------------------------------------------------------------------------------------------*/
	@echo /*  1. Download and install GNU make for windows.                                                           */
	@echo /*     http://gnuwin32.sourceforge.net/packages/make.htm                                                    */
	@echo /*     http://gnuwin32.sourceforge.net/downlinks/make.php                                                   */
	@echo /*                                                                                                          */
	@echo /*  2. Add "make" execution path into system Path.                                                          */
	@echo /*     For example: "C:\Program Files (x86)\GnuWin32\bin"                                                   */
	@echo /*                                                                                                          */
	@echo /*  3. How to Build                                                                                         */
	@echo /*     Use command line and change working directory into the "GNU_ARM" folder of the project.              */
	@echo /*     And then typing following command to build the code. xxxxx is chip name.                             */
	@echo /*       "make IC=xxxxx" or "make -f xxxxx.mk" or "make xxxxx"                                              */
	@echo /*     For example:                                                                                         */
	@echo        "------------------------------------------------------------------------------------------"
	@echo        "|C:\Users\Username>d:                                                                    |"
	@echo        "|D:\>cd HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM               |"
	@echo        "|D:\HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM>make -f 52352.mk  |"
	@echo        "|                                                                                        |"
	@echo        "|     ......build message......                                                          |"
	@echo        "|                                                                                        |"
	@echo        "|arm-none-eabi-size.exe HT32M\52352\Obj\HT32.elf                                         |"
	@echo        "|   text    data     bss     dec     hex filename                                        |"
	@echo        "|   3192       8      32    3232     ca0 HT32M\52352\Obj\HT32.elf                        |"
	@echo        "|========                                                                                |"
	@echo        "|BUILD SUCCESS                                                                           |"
	@echo        "|                                                                                        |"
	@echo        "|D:\HT32_STD_5xxxx_FWLib_v005_2639\project_template\IP\Example\GNU_ARM>                  |"
	@echo        "------------------------------------------------------------------------------------------"
	@echo /*                                                                                                          */
	@echo /*  4. How to Download (e-Link32 Pro/Lite or Starter Kit required)                                          */
	@echo /*     Follow the step3 to change the working directory, typing following command. The xxxxx is chip name.  */
	@echo /*       Erase:   "make IC=xxxxx eraseall" or "make -f xxxxx.mk eraseall" (Flash mass erase)                */
	@echo /*       Program: "make IC=xxxxx program"  or "make -f xxxxx.mk program"                                    */
	@echo /*       Run:     "make IC=xxxxx run"      or "make -f xxxxx.mk run"                                        */
	@echo /*     You can also combine the eraseall/program/run command such as:                                       */
	@echo /*       "make IC=xxxxx program run"                                                                        */
	@echo /*       "make -f xxxxx.mk all eraseall program run clean"                                                  */
	@echo /*                                                                                                          */
	@echo /*  5. How to Clean                                                                                         */
	@echo /*     Follow the step3 to change the working directory and typing  following command to clean.             */
	@echo /*       "make IC=xxxxx clean" or "make -f xxxxx.mk clean" or "make clean"                                  */
	@echo /*                                                                                                          */


clean:
	@echo -
	-del /q /f *.o *.bin *.elf *.hex *.map *.d 1>nul 2>&1 || (exit 0)
	-rmdir /S /Q "HT32M\" 1>nul 2>&1 || (exit 0)
	@echo ========
	@echo CLEAN SUCCESS


eraseall:
	@make -f $(IC).mk eraseall


program:
	@make -f $(IC).mk program


run:
	@make -f $(IC).mk run
