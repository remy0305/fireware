#/*---------------------------------------------------------------------------------------------------------*/
#/* Holtek Semiconductor Inc.                                                                               */
#/*                                                                                                         */
#/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
#/* All rights reserved.                                                                                    */
#/*                                                                                                         */
#/*-----------------------------------------------------------------------------------------------------------
#  File Name        : 52241.mk
#  Version          : V1.20
#  Date             : 2022-05-13
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
#/* Compiler Setting                                                                                        */
#/*---------------------------------------------------------------------------------------------------------*/
ARM_CORE = cortex-m0
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = arm-none-eabi-ar
LD = arm-none-eabi-ld
SIZE = arm-none-eabi-size.exe
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
PROGRAMMER=..\..\..\..\utilities\elink32pro\eLink32pro.exe
#GNU_PATH = C:/Program Files (x86)/GNU Tools Arm Embedded/7 2018-q2-update/


#/*---------------------------------------------------------------------------------------------------------*/
#/* Target Setting                                                                                          */
#/*---------------------------------------------------------------------------------------------------------*/
CHIP_NAME = 52241
STARTUP = startup_ht32f5xxxx_gcc_01
TARGET_NAME = HT32


#/*---------------------------------------------------------------------------------------------------------*/
#/* Options: CC, Assembeler, Linker                                                                         */
#/*---------------------------------------------------------------------------------------------------------*/
ARCH_OPTION = -mcpu=$(ARM_CORE) -mthumb -mthumb-interwork
C_OPTION = -gdwarf-2 -MD -Wall -Os -mapcs-frame -ffunction-sections -fdata-sections
L_OPTION = -Wl,-Map=$(TARGET_NAME).map -Wl,--gc-sections --specs=nano.specs


#/*---------------------------------------------------------------------------------------------------------*/
#/* Preprocessor Define                                                                                     */
#/*---------------------------------------------------------------------------------------------------------*/
C_OPTION += -DUSE_HT32_DRIVER
C_OPTION += -DUSE_HT32F52241_SK
C_OPTION += -DUSE_HT32F52231_41
C_OPTION += -DUSE_MEM_HT32F52241
S_OPTION = --defsym USE_HT32_CHIP=2


#/*---------------------------------------------------------------------------------------------------------*/
#/* Include Path                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
INCLUDE_PATH += -I./../
INCLUDE_PATH += -I./../../../../library/CMSIS/Include
INCLUDE_PATH += -I./../../../../library/Device/Holtek/HT32F5xxxx/Include
INCLUDE_PATH += -I./../../../../library/HT32F5xxxx_Driver/inc
INCLUDE_PATH += -I./../../../../library/HT32_USBD_Library/inc
INCLUDE_PATH += -I./../../../../utilities

#INCLUDE_PATH += -I"$(GNU_PATH)arm-none-eabi/include"
#INCLUDE_PATH += -I"$(GNU_PATH)lib/gcc/arm-none-eabi/7.3.1/include"
#INCLUDE_PATH += -I"$(GNU_PATH)arm-none-eabi/include/c++/7.3.1"
#INCLUDE_PATH += -I"$(GNU_PATH)arm-none-eabi/include/c++/7.3.1/arm-none-eabi"


#/*---------------------------------------------------------------------------------------------------------*/
#/* Source files                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
SOURCE_NAME_PATH += ../main.c
SOURCE_NAME_PATH += ../ht32f5xxxx_01_it.c
SOURCE_NAME_PATH += ../system_ht32f5xxxx_02.c
#SOURCE_NAME_PATH += ../ADD_YOUR_C_CODE_FILE_HERE.c

HT32_USB_PATH = ../../../../library/HT32_USBD_Library/src/
HT32_LIB_PATH = ../../../../library/HT32F5xxxx_Driver/src/
HT32_UTL_PATH = ../../../../utilities/

