//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#ifndef __SYSTEM_DLL_LOGGER_H_
#define __SYSTEM_DLL_LOGGER_H_

/// @brief Log levels.
typedef enum E_LOG_LEVEL
{
    /// @brief Debug log level.
    /// @remarks This level only log if DEBUG preprocessor is defined.
    LOG_DEBUG,
    /// @brief Information log level.
    LOG_INFO,
    /// @brief Warning log level.
    LOG_WARN,
    /// @brief Error log level.
    LOG_ERROR,
    /// @brief Critical error log level.
    LOG_CRITICAL
};

/// @brief Opens or creates the log file.
/// @param welcomeMessage First message logged in the session. Neither the log
/// level nor the timestamp is included.
/// @remarks The file is opened in append mode.
void openLogFile(const char *welcomeMessage);

/// @brief Closes the log file.
/// @param closeMessage Last message logged in the session. Neither the log
/// level nor the timestamp is included.
void closeLogFile(const char *closeMessage);

/// @brief Logs a formatted message.
/// @param level Debug level.
/// @param message Message to log.
/// @param ... Optional values to formatted into mesaage.
/// @returns Returns the formatted message, if was logged, NULL otherwise.
/// @remarks The logged message contains a date time stamp at the start of line
/// followed by the log level tag like as follow:
/// "2026-10-14 19:28:18 | INFO | Hello, world!"
char *logMessage(const E_LOG_LEVEL level, const char *message, ...);

/// @brief Logs a formatted message (Variadic).
/// @param level Debug level.
/// @param message Message to log.
/// @param args Values to formatted into mesaage.
/// @returns Returns the formatted message, if was logged, NULL otherwise.
/// @remarks The logged message contains a date time stamp at the start of line
/// followed by the log level tag like as follow:
/// "2026-10-14 19:28:18 | INFO | Hello, world!"
char *logMessageArgs(const E_LOG_LEVEL level, const char *message, va_list args);

#endif
