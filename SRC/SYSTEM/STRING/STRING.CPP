//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#include <string.h>
#include "..\..\H\STRING.H"

string_service_t* service;

static int len(const string str)
{
    return strlen(str);
}

static bool all(const string str, const char chr)
{
    int i = service->len(str);

    while (--i >= 0 && str[i] == chr);

    return i <= 0;
}

static bool any(const string str, const string chars)
{
    return strpbrk(str, chars) != NULL;
}

static bool isEmpty(const string str)
{
    return str == NULL || service->all(str, '\0');
}

static bool equals(const string lhs, const string rhs)
{
    return strcmp(lhs, rhs) == 0;
}

void registerStringService()
{
    service = (string_service_t*)malloc(sizeof(string_service_t));

    service->len        = len;
    service->all        = all;
    service->any        = any;
    service->isEmpty    = isEmpty;
    service->equals     = equals;

    registerService(STRING_SERVICE, service);
}
