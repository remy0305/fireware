/*********************************************************************************************************//**
 * @file    THIRD_PARTY_LICENSE_Gsar_readme.txt
 * @version $Rev:: 326          $
 * @date    $Date:: 2025-05-02 #$
 * @brief   Third-Party Tool Usage Notice - Gsar.
 *************************************************************************************************************

Third-Party Tool Usage Notice - Gsar
========================================
This HOLTEK HT32 Firmware Library and HT32 Application Code utilizes the following third-party utility for automated text replacement tasks:

Tool Used:
- gsar.exe

Source:
- gsar-1.21-bin.zip
This tool is part of the Gsar (General Search And Replace) project, provided through the GnuWin32 project. It is used to perform search-and-replace operations on binary or text files via the command line.

License:
Gsar is licensed under the GNU General Public License (GPL), Version 2.

We use the unmodified official build of "gsar.exe" as a standalone utility within batch scripts to assist in generating IDE project files (e.g., ".uvprojx" for Keil, ".ewp" for IAR) and to modify settings in ".c"and ".h" source files. It is not linked with, nor integrated into, the source code of the HOLTEK HT32 Firmware Library or HT32 Application Code.

This tool may also be used in scripts to perform automated modifications on source files such as ".c", ".h", and linker script files. These changes are simple text replacements and are part of the build configuration or project generation process.

The use of "gsar.exe" in this manner does **not** cause any portion of the firmware source code to become a derivative work of Gsar, as there is no linking, bundling, or code reuse involved.

A copy of the GNU General Public License is included with this distribution (path: "utilities\gsar\contrib\gsar\1.21\gsar-1.21").

Source Code Availability:
Under the terms of the GPL license, you have the right to access and modify the source code of Gsar. The official source code is available at:

https://gnuwin32.sourceforge.net/packages/gsar.htm
https://sourceforge.net/projects/gnuwin32/files/gsar/1.21/gsar-1.21-bin.zip/download
