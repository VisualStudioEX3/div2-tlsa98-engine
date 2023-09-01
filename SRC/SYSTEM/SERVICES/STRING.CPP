//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#include <assert.h>
#include <ctype.h>
#include "..\..\H\SYSTEM\SERVICES\STRING.H"
#include "..\..\H\SYSTEM\SERVICES\MEM.H"

string_service_t service;

static mem_service_t *memoryService;

static string stringCreate(int chars)
{
    return (string)memoryService->calloc(++chars); // Add extra char for null terminated char.
}

static string stringResize(string str, int chars)
{
    return (string)memoryService->realloc(str, ++chars, true); // Add extra char for null terminated char.
}

static void stringClear(string str)
{
    memoryService->clear(str, service.length(str));
}

static int stringLength(const string str)
{
    return strlen(str);
}

static bool stringAll(const string str, const char chr)
{
    int i = service.length(str);

    while (--i >= 0 && str[i] == chr)
        ;

    return i <= 0;
}

static bool stringAny(const string str, const string chars)
{
    return strpbrk(str, chars) != NULL;
}

static bool stringIsEmpty(const string str)
{
    return str == NULL || service.all(str, '\0');
}

static bool stringEquals(const string lhs, const string rhs)
{
    return strcmp(lhs, rhs) == 0;
}

// We can't use standard strdup, so we implemented own version.
static string stringCopy(const string str)
{
    int nChars = service.length(str);
    string strCopy = service.create(nChars);

    memoryService->copyTo(str, strCopy, nChars);

    return strCopy;
}

static string stringToCase(const string str, int (*case_f)(int))
{
    string strCopy = service.copy(str);

    for (char *chr = &strCopy[0]; *chr != '\0'; chr++)
        *chr = case_f(*chr);

    return strCopy;
}

static string stringToLowerCase(const string str)
{
    return stringToCase(str, tolower);
}

static string stringToUpperCase(const string str)
{
    return stringToCase(str, toupper);
}

static bool stringFormat(string str, const string format, ...)
{
    va_list args;

    va_start(args, format);

    bool ret = service.formatArgs(str, format, args);

    va_end(args);

    return ret;
}

static bool stringFormatArgs(string str, const string format, va_list args)
{
    va_list copyArgs;

    va_copy(copyArgs, args);

    return vsprintf(str, format, copyArgs) > 0;
}

static string stringJoin(const string separator, int count, ...)
{
    va_list args;

    va_start(args, count);

    string str = service.joinArgs(separator, count, args);

    va_end(args);

    return str;
}

static int stringGetTotalCharsFromArgumentList(int count, va_list args)
{
    int chars = 0;
    va_list copyArgs;
    string arg;

    va_copy(copyArgs, args);

    for (int i = 0; i < count; i++)
    {
        arg = va_arg(copyArgs, string);
        chars += service.length(arg);
    }

    return chars;
}

static string stringJoinArgs(const string separator, int count, va_list args)
{
    va_list copyArgs;

    va_copy(copyArgs, args);

    int strChars = stringGetTotalCharsFromArgumentList(count, copyArgs);
    string str = service.create(strChars);

    for (int i = 0; i < count; i++)
    {
        string arg = va_arg(copyArgs, string);

        if (i > 0)
            strcat(str, separator);

        strcat(str, arg);
    }

    return str;
}

void registerStringService()
{
    engine->fileLogger->log("Initializing String service...");

    memoryService = (mem_service_t *)getService(MEM_SERVICE);

    service.create = stringCreate;
    service.resize = stringResize;
    service.clear = stringClear;
    service.length = stringLength;
    service.all = stringAll;
    service.any = stringAny;
    service.isEmpty = stringIsEmpty;
    service.equals = stringEquals;
    service.copy = stringCopy;
    service.toLower = stringToLowerCase;
    service.toUpper = stringToUpperCase;
    service.format = stringFormat;
    service.formatArgs = stringFormatArgs;
    service.join = stringJoin;
    service.joinArgs = stringJoinArgs;

    int result = engine->services->registerService(STRING_SERVICE, &service);

    assert(result == RESULT_OK);

    engine->fileLogger->log("String service initialized.");
}
