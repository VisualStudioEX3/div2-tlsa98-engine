//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    File logger.
*/

#include "LOGGER.H"
#include "..\STRING\STRING.H"
#include "..\IO\FILESYS.H"
#include "..\DATETIME\DATETIME.H"

const string ROOT_LOG_FOLDERNAME            = "LOGS";
const int LOG_TODAY_FOLDERNAME_LENGTH       = 8;
const string LOG_TODAY_FOLDERNAME_FORMAT    = "%i%02i%02i"; // Folder name format: "$yyyy$MM$dd".
const int LOG_FILENAME_LENGTH               = 9;
const string LOG_FILENAME_FORMAT            = "%02i%02i%02i.LOG"; // Log filename format: "$HH$mm$ss.LOG"
const string LOG_HEADER_MESSAGE_TEMPLATE    = "Log started on %s";
const string LOG_FOOTER_MESSAGE_TEMPLATE    = "Log finished on %s";
const string LOG_MESSAGE_TEMPLATE           = "[%02i:%02i:%02i] %s\n"; // "[$HH:$mm:$ss] $message"
const string LINE_SEPARATOR                 = "-------------------------------------------------------------------------------";
const int LOG_MESSAGE_MAX_CHARS             = 1024;

FILE* file;
datetime_t* now;
string messageBuffer;

static string checkAndCreateRootLogsFolder(const string appRootFolderPath)
{
    string path = combinePath(2, appRootFolderPath, ROOT_LOG_FOLDERNAME);

    if (!directoryExists(path))
        if (!createDirectory(path))
            ; // TODO: Assert fail.

    return path;
}

static string checkAndCreateTodayFolder(const string rootLogsFolderPath, const datetime_t* today)
{
    string folderName = stringCreate(LOG_TODAY_FOLDERNAME_LENGTH);

    stringFormat(folderName, LOG_TODAY_FOLDERNAME_FORMAT, today->hour, today->minutes, today->seconds);

    string path = combinePath(2, rootLogsFolderPath, folderName);

    if (!directoryExists(path))
        if (!createDirectory(path))
            ; // TODO: Assert fail.

    return path;
}

static void openOrCreateTodayLogFile(const string todayLogsFolderPath, const datetime_t* today)
{
    string filename = stringCreate(LOG_FILENAME_LENGTH);

    stringFormat(filename, LOG_FILENAME_FORMAT, today->hour, today->minutes, today->seconds);

    string path = combinePath(2, todayLogsFolderPath, filename);

    file = openFile(path, "a+");

    if (file == NULL)
        ; // TODO: Assert fail.
}

static void logToFileNoDateTimeMark(const string message, ...)
{
    va_list args;

    va_start(args, message);

    writeStringToFileArgs(file, message, args);

    va_end(args);
}

static void logInitializationMessage(const datetime_t* today)
{
    string timeStamp = dateTimeToString(today);

    logToFileNoDateTimeMark(LOG_HEADER_MESSAGE_TEMPLATE, timeStamp, '\n', LINE_SEPARATOR);
}

static void logTerminationMessage()
{
    getDateTimeNotAlloc(now);

    string timeStamp = dateTimeToString(now);

    logToFileNoDateTimeMark(LOG_FOOTER_MESSAGE_TEMPLATE, LINE_SEPARATOR, '\n', timeStamp);
}

void createLogFile()
{
    now = getDateTime();
    messageBuffer = stringCreate(LOG_MESSAGE_MAX_CHARS);

    string appRootFolderPath = getCurrentDirectory();
    string logsFolderPath = checkAndCreateRootLogsFolder(appRootFolderPath);
    string todayLogFolderPath = checkAndCreateTodayFolder(logsFolderPath, now);

    openOrCreateTodayLogFile(todayLogFolderPath, now);
    logInitializationMessage(now);
}

void closeLogFile()
{
    logTerminationMessage();
    closeFile(file);
    free(messageBuffer);
    free(now);
}

void logToFile(const string message, ...)
{
    va_list args;

    va_start(args, message);
    logToFileArgs(message, args);
    va_end(args);
}

void logToFileArgs(const string message, va_list args)
{
    getDateTimeNotAlloc(now);
    stringClear(messageBuffer);
    stringFormatArgs(messageBuffer, message, args);
    writeStringToFile(file, LOG_MESSAGE_TEMPLATE, now->hour, now->minutes, now->seconds, messageBuffer);
}