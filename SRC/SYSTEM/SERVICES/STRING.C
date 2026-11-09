//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#include <ctype.h>
#include "../H/SERVICES/LOGGER.H"
#include "../H/SERVICES/MEM.H"
#include "../H/SERVICES/STRING.H"

typedef struct
{
    string_create_f create;
    string_resize_f resize;
    string_clear_f clear;
    string_len_f length;
    string_all_f all;
    string_any_f any;
    string_empty_f isEmpty;
    string_equals_f equals;
    string_copy_f copy;
    string_to_lower_f toLower;
    string_to_upper_f toUpper;
    string_format_f format;
    string_format_args_f formatArgs;
    string_join_f join;
    string_join_args_f joinArgs;
} _string_service_t;

static const mem_service_t *memoryService;
static const logger_service_t *logger;

static _string_service_t service;

static string stringCreate(const int chars)
{
    // Add extra char for null terminated char:
    return (string)memoryService->clearAllocate(chars + 1);
}

static string stringResize(string str, const int chars)
{
    // Add extra char for null terminated char:
    return (string)memoryService->reAllocate(str, chars + 1, true);
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
    char *chr;

    for (chr = &strCopy[0]; *chr != '\0'; chr++)
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
    bool ret;
    va_list args;

    va_start(args, format);
    ret = service.formatArgs(str, format, args);
    va_end(args);

    return ret;
}

static bool stringFormatArgs(string str, const string format, va_list args)
{
    va_list copyArgs;

    va_copy(copyArgs, args);

    return vsprintf(str, format, copyArgs) > 0;
}

static string stringJoin(const string separator, const int count, ...)
{
    string ret;
    va_list args;

    va_start(args, count);
    ret = service.joinArgs(separator, count, args);
    va_end(args);

    return ret;
}

static int stringGetTotalCharsFromArgumentList(const int count, va_list args)
{
    int chars = 0;
    va_list copyArgs;
    string arg;
    int i;

    va_copy(copyArgs, args);

    for (i = 0; i < count; i++)
    {
        arg = va_arg(copyArgs, string);
        chars += service.length(arg);
    }

    return chars;
}

static string stringJoinArgs(const string separator, const int count, va_list args)
{
    va_list copyArgs;
    string str, arg;
    int strChars, i;

    va_copy(copyArgs, args);

    strChars = stringGetTotalCharsFromArgumentList(count, copyArgs);
    str = service.create(strChars);

    for (i = 0; i < count; i++)
    {
        arg = va_arg(copyArgs, string);

        if (i > 0)
            strcat(str, separator);

        strcat(str, arg);
    }

    return str;
}

void registerStringService()
{
    logger = (logger_service_t *)getService(LOGGER_SERVICE);
    memoryService = (mem_service_t *)getService(MEM_SERVICE);

    logger->debug("Initializing String service...");

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

    assert(addService(STRING_SERVICE, &service));

    logger->debug("String service initialized.");
}
