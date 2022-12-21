//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio 2 header setup and extensions.
*/

#ifndef __SYSTEM_DIV2_
#define __SYSTEM_DIV2_

#define GLOBALS         // Required by DIV.H (before incluide it).

#include "DIV.H"        // DIV Games Studio 2 API.

/// @brief getparm() version to get a DIV Games Studio 2 STRING parameter.
/// @return Returns the next parameter from DIV function stack as string value.
#define getstrparm()    (char*)&mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
/// @param Size Size of the memory region to allocate.
/// @return Returns the pointer to the new allocated memory region.
#define malloc(size)    div_malloc(size)

/// @brief free() alias to DIV implementation.
/// @param ptr Pointer of the memory region to release.
#define free(ptr)       div_free(ptr)

#endif