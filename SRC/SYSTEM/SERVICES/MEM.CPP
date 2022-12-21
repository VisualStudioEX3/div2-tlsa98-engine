//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory service.
*/

#include <string.h>
#include "..\H\SYSTEM\DIV2.H"
#include "..\H\SYSTEM\GLOBAL.H"
#include "..\H\SYSTEM\MEM.H"
#include "..\H\SYSTEM\SERVICES.H"

mem_service_t* service;

static void clear(void* ptr, size_t size)
{
    memset(ptr, NULL, size);
}

// We can't use standard calloc, so we implemented own version.
static void* div_calloc(size_t size)
{
    void* ptr = malloc(size);

    service->clear(ptr, size);

    return ptr;
}

static void* copy(const void* ptr, size_t size)
{
    void* copyPtr = malloc(size);

    service->copyTo(ptr, copyPtr, size);

    return copyPtr;
}

static void copyTo(const void* from, void* to, size_t size)
{
    memmove(to, from, size);
}

static bool equals(const void* ptr1, const void* ptr2, size_t size)
{
    return memcmp(ptr1, ptr2, size) == 0;
}

void registerMemService()
{
    service = (mem_service_t*)malloc(sizeof(mem_service_t));

    service->clear  = clear;
    service->calloc = div_calloc;
    service->copy   = copy;
    service->copyTo = copyTo;
    service->equals = equals;

    registerService(MEM_SERVICE, service);
}