//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory service.
*/

#include <assert.h>
#include "../../H/SYSTEM/SERVICES/LOGGER.H"
#include "../../H/SYSTEM/SERVICES/MEM.H"

typedef struct
{
    mem_clear_f clear;
    mem_calloc_f clearAllocate;
    mem_realloc_f reAllocate;
    mem_copy_f copy;
    mem_copy_to_f copyTo;
    mem_equals_f equals;
} _mem_service_t;

static _mem_service_t service;
static logger_service_t *logger;

static void memoryClear(void *ptr, const size_t size)
{
    memset(ptr, NULL, size);
}

// We can't use standard calloc, so we implemented own version.
static void *memoryCalloc(const size_t size)
{
    void *ptr = malloc(size);

    service.clear(ptr, size);

    return ptr;
}

// We can't use standard realloc, so we implemented own version.
static void *memoryRealloc(void *ptr, const size_t size, const bool clearMemory)
{
    void *newPtr = clearMemory
                       ? service.clearAllocate(size)
                       : malloc(size);

    service.copyTo(ptr, newPtr, size);
    free(ptr);

    return newPtr;
}

static void *memoryCopy(const void *ptr, const size_t size)
{
    void *copyPtr = malloc(size);

    service.copyTo(ptr, copyPtr, size);

    return copyPtr;
}

static void memoryCopyTo(const void *from, void *to, const size_t size)
{
    memmove(to, from, size);
}

static bool memoryEquals(const void *ptr1, const void *ptr2, const size_t size)
{
    return memcmp(ptr1, ptr2, size) == 0;
}

void registerMemService()
{
    logger = (logger_service_t *)getService(LOGGER_SERVICE);

    logger->debug("Initializing Memory service...");

    service.clear = memoryClear;
    service.clearAllocate = memoryCalloc;
    service.reAllocate = memoryRealloc;
    service.copy = memoryCopy;
    service.copyTo = memoryCopyTo;
    service.equals = memoryEquals;

    assert(addService(MEM_SERVICE, &service) == RESULT_OK);

    logger->debug("Memory service initialized.");
}
