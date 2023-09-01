//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#include "assert.h"
#include "time.h"
#include "..\H\SYSTEM\LOGGER.H"

const string LOG_NAME = "TLSA98 Engine Debug File Logger";
const string LOG_FILENAME = "log.txt";
const string LOG_MESSAGE_FORMAT = "[%.24s] %s\n";
const string LOG_SEPARATOR_LINE_SINGLE = "─────────────────────────────────────────────────────────────────────────────────";
const string LOG_SEPARATOR_LINE_DOUBLE = "═════════════════════════════════════════════════════════════════════════════════";
const string LOG_SEPARATOR_LINE_TRIPPLE = "≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡";
const int LOG_MESSAGE_MAX_LENGTH = 255;
const int TIMESTAMP_LENGTH = 28; // "[Fri Sep  1 14:01:10 2023] " <- 28 characters length.

FILE *file;
char messageBuffer[LOG_MESSAGE_MAX_LENGTH - TIMESTAMP_LENGTH];

static string getDateTimeStamp()
{
    time_t curtime;

    time(&curtime);

    return ctime(&curtime);
}

static void writeLogMessageToFile(string formattedMessage)
{
    fprintf(file, LOG_MESSAGE_FORMAT, getDateTimeStamp(), formattedMessage);
}

static void logTripleSeparator()
{
    logMessage(LOG_SEPARATOR_LINE_TRIPPLE);
}

void openLogFile(FILE *(*fopen_f)(char *, char *))
{
    file = fopen_f(LOG_FILENAME, "a");

    logTripleSeparator();
    logMessage("%s session initialized", LOG_NAME);
    logTripleSeparator();
}

void closeLogFile(void (*fclose_f)(FILE *))
{
    logTripleSeparator();
    logMessage("%s session terminated.", LOG_NAME);
    logTripleSeparator();

    fclose_f(file);
}

void logMessage(string message, ...)
{
    va_list args;

    va_start(args, message);
    logMessageArgs(message, args);
    va_end(args);
}

void logMessageArgs(string message, va_list args)
{
    va_list copyArgs;

    va_copy(copyArgs, args);
    vsprintf(messageBuffer, message, copyArgs);
    writeLogMessageToFile(messageBuffer);
}

void logSingleSeparator()
{
    logMessage(LOG_SEPARATOR_LINE_SINGLE);
}

void logDoubleSeparator()
{
    logMessage(LOG_SEPARATOR_LINE_DOUBLE);
}