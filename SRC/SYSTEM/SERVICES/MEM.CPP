//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory service.
*/

#include <assert.h>
#include "..\..\H\SYSTEM\SERVICES\MEM.H"

mem_service_t service;

static void memoryClear(void *ptr, size_t size)
{
    memset(ptr, NULL, size);
}

// We can't use standard calloc, so we implemented own version.
static void *memoryCalloc(size_t size)
{
    void *ptr = malloc(size);

    service.clear(ptr, size);

    return ptr;
}

static void *memoryRealloc(void *ptr, size_t size, bool useCalloc)
{
    void *newPtr = useCalloc
                       ? service.calloc(size)
                       : malloc(size);

    service.copyTo(ptr, newPtr, size);
    free(ptr);

    return newPtr;
}

static void *memoryCopy(const void *ptr, size_t size)
{
    void *copyPtr = malloc(size);

    service.copyTo(ptr, copyPtr, size);

    return copyPtr;
}

static void memoryCopyTo(const void *from, void *to, size_t size)
{
    memmove(to, from, size);
}

static bool memoryEquals(const void *ptr1, const void *ptr2, size_t size)
{
    return memcmp(ptr1, ptr2, size) == 0;
}

void registerMemService()
{
    service.clear = memoryClear;
    service.calloc = memoryCalloc;
    service.realloc = memoryRealloc;
    service.copy = memoryCopy;
    service.copyTo = memoryCopyTo;
    service.equals = memoryEquals;

    int result = engine->services->registerService(MEM_SERVICE, &service);

    assert(result == RESULT_OK);
}