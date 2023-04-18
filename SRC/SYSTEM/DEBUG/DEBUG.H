//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Debug functions.
*/

#ifndef __SYSTEM_DEBUG_H_
#define __SYSTEM_DEBUG_H_

#include "..\..\H\SYSTEM.H"

/// @brief Initializes all debug subsystems.
void initializeDebugSystem();

/// @brief Terminates all debug subsystems.
void terminateDebugSystem();

/// @brief Plays a standard CPU beep sound.
/// @remarks This function play a sound with 800hz frequency and 200 milliseconds 
/// duration. This function locks the program until the sound is finished.
void beep();

/// @brief Logs a message.
/// @param message Message to log.
/// @param ... Optional list of arguments to format in the string. To see how to format the 
/// output see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks The log message was formatted as follow: [$date-$time]: $message
void log(string message, ...);

/// @brief Logs a message (Variadic version).
/// @param message Message to log.
/// @param args List of arguments to format in the string. To see how to format the output 
/// see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks The log message was formatted as follow: [$date-$time]: $message
void logArgs(string message, va_list args);

/// @brief Prints a message in screen over the top render.
/// @param message Message to print.
/// @param ... Optional list of arguments to format in the string. To see how to format the 
/// output see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks This function works like the PRINT instruction in BASIC language interpreters.
void print(string message, ...);

/// @brief Prints a message in screen over the top render (Variadic version).
/// @param message Message to log.
/// @param args List of arguments to format in the string. To see how to format the output 
/// see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks This function works like the PRINT instruction in BASIC language interpreters.
void printArgs(string message, va_list args);

/// @brief Clear printed messages in screen.
void cls();

#endif