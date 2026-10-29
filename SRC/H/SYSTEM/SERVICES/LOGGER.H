//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Logger service.
*/

#ifndef __SYSTEM_DLL_LOGGER_SERVICE_H_
#define __SYSTEM_DLL_LOGGER_SERVICE_H_

#include "../GLOBALS.H"
#include "../FILELOG.H"

/// @brief Logger service id.
#define LOGGER_SERVICE 1003

/**
 * @brief Callback predicate to define an event listener to get notifications
 * when a message was logged.
 * @param level Log level.
 * @param message Log message.
 */
typedef void (*logger_message_callback_f)(const E_LOG_LEVEL, const string);

typedef void (*logger_log_message_f)(const string, ...);
typedef void (*logger_log_message_args_f)(const string, va_list);
typedef void (*logger_add_listener_f)(const logger_message_callback_f);

/**
 * @brief Logger service.
 * @remarks This service allow to log events in a file, created with the date as
 * name under game root "LOGS" folder("LOGS\20261014.LOG").
 *
 * The service allows to notified log events by function callback listeners. This
 * allow to extend the logger to other features, like a debug console.
 */
typedef struct
{
    /**
     * @brief Logs a debug message.
     * @param message Message to log.
     * @param ... Optional values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | DEBUG | Hello, world!"
     * The message only log if the DEBUG preprocessor is defined.
     */
    logger_log_message_f debug;

    /**
     * @brief Logs a debug message (Variadic).
     * @param message Message to log.
     * @param args Values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | DEBUG | Hello, world!"
     * The message only log if the DEBUG preprocessor is defined.
     */
    logger_log_message_args_f debugArgs;

    /**
     * @brief Logs an information message.
     * @param message Message to log.
     * @param ... Optional values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | INFO | Hello, world!"
     */
    logger_log_message_f info;

    /**
     * @brief Logs an information message (Variadic).
     * @param message Message to log.
     * @param args Values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | INFO | Hello, world!"
     */
    logger_log_message_args_f infoArgs;

    /**
     * @brief Logs a warning message.
     * @param message Message to log.
     * @param ... Optional values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | WARN | Hello, world!"
     */
    logger_log_message_f warning;

    /**
     * @brief Logs a warning message (Variadic).
     * @param message Message to log.
     * @param args Values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | WARN | Hello, world!"
     */
    logger_log_message_args_f warningArgs;

    /**
     * @brief Logs an error message.
     * @param message Message to log.
     * @param ... Optional values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | ERROR | Hello, world!"
     */
    logger_log_message_f error;

    /**
     * @brief Logs an error message (Variadic).
     * @param message Message to log.
     * @param args Values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | ERROR | Hello, world!"
     */
    logger_log_message_args_f errorArgs;

    /**
     * @brief Logs a critical error message.
     * @param message Message to log.
     * @param ... Optional values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | CRITICAL | Hello, world!"
     */
    logger_log_message_f critical;

    /**
     * @brief Logs a critical error message (Variadic).
     * @param message Message to log.
     * @param args Values to formatted into mesaage.
     * @remarks The logged message contains a date time stamp at the start of line
     * followed by the log level tag like as follow:
     * "2026-10-14 19:28:18 | CRITICAL | Hello, world!"
     */
    logger_log_message_args_f criticalArgs;

    /**
     * @brief Add event listener.
     * @param listener Pointer function to the event listener.
     * @remarks Use this method to register callback listeners for when a message
     * was logged.
     */
    logger_add_listener_f addListener;
} logger_service_t;

/// @brief Register and initializes the service.
void registerLoggerService();

#endif
