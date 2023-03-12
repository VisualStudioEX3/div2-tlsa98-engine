//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory service.
*/

#include "..\H\SYSTEM\MEM.H"
#include "..\H\SYSTEM\SERVICES.H"
#include "..\MEM\MEM.H"

mem_service_t* service;

void registerMemService()
{
    service = (mem_service_t*)malloc(sizeof(mem_service_t));

    service->clear      = memoryClear;
    service->calloc     = memoryCalloc;
    service->realloc    = memoryRealloc;
    service->copy       = memoryCopy;
    service->copyTo     = memoryCopyTo;
    service->equals     = memoryEquals;

    registerService(MEM_SERVICE, service);
}