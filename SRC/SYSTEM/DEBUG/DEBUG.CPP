//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Debug functions.
*/

#include <dos.h>
#include "LOGGER.H"
#include "DEBUG.H"

#ifdef DOSBOX_SUPPORT
    // DOS Delay function / BIOS interruption 15h seems not working on DOSBox emulator:
    // https://stackoverflow.com/questions/43194265/dosbox-is-buggy-with-int-15h-ah-86h/66845163#66845163

    #include "..\DATETIME\DATETIME.H"

    // TODO: Try to find another way to implement this in assembler.
    #define delay(milliseconds) \
        ulong targetTime = getTickCount() + milliseconds; \
        while (getTickCount() < targetTime) { }
#endif

void initializeDebugSystem()
{
    createLogFile();
}

void terminateDebugSystem()
{
    closeLogFile();
}

void beep()
{
    sound(800);
    delay(200);
    nosound();
}

void log(string message, ...)
{
    va_list args;

    va_start(args, message);
    logArgs(message, args);
    va_end(args);
}

void logArgs(string message, va_list args)
{
    logToFileArgs(message, args);
}

void print(string message, ...)
{
    va_list args;

    va_start(args, message);
    printArgs(message, args);
    va_end(args);
}

void printArgs(string message, va_list args)
{
    // TODO: Implement print console.
}

void cls()
{
    // TODO: Implement print console.
}