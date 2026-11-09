//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Logger service.
*/

#include "../H/SERVICES/LOGGER.H"

typedef struct
{
    logger_log_message_f debug;
    logger_log_message_args_f debugArgs;
    logger_log_message_f info;
    logger_log_message_args_f infoArgs;
    logger_log_message_f warning;
    logger_log_message_args_f warningArgs;
    logger_log_message_f error;
    logger_log_message_args_f errorArgs;
    logger_log_message_f critical;
    logger_log_message_args_f criticalArgs;
    logger_add_listener_f addListener;
} _logger_service_t;

static _logger_service_t service;

static void _logMessageArgs(const E_LOG_LEVEL level, const string message, va_list args)
{
    const string formattedMessage = logMessageArgs(level, message, args);

    if (formattedMessage)
    {
        // TODO: Future event notification.
    }
}

static void _logMessage(const E_LOG_LEVEL level, const string message, ...)
{
    va_list args;

    va_start(args, message);
    _logMessageArgs(level, message, args);
    va_end(args);
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

static void addListener(const logger_message_callback_f listener)
{
    // TODO: Implement array or list to store the function pointers for the listeners.
}

void registerLoggerService()
{
    logMessage(LOG_DEBUG, "Initializing logger service...");

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

    assert(addService(LOGGER_SERVICE, &service));

    logMessage(LOG_DEBUG, "Logger service initialized.");
}
