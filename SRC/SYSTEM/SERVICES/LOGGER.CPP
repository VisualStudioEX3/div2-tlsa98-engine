//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    File logger service.
*/

#include <assert.h>
#include "../../H/SYSTEM/LOGGER.H"
#include "../../H/SYSTEM/SERVICES/LOGGER.H"

static file_logger_service_t service;

static void _logMessage(LogLevel level, const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(level, message, args);
    va_end(args);
}

static void _logMessageArgs(LogLevel level, const string message, va_list args)
{
    string message = logMessageArgs(level, message, args);

    if (message)
    {
        // TODO: Future event notification.
    }
}

static void logDebug(const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(LOG_DEBUG, message, args);
    va_end(args);
}

static void logDebugArgs(const string message, va_list args)
{
    _logMessageArgs(LOG_DEBUG, message, args);
}

static void logInfo(const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(LOG_INFO, message, args);
    va_end(args);
}

static void logInfoArgs(const string message, va_list args)
{
    _logMessageArgs(LOG_INFO, message, args);
}

static void logWarning(const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(LOG_WARN, message, args);
    va_end(args);
}

static void logWarningArgs(const string message, va_list args)
{
    _logMessageArgs(LOG_WARN, message, args);
}

static void logError(const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(LOG_ERROR, message, args);
    va_end(args);
}

static void logErrorArgs(const string message, va_list args)
{
    _logMessageArgs(LOG_ERROR, message, args);
}

static void logCritical(const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(LOG_CRITICAL, message, args);
    va_end(args);
}

static void logCriticalArgs(const string message, va_list args)
{
    _logMessageArgs(LOG_CRITICAL, message, args);
}

static void addListener(const log_message_callback listener)
{
    // TODO: Implement array or list to store the function pointers for the listeners.
}

void registerLoggerService()
{
    logMessage(LOG_DEBUG, "Initializing file logger service...");

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

    logMessage(LOG_DEBUG, "File logger service initialized.");
}