SOURCE_NAME_PATH += \
$(HT32_LIB_PATH)ht32_cm0plus_misc.c \
$(HT32_LIB_PATH)ht32f5xxxx_adc.c \
$(HT32_LIB_PATH)ht32f5xxxx_bftm.c \
$(HT32_LIB_PATH)ht32f5xxxx_ckcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_crc.c \
$(HT32_LIB_PATH)ht32f5xxxx_exti.c \
$(HT32_LIB_PATH)ht32f5xxxx_flash.c \
$(HT32_LIB_PATH)ht32f5xxxx_gpio.c \
$(HT32_LIB_PATH)ht32f5xxxx_i2c.c \
$(HT32_LIB_PATH)ht32f5xxxx_mctm.c \
$(HT32_LIB_PATH)ht32f5xxxx_pwrcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_rstcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_rtc.c \
$(HT32_LIB_PATH)ht32f5xxxx_spi.c \
$(HT32_LIB_PATH)ht32f5xxxx_tm.c \
$(HT32_LIB_PATH)ht32f5xxxx_usart.c \
$(HT32_LIB_PATH)ht32f5xxxx_wdt.c \
$(HT32_LIB_PATH)ht32_retarget.c \
$(HT32_LIB_PATH)ht32_serial.c \
$(HT32_LIB_PATH)printf.c \
$(HT32_LIB_PATH)syscalls.c \
$(HT32_UTL_PATH)ht32_board.c \
$(HT32_UTL_PATH)common/i2c_eeprom.c \
$(HT32_UTL_PATH)common/spi_flash.c \
$(HT32_UTL_PATH)common/spi_lcd.c \


#/*---------------------------------------------------------------------------------------------------------*/
#/* MISC Setting                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
LINK_NAME_PATH = linker.ld
START_NAME_PATH = $(STARTUP).s

C_OBJECT_OPTION = $(ARCH_OPTION) $(C_OPTION) -c
S_OBJECT_OPTION = $(ARCH_OPTION) $(S_OPTION)
LINK_OPTION = $(ARCH_OPTION) $(L_OPTION)

HEX_OPTION = -O ihex
BIN_OPTION = -O binary
TEXT_OPTION = -D
#TEXT_OPTION = -S

OBJS = $(wildcard *.o)

#/*---------------------------------------------------------------------------------------------------------*/
#/* Make Targets                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
all:$(TARGET_NAME).o $(TARGET_NAME).elf $(TARGET_NAME).hex $(TARGET_NAME).bin $(TARGET_NAME).text
	@echo -
	@-mkdir HT32M 1>nul 2>&1 || (exit 0)
	@-mkdir HT32M\$(CHIP_NAME) 1>nul 2>&1 || (exit 0)
	@-mkdir HT32M\$(CHIP_NAME)\Obj 1>nul 2>&1 || (exit 0)
	@move /Y $(TARGET_NAME).elf ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y $(TARGET_NAME).hex ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y $(TARGET_NAME).bin ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y *.o ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y *.d ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y *.map ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	@move /Y *.text ".\HT32M\$(CHIP_NAME)\Obj\" 1>nul 2>&1
	$(SIZE) HT32M\$(CHIP_NAME)\Obj\$(TARGET_NAME).elf
	@echo ========
	@echo BUILD SUCCESS

$(TARGET_NAME).o: $(START_NAME_PATH) $(SOURCE_NAME_PATH)
	@echo Compiling...
	$(AS) $(S_OBJECT_OPTION) $(START_NAME_PATH) -o $(STARTUP).o
	$(CC) $(C_OBJECT_OPTION) $(INCLUDE_PATH) $(SOURCE_NAME_PATH)

$(TARGET_NAME).elf: $(OBJS) $(START_NAME_PATH) $(SOURCE_NAME_PATH)
	@echo Linking...
	$(CC) -T$(LINK_NAME_PATH) $(LINK_OPTION) $(OBJS) -o $(TARGET_NAME).elf

$(TARGET_NAME).hex: $(TARGET_NAME).elf
	$(OBJCOPY) $(HEX_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).hex

$(TARGET_NAME).bin: $(TARGET_NAME).elf
	$(OBJCOPY) $(BIN_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).bin

$(TARGET_NAME).text: $(TARGET_NAME).elf
	$(OBJDUMP) $(TEXT_OPTION) $(TARGET_NAME).elf > $(TARGET_NAME).text

clean:
	@echo -
	-del /q /f *.o *.bin *.elf *.hex *.map *.d 1>nul 2>&1 || (exit 0)
	-rmdir /S /Q "HT32M\" 1>nul 2>&1 || (exit 0)
	@echo ========
	@echo CLEAN SUCCESS


eraseall:
	@echo -
	$(PROGRAMMER) -me
	@echo ========
	@echo ERASEALL SUCCESS


program:
	@echo -
	$(PROGRAMMER) -a ".\HT32M\$(CHIP_NAME)\Obj\$(TARGET_NAME).bin" -v ".\HT32M\$(CHIP_NAME)\Obj\$(TARGET_NAME).bin"
	@echo ========
	@echo PROGRAM SUCCESS


run:
	@echo -
	$(PROGRAMMER) -run
	@echo ========
	@echo RUN SUCCESS
