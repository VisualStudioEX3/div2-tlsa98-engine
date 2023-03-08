//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    String service.
*/

#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\SYSTEM\STRING.H"
#include "..\STRING\STRING.H"

string_service_t* service;

void registerStringService()
{
    service = (string_service_t*)malloc(sizeof(string_service_t));

    service->strAlloc   = stringAlloc;
    service->len        = stringLength;
    service->all        = stringAll;
    service->any        = stringAny;
    service->isEmpty    = stringIsEmpty;
    service->equals     = stringEquals;
    service->copy       = stringCopy;
    service->toLower    = stringToLowerCase;
    service->toUpper    = stringToUpperCase;

    registerService(STRING_SERVICE, service);
}
