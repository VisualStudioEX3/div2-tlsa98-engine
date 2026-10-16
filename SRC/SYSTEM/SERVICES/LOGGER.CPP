//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    File logger service.
*/

#include <assert.h>
#include "../../H/SYSTEM/LOGGER.H"
#include "../../H/SYSTEM/SERVICES/LOGGER.H"

static const int MAX_LISTENERS = 8;

static file_logger_service_t service;

static void _logMessage(LogLevel level, string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(level, message, args);
    va_end(args);
}

static void _logMessageArgs(LogLevel level, string message, va_list args)
{
    if (logMessageArgs(level, message, args))
    {
        // TODO: Future event notification.
    }
}

static void logDebug(string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(DEBUG, message, args);
    va_end(args);
}

static void logDebugArgs(string message, va_list args)
{
    _logMessageArgs(DEBUG, message, args);
}

static void logInfo(string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(INFO, message, args);
    va_end(args);
}

static void logInfoArgs(string message, va_list args)
{
    _logMessageArgs(INFO, message, args);
}

static void logWarning(string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(WARN, message, args);
    va_end(args);
}

static void logWarningArgs(string message, va_list args)
{
    _logMessageArgs(WARN, message, args);
}

static void logError(string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(ERROR, message, args);
    va_end(args);
}

static void logErrorArgs(string message, va_list args)
{
    _logMessageArgs(ERROR, message, args);
}

static void logCritical(string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(CRITICAL, message, args);
    va_end(args);
}

static void logCriticalArgs(string message, va_list args)
{
    _logMessageArgs(CRITICAL, message, args);
}

static void addListener(log_message_callback listener)
{
    // TODO: Implement array or list to store the function pointers for the listeners.
}

void registerLoggerService()
{
    logMessage(DEBUG, "Initializing file logger service...");

    service.debug = logDebug;
    service.debugArgs = logDebugArgs;
    service.info = logInfo;
    service.infoArgs = logInfoArgs;
    service.warning = logWarning;
    service.warningArgs = logWarningArgs;
    service.error = logError;
    service.errorArgs = logErrorArgs;
    service.critical = logCritical;
    service.criticalArgs = logCriticalArgs;
    service.addListener = addListener;

    int result = engine->services->registerService(LOGGER_SERVICE, &service);

    assert(result == RESULT_OK);

    logMessage(DEBUG, "File logger service initialized.");
}
