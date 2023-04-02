//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String functions.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "STRING.H"
#include "..\MEM\MEM.H"

static string stringToCase(const string str, int (*case_f)(int))
{
    string strCopy = stringCopy(str);

    for (char* chr = &strCopy[0]; *chr != '\0'; chr++)
        *chr = case_f(*chr);

    return strCopy;
}

static int stringGetTotalCharsFromArgumentList(int count, va_list args)
{
    int chars = 0;
    string arg;

    for (int i = 0; i < count; i++)
    {
        arg = va_arg(args, string);
        chars += stringLength(arg);
    }

    return chars;
}

string stringCreate(int chars)
{
    return (string)memoryCalloc(++chars); // Add extra char for null terminated char.
}

string stringResize(string str, int chars)
{
    return (string)memoryRealloc(str, ++chars, true); // Add extra char for null terminated char.
}

int stringLength(const string str)
{
    return strlen(str);
}

bool stringAll(const string str, const char chr)
{
    int i = stringLength(str);

    while (--i >= 0 && str[i] == chr);

    return i <= 0;
}

bool stringAny(const string str, const string chars)
{
    return strpbrk(str, chars) != NULL;
}

bool stringIsEmpty(const string str)
{
    return str == NULL || stringAll(str, '\0');
}

bool stringEquals(const string lhs, const string rhs)
{
    return strcmp(lhs, rhs) == 0;
}

// We can't use standard strdup, so we implemented own version.
string stringCopy(const string str)
{
    int nChars = stringLength(str);
    string strCopy = stringCreate(nChars);

    memoryCopyTo(str, strCopy, nChars);

    return strCopy;
}

string stringToLowerCase(const string str)
{
    return stringToCase(str, tolower);
}

string stringToUpperCase(const string str)
{
    return stringToCase(str, toupper);
}

bool stringFormat(string str, const string format, ...)
{
    va_list args;

    va_start(args, format);

    bool ret = stringFormatArgs(str, format, args);

    va_end(args);

    return ret;
}

bool stringFormatArgs(string str, const string format, va_list args)
{
    return vsprintf(str, format, args) > 0;
}

string stringJoin(const string separator, int count, ...)
{
    va_list args;

    va_start(args, count);

    string str = stringJoinArgs(separator, count, args);

    va_end(args);

    return str;
}

string stringJoinArgs(const string separator, int count, va_list args)
{
    va_list copyArgs;

    va_copy(copyArgs, args);

    int strChars = stringGetTotalCharsFromArgumentList(count, copyArgs);
    string str = stringCreate(strChars);

    for (int i = 0; i < count; i++)
    {
        string arg = va_arg(args, string);

        if (i > 0)
            strcat(str, separator);

        strcat(str, arg);
    }

    return str;
}