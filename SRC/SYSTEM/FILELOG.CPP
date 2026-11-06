//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#include <assert.h>
#include <direct.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "H/DIV2.H"
#include "H/FILELOG.H"

static const int LOG_MESSAGE_MAX_LENGTH = 256;
static const char LOG_MESSAGE_FORMAT[] = "%s | %s | %s\n"; // "2026-10-14 19:28:18 | INFO | Hello, world!"
static const char LOGS_FOLDERNAME[] = "LOGS";
static const size_t LOG_TIMESTAMP_LENGTH = 20; // "2026-10-14 19:28:18"
static const char *LOG_LEVELS[] =
    {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};

static FILE *file;
static char logTimeStamp[LOG_TIMESTAMP_LENGTH];
static char messageBuffer[LOG_MESSAGE_MAX_LENGTH];

// Local macros pointed right to DIV2.H:
#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list));

static struct tm *getLocalDateTime()
{
    const time_t currentTime = time(NULL);
    struct tm *currentDateTime = localtime(&currentTime);

    return currentDateTime;
}

static int checkIfLogFolderExists()
{
    struct stat *buf = (struct stat *)malloc(sizeof(struct stat));

    stat(LOGS_FOLDERNAME, buf);

    const int folderExists = S_ISDIR(buf->st_mode);

    free(buf);

    return folderExists;
}

static void createLogsFolder()
{
    if (!checkIfLogFolderExists())
        assert(mkdir(LOGS_FOLDERNAME) == 0);
}

static char *getFilenameTimeStamp()
{
    // 2026-10-14 -> "20261014":
    const size_t size = sizeof(char) * strlen("20261014") + 1;

    char *timeStamp = (char *)malloc(size);
    struct tm *dateTime = getLocalDateTime();

    strftime(timeStamp, size, "%Y%m%d", dateTime);

    return (char *)timeStamp;
}

static char *getLogFilename()
{
    const size_t size =
        sizeof(char) * strlen("LOGS\\20261014.LOG") + 1;

    char *filename = (char *)malloc(size);
    char *timeStamp = getFilenameTimeStamp();

    sprintf(filename, "%s\\%s.LOG", LOGS_FOLDERNAME, timeStamp);
    free(timeStamp);

    return (char *)filename;
}

static char *getLogTimeStampNotAllocated()
{
    struct tm *dateTime = getLocalDateTime();

    // "2026-10-14 19:28:18":
    strftime(logTimeStamp, LOG_TIMESTAMP_LENGTH, "%Y-%m-%d %H:%M:%S", dateTime);

    return (char *)logTimeStamp;
}

void openLogFile(const char *welcomeMessage)
{
    char *filename = getLogFilename();

    createLogsFolder();
    file = fopen(filename, "a");
    free(filename);
    fprintf(file, "%s\n", welcomeMessage);
}

void closeLogFile(const char *closeMessage)
{
    fprintf(file, "%s\n", closeMessage);
    fclose(file);
}

char *logMessage(const E_LOG_LEVEL level, const char *message, ...)
{
    va_list args;

    va_start(args, message);
    char *result = logMessageArgs(level, message, args);
    va_end(args);

    return result;
}

char *logMessageArgs(const E_LOG_LEVEL level, const char *message, va_list args)
{
    va_list copyArgs;

#ifndef DEBUG
    if (level == LOG_DEBUG)
        return NULL;
#endif

    va_copy(copyArgs, args);
    vsprintf(messageBuffer, message, copyArgs);
    fprintf(file, LOG_MESSAGE_FORMAT,
            getLogTimeStampNotAllocated(), LOG_LEVELS[level], messageBuffer);

    return messageBuffer;
}
