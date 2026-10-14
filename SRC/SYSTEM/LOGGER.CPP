//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "../H/DIV2.H"
#include "../H/SYSTEM/LOGGER.H"

static const int LOG_MESSAGE_MAX_LENGTH = 256;
static const char *LOG_MESSAGE_FORMAT = "%s | %s | %s\n";      // "2026-10-14 19:28:18 | INFO | Hello, world!"
static const char *FILENAME_TIMESTAMP_TEMPLATE = "%Y%m%d.log"; // "20261014.log"
static const int FILENAME_TIMESTAMP_LENGTH = 12;               // 8:3 MS-DOS filename format.
static const size_t FILENAME_TIMESTAMP_STRING_SIZE = sizeof(char) * FILENAME_TIMESTAMP_LENGTH;
static const char *LOG_TIMESTAMP_TEMPLATE = "%Y-%m-%d %H:%M:%S"; // "2026-10-14 19:28:18"
static const int LOG_TIMESTAMP_LENGTH = strlen("2026-10-14 19:28:18");
static const size_t LOG_TIMESTAMP_STRING_SIZE = sizeof(char) * LOG_TIMESTAMP_LENGTH;
static const char const *LOG_LEVELS[] = {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};

static FILE *file;
static char messageBuffer[LOG_MESSAGE_MAX_LENGTH];

#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list));

static tm *getLocalDateTime()
{
    time_t currentTime = time(NULL);
    struct tm *currentDateTime = localtime(&currentTime);

    return currentDateTime;
}

static char *getFilenameTimeStamp()
{
    char *filename = (char *)div_malloc(FILENAME_TIMESTAMP_STRING_SIZE);

    strftime(filename, FILENAME_TIMESTAMP_STRING_SIZE, FILENAME_TIMESTAMP_TEMPLATE, getLocalDateTime());

    return (char *)filename;
}

static char *getLogTimeStamp()
{
    char *timestamp = (char *)div_malloc(LOG_TIMESTAMP_STRING_SIZE);

    strftime(timestamp, LOG_TIMESTAMP_STRING_SIZE, LOG_TIMESTAMP_TEMPLATE, getLocalDateTime());

    return (char *)timestamp;
}

void openLogFile(char *welcomeMessage)
{
    file = div_fopen(getFilenameTimeStamp(), "a");

    fprintf(file, welcomeMessage);
}

void closeLogFile(char *closeMessage)
{
    fprintf(file, "%s\n", closeMessage);
    div_fclose(file);
}

int logMessage(LogLevel level, char *message, ...)
{
    va_list args;

    va_start(args, message);
    int result = logMessageArgs(level, message, args);
    va_end(args);

    return result;
}

int logMessageArgs(LogLevel level, char *message, va_list args)
{
#if !DEBUG
    if (level == DEBUG)
        return 0;
#endif

    va_list copyArgs;

    va_copy(copyArgs, args);
    vsprintf(messageBuffer, message, copyArgs);
    fprintf(file, LOG_MESSAGE_FORMAT, getLogTimeStamp(), LOG_LEVELS[level], messageBuffer);

    return 1;
}
