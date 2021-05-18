##CM7_CRT0

A basic CRT0 like bootstrap implementation targeting Cortex-M7

The startup code basicall does:
  - Initialize the system clock
  - Initialize ZI regions and copy rwdata sections to RAM.
  - Call the user main()


###HOWTO
For demonstration purpose, an example application is supplied. It targets the STM32H723 MCU (Board NUCLEO-H723ZG)
The application, led_blinker, can be compiled without any specific library or dependencies.
You only need **GCC** and **make**. To build the application, cd to gcc folder and execute the make command.
Application building will result in two binary files (ELF and raw BIN), use one of them to flash it (STM32CubeProgrammer) into target starting at address 0x80000000.

###NOTES
The system clock is drived directly from HSI (64MHz, no PLL)