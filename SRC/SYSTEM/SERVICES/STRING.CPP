//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#include <ctype.h>
#include <string.h>
#include "..\H\GLOBAL.H"
#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\SYSTEM\MEM.H"
#include "..\H\SYSTEM\STRING.H"

string_service_t* service;
mem_service_t* memService;

static string strAlloc(int chars)
{
    return (string)memService->calloc(++chars); // Add extra char for null terminated char.
}

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

// We can't use standard strdup, so we implemented own version.
static string copy(const string str)
{
    int nChars = service->len(str);
    string strCopy = service->strAlloc(nChars);

    memService->copyTo(str, strCopy, nChars);

    return strCopy;
}

static string toCase(const string str, int (*case_f)(int))
{
    string strCopy = service->copy(str);

    for (char* chr = strCopy; chr != '\0'; chr++)
        *chr = case_f(*chr);

    return strCopy;
}

static string toLowerS(const string str)
{
    return toCase(str, tolower);
}

static string toUpperS(const string str)
{
    return toCase(str, toupper);
}

static void createService()
{
    service = (string_service_t*)malloc(sizeof(string_service_t));

    service->strAlloc   = strAlloc;
    service->len        = len;
    service->all        = all;
    service->any        = any;
    service->isEmpty    = isEmpty;
    service->equals     = equals;
    service->copy       = copy;
    service->toLower    = toLowerS;
    service->toUpper    = toUpperS;

    registerService(STRING_SERVICE, service);
}

void registerStringService()
{
    memService = (mem_service_t*)getService(MEM_SERVICE);

    createService();
}
