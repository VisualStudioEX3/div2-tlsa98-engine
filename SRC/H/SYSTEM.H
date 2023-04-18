//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Main engine file and access to all core services.
*/

#ifndef __SYSTEM_DLL_H_
#define __SYSTEM_DLL_H_

#define GLOBALS                 // Required by DIV.H.
#define DOSBOX_SUPPORT          // Uncomment this for support and fixes for DOSBox emulator.

#include <stdarg.h>
#include <string.h>
#include "DIV.H"                // DIV Games Studio 2 API. This header also include stdio.h.
#include "SYSTEM\SERVICES.H"    // Service provider.
#include "SYSTEM\MEM.H"         // Memory service.
#include "SYSTEM\STRING.H"      // String service.
#include "SYSTEM\DIVFNEXP.H"    // DIV Games Studio function exporter service.
#include "SYSTEM\MATH.H"        // Math service.

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
/// @remarks You can use this alias instead of normal char (-127 to 127) to manage memory
/// stream data, ensuring that all values are valid byte values (0 to 255).
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief Unsigned integer alias.
typedef unsigned int uint;

/// @brief Unsigned long alias.
typedef unsigned long ulong;

/// @brief STRING type in DIV Games Studio 2.
/// @remarks An alias for char pointer type. All DIV parameters, even the string values, are
/// received as integer values as a position in DIV managed memory of the parameter is stored.
typedef char* string;

/// @brief Date and time value.
typedef struct datetime_t
{
    /// @brief Seconds after the minute (from 0).
    int seconds;
    /// @brief Minutes after the hour (from 0).
    int minutes;
    /// @brief Hour of the day (from 0).
    int hour;
    /// @brief Day of the month (from 1).
    int day;
    /// @brief Month of the year (from 1).
    int month;
    /// @brief Year (from 1900).
    int year;
};

/// @brief #DIV::getparm() version to get a DIV Games Studio 2 STRING parameters.
/// @return Returns the next parameter from DIV function stack as string value.
#define getstrparm()        (string)&mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
/// @param size Size of the memory region to allocate.
/// @return Returns the pointer to the new allocated memory region.
/// @remarks DIV Games Studio runtime has his onw malloc() implementation to manage his 
/// memory allocations. If you try to use the standard malloc() the program starts to generate
/// memory corruption and even crashes. This macro allows you to use safe malloc() calls but 
/// using the DIV implementation.
#define malloc(size)        div_malloc(size)

/// @brief free() alias to DIV implementation.
/// @param ptr Pointer of the memory region to release.
/// @remarks DIV Games Studio runtime has his onw free() implementation to manage his 
/// memory allocations. If you try to use the standard free() the program starts to generate
/// memory corruption and even crashes. This macro allows you to use safe free() calls but 
/// using the DIV implementation.
#define free(ptr)           div_free(ptr)

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a)         sizeof(a) / sizeof(a[0])

/// @brief Custom implemnetation of ANSI C99 va_copy macro.
#define va_copy(dst, src)   memcpy((void*)dst, (void*)src, sizeof(va_list));

#endif