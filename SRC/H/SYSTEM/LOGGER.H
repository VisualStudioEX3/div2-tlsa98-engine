//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#ifndef __SYSTEM_DLL_LOGGER_H_
#define __SYSTEM_DLL_LOGGER_H_

#include "GLOBALS.H"

/// @brief Opens or creates the log file.
/// @param fopen_f Pointer to fopen function (must be point to DIV2.H div_fopen).
/// @remarks The files is opened in append mode.
void openLogFile(FILE *(*fopen_f)(char *, char *));

/// @brief Closes the log file.
/// @param fclose_f Pointer to fclose function (must be point to DIV2.H div_fclose).
void closeLogFile(void (*fclose_f)(FILE *));

/// @brief Logs a formatted message.
/// @param message Message to log.
/// @param ... Optional values to formatted into mesaage.
/// @remarks The logged message contains a date time stamp at the start of line.
void logMessage(string message, ...);

/// @brief Logs a formatted message (Variadic).
/// @param message Message to log.
/// @param args Values to formatted into mesaage.
/// @remarks The logged message contains a date time stamp at the start of line.
void logMessageArgs(string message, va_list args);

/// @brief Logs a single line separator.
void logSingleSeparator();

/// @brief Logs a double line separator.
void logDoubleSeparator();

#endif