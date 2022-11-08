//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine base members and shared entry point to service provider.
*/

#ifndef _SYSTEM_DLL_
#define _SYSTEM_DLL_

#define GLOBALS                 // Required by DIV.H (before incluide it).
#include "..\DIV.H"             // DIV Games Studio 2 API header.
#include "SERVICES/SERVICES.H"  // Service provider header.

/// @brief BYTE type in DIV Games Studio 2.
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief STRING type in DIV Games Studio 2.
/// @remarks An alias for char pointer type.
typedef char* string;

/// @brief Boolean alias.
/// @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
typedef int bool;

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

/// @brief DIV getparm() overload to get a DIV2 STRING parameter.
#define getstrparm()    (string)&mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
#define malloc(size)    div_malloc(size)

/// @brief free() alias to DIV implementation.
#define free(ptr)       div_free(ptr)

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a)     sizeof(a) / sizeof(a[0])

#endif
