//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    File logger.
*/

#ifndef __SYSTEM_DEBUG_LOGGER_H_
#define __SYSTEM_DEBUG_LOGGER_H_

#include "..\..\H\SYSTEM.H"

/// @brief Creates the log file.
/// @remarks This function also create, if not exists, the logs root folder, the today folder,
/// if not exists, with date as name ($yyyy$MM$dd), and the log file with creation time as name
/// ($HH$mm$ss.log).
void createLogFile();

/// @brief Closes the log file.
/// @remarks Before closes the file, writes a termination message to log file, as confirmation
/// of expected termination.
void closeLogFile();

/// @brief Logs a message to log file.
/// @param message Message to log.
/// @param ... Optional list of arguments to format in the string. To see how to format the 
/// output see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks The message is formatted as follow: [$HH:$mm:$ss]: $message
void logToFile(const string message, ...);

/// @brief Logs a message to log file (Variadic version).
/// @param message Message to log.
/// @param args List of arguments to format in the string. To see how to format the output 
/// see: https://cplusplus.com/reference/cstdio/printf/.
/// @remarks The message is formatted as follow: [$HH:$mm:$ss]: $message
void logToFileArgs(const string message, va_list args);

#endif