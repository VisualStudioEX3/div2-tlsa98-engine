//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String functions.
*/

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "STRING.H"
#include "..\MEM\MEM.H"

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

static string stringToCase(const string str, int (*case_f)(int))
{
    string strCopy = stringCopy(str);

    for (string chr = strCopy; chr != '\0'; chr++)
        *chr = case_f(*chr);

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

    bool ret = sprintf(str, format, args) > 0;

    va_end(args);

    return ret;
}

string stringJoin(const string separator, int count, ...)
{
    const int SEPARATOR_LENGTH = stringLength(separator);

    va_list args;
    string str;
    int strChars;
    string arg;
    int argChars;

    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        va_arg(arg, string);
        argChars = stringLength(arg);

        if (i == 0)
            str = stringCreate(argChars);
        else
        {
            strChars = stringLength(str) + SEPARATOR_LENGTH + argChars;
            str = stringResize(str, strChars);
            strcat(str, separator);
        }

        strcat(str, arg);
    }

    va_end(args);

    return str;
}