//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Global members.
*/

#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#define GLOBALS         // Required by DIV.H (before incluide it).

#include "DIV.H"        // DIV Games Studio 2 API.

/// @brief True constant value.
/// @remarks In DIV Games Studio, all odd values are considered as true value.
#define true            1

/// @brief False constant value.
/// @remarks In DIV Games Studio, all even values are considered as false value.
#define false           0

/// @brief Default function success result.
#define RESULT_OK       0

/// @brief Default function error result.
#define RESULT_ERROR    -1

/// @brief Boolean alias.
/// @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
typedef int bool;

/// @brief BYTE type in DIV Games Studio 2.
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief Unsigned integer alias.
typedef unsigned int uint;

/// @brief STRING type in DIV Games Studio 2.
/// @remarks An alias for char pointer type.
typedef char* string;

/// @brief getparm() version to get a DIV Games Studio 2 STRING parameter.
/// @return Returns the next parameter from DIV function stack as string value.
#define getstrparm()    (string)&mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
/// @param Size Size of the memory region to allocate.
/// @return Returns the pointer to the new allocated memory region.
#define malloc(size)    div_malloc(size)

/// @brief free() alias to DIV implementation.
/// @param ptr Pointer of the memory region to release.
#define free(ptr)       div_free(ptr)

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a)     sizeof(a) / sizeof(a[0])

#endif