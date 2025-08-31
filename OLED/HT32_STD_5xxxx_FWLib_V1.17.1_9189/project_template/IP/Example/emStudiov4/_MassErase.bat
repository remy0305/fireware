@ECHO OFF
SET TARGET_CHIP=HT32F52352
SET PACK_FILE=..\..\..\..\utilities\pack\Holtek.HT32_DFP.latest.pack

pyocd erase --chip -t %TARGET_CHIP% --pack=%PACK_FILE%

pause
