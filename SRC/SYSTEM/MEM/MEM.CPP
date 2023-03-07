//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory functions.
*/

#include <string.h>
#include "MEM.H"

void memoryClear(void* ptr, size_t size)
{
    memset(ptr, NULL, size);
}

// We can't use standard calloc, so we implemented own version.
void* memoryCalloc(size_t size)
{
    void* ptr = malloc(size);

    memoryClear(ptr, size);

    return ptr;
}

void* memoryCopy(const void* ptr, size_t size)
{
    void* copyPtr = malloc(size);

    memoryCopyTo(ptr, copyPtr, size);

    return copyPtr;
}

void memoryCopyTo(const void* from, void* to, size_t size)
{
    memmove(to, from, size);
}

bool memoryEquals(const void* ptr1, const void* ptr2, size_t size)
{
    return memcmp(ptr1, ptr2, size) == 0;
}