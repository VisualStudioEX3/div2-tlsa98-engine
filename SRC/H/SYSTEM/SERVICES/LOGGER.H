//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    File logger service.
*/

#ifndef __SYSTEM_DLL_LOGGER_SERVICE_H_
#define __SYSTEM_DLL_LOGGER_SERVICE_H_

#include "../GLOBALS.H"

/// @brief DateTime service id.
#define LOGGER_SERVICE 1003

/// @brief Callback predicate to define an event listener to get notifications when
/// a message was logged.
/// @param level Log level.
/// @param message Log message.
typedef void (*log_message_callback)(LogLevel, string);

typedef void (*file_logger_log_message)(string, ...);
typedef void (*file_logger_log_message_args)(string, va_list);
typedef void (*file_logger_add_listener)(log_message_callback);

/// @brief File logger.
/// @remarks This file logger is a basic and standalone logger service to use for
/// low-level debug purposes and for log runtime events.
typedef struct
{
    /// @brief Logs a debug message.
    /// @param message Message to log.
    /// @param ... Optional values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | DEBUG | Hello, world!"
    /// The message only log if the DEBUG preprocessor is defined.
    file_logger_log_message debug;

    /// @brief Logs a debug message (Variadic).
    /// @param message Message to log.
    /// @param args Values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | DEBUG | Hello, world!"
    /// The message only log if the DEBUG preprocessor is defined.
    file_logger_log_message_args debugArgs;

    /// @brief Logs an information message.
    /// @param message Message to log.
    /// @param ... Optional values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | INFO | Hello, world!"
    file_logger_log_message info;

    /// @brief Logs an information message (Variadic).
    /// @param message Message to log.
    /// @param args Values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | INFO | Hello, world!"
    file_logger_log_message_args infoArgs;

    /// @brief Logs a warning message.
    /// @param message Message to log.
    /// @param ... Optional values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | WARN | Hello, world!"
    file_logger_log_message warning;

    /// @brief Logs a warning message (Variadic).
    /// @param message Message to log.
    /// @param args Values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | WARN | Hello, world!"
    file_logger_log_message_args warningArgs;

    /// @brief Logs an error message.
    /// @param message Message to log.
    /// @param ... Optional values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | ERROR | Hello, world!"
    file_logger_log_message error;

    /// @brief Logs an error message (Variadic).
    /// @param message Message to log.
    /// @param args Values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | ERROR | Hello, world!"
    file_logger_log_message_args errorArgs;

    /// @brief Logs a critical error message.
    /// @param message Message to log.
    /// @param ... Optional values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | CRITICAL | Hello, world!"
    file_logger_log_message critical;

    /// @brief Logs a critical error message (Variadic).
    /// @param message Message to log.
    /// @param args Values to formatted into mesaage.
    /// @remarks The logged message contains a date time stamp at the start of line
    /// followed by the log level tag like as follow:
    /// "2026-10-14 19:28:18 | CRITICAL | Hello, world!"
    file_logger_log_message_args criticalArgs;

    /// @brief Add event listener.
    /// @param listener Pointer function to the event listener.
    /// @remarks Use this method to register listeners for when a message was logged.
    file_logger_add_listener addListener;
} file_logger_service_t;

/// @brief Register and initializes the service.
void registerLoggerService();

#endif
