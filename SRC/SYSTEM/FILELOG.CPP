//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Basic file logger, full-standalone from the engine services.
*/

#include <assert.h>
#include <direct.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "../H/DIV2.H"
#include "../H/SYSTEM/FILELOG.H"

static const int LOG_MESSAGE_MAX_LENGTH = 256;
static const char LOG_MESSAGE_FORMAT[] = "%s | %s | %s\n"; // "2026-10-14 19:28:18 | INFO | Hello, world!"

static const char LOGS_FOLDERNAME[] = "LOGS";

static const char FILENAME_TIMESTAMP_TEMPLATE[] = "%Y%m%d"; // 2026-10-14 -> "20261014"
static const int FILENAME_TIMESTAMP_LENGTH = strlen("20261014");
static const size_t FILENAME_TIMESTAMP_STRING_SIZE = sizeof(char) * FILENAME_TIMESTAMP_LENGTH;

static const char LOG_FILENAME_TEMPLATE[] = "%s\\%s.LOG"; // "LOGS\20261014.LOG"
static const int LOG_FILENAME_LENGTH = strlen(LOG_FILENAME_TEMPLATE);
static const size_t LOG_FILENAME_STRING_SIZE = sizeof(char) * LOG_FILENAME_LENGTH;

static const char LOG_TIMESTAMP_TEMPLATE[] = "%Y-%m-%d %H:%M:%S"; // "2026-10-14 19:28:18"
static const int LOG_TIMESTAMP_LENGTH = 19;
static const size_t LOG_TIMESTAMP_STRING_SIZE = sizeof(char) * LOG_TIMESTAMP_LENGTH;

static const char *LOG_LEVELS[] = {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};

static FILE *file;
static char timeStamp[LOG_TIMESTAMP_LENGTH];
static char messageBuffer[LOG_MESSAGE_MAX_LENGTH];

#define malloc(size) div_malloc(size)
#define free(ptr) div_free(ptr)
#define fopen(filename, mode) div_fopen(filename, mode)
#define fclose(file) div_fclose(file)
#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list))

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

    int folderExists = S_ISDIR(buf->st_mode);

    free(buf);

    return folderExists;
}

static void createLogsFolder()
{
    if (checkIfLogFolderExists())
        assert(mkdir(LOGS_FOLDERNAME) == 0);
}

static char *getFilenameTimeStamp()
{
    char *timeStamp = (char *)malloc(FILENAME_TIMESTAMP_STRING_SIZE);

    strftime(timeStamp, FILENAME_TIMESTAMP_STRING_SIZE, FILENAME_TIMESTAMP_TEMPLATE, getLocalDateTime());

    return (char *)timeStamp;
}

static char *getLogFilename()
{
    char *filename = (char *)malloc(LOG_FILENAME_STRING_SIZE);

    sprintf(filename, LOG_FILENAME_TEMPLATE, LOGS_FOLDERNAME, getFilenameTimeStamp());

    return (char *)filename;
}

static char *getLogTimeStampNotAllocated()
{
    strftime(timeStamp, LOG_TIMESTAMP_STRING_SIZE, LOG_TIMESTAMP_TEMPLATE, getLocalDateTime());

    return (char *)timeStamp;
}

void openLogFile(const char *welcomeMessage)
{
    createLogsFolder();

    file = fopen(getLogFilename(), "a");

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

#if !DEBUG
    if (level == LOG_DEBUG)
        return NULL;
#endif

    va_copy(copyArgs, args);
    vsprintf(messageBuffer, message, copyArgs);
    fprintf(file, LOG_MESSAGE_FORMAT, getLogTimeStampNotAllocated(), LOG_LEVELS[level], messageBuffer);

    return messageBuffer;
}
