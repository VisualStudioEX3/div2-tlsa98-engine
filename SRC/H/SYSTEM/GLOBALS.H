//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Global definitions, macros and types, and DIV Games Studio 2 API include and extensions.
*/

#ifndef __SYSTEM_DLL_GLOBALS_H_
#define __SYSTEM_DLL_GLOBALS_H_

#define GLOBALS        // Requires by DIV.H before include it.
#define DOSBOX_SUPPORT // Uncomment this for support and fixes for DOSBox emulator.

#include <stdarg.h> // Required for va_copy macro.
#include <string.h> // Required for va_copy macro.
#include "DIV.H"    // DIV Games Studio 2 API.

/// @brief True constant value.
/// @remarks In DIV Games Studio, all odd values are considered as true value.
#define true 1

/// @brief False constant value.
/// @remarks In DIV Games Studio, all even values are considered as false value.
#define false 0

/// @brief Default function success result.
#define RESULT_OK 0

/// @brief Default function error result.
#define RESULT_ERROR -1

/// @brief A service is already registered with the used id.
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED 1000

/// @brief Service container is full.
#define RESULT_ERROR_SERVICE_CONTAINER_IS_FULL 1001

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
typedef char *string;

/// @brief Date and time value.
typedef struct
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
} datetime_t;

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a) sizeof(a) / sizeof(a[0])

/// @brief Custom implemnetation of ANSI C99 va_copy macro.
#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list));

/// @brief #DIV::getparm() version to get a DIV Games Studio 2 STRING parameters.
/// @return Returns the next parameter from DIV function stack as string value.
#define getstrparm() (string) & mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
/// @param size Size of the memory region to allocate.
/// @return Returns the pointer to the new allocated memory region.
/// @remarks DIV Games Studio runtime has his own malloc() implementation to manage his
/// memory allocations. If you try to use the standard malloc() the program starts to generate
/// memory corruption and even crashes. This macro allows you to use safe malloc() calls but
/// using the DIV implementation.
#define malloc(size) div_malloc(size)

/// @brief free() alias to DIV implementation.
/// @param ptr Pointer of the memory region to release.
/// @remarks DIV Games Studio runtime has his own free() implementation to manage his
/// memory deallocations. If you try to use the standard free() the program starts to generate
/// memory corruption and even crashes. This macro allows you to use safe free() calls but
/// using the DIV implementation.
#define free(ptr) div_free(ptr)

/// @brief fopen() alias to DIV implementation.
/// @param filename The path and name of the file to open.
/// @param mode File access mode. See standard fopen documentation to know the avaiable modes:
/// https://cplusplus.com/reference/cstdio/fopen/.
/// @return Returns the pointer to the opened file, #DIV::NULL otherwise.
/// @remarks DIV Games Studio runtime has his own fopen() implementation to manage his
/// file open operations. If you try to use the standard fopen() the program starts to
/// generate memory corruption and even crashes. This macro allows you to use safe fopen()
/// calls but using the DIV implementation.
#define fopen(filename, mode) div_fopen(filename, mode)

/// @brief fclose() alias to DIV implementation.
/// @param file The pointer to file to close.
/// @remarks DIV Games Studio runtime has his own fclose() implementation to manage his
/// file close operations. If you try to use the standard fclose() the program starts to
/// generate memory corruption and even crashes. This macro allows you to use safe fclose()
/// calls but using the DIV implementation.
#define fclose(file) div_fclose(file)

/// @brief Service id.
typedef int service_id_t;

typedef int (*register_service_f)(service_id_t, void *);
typedef const void *(*get_service_f)(service_id_t);
typedef int (*get_registered_services_count)();
typedef int (*get_service_provider_capacity_f)();

/// @brief Service provider.
typedef struct
{
    /// @brief Registers a new service.
    /// @param id Unique id used to identify the service.
    /// @param service Pointer to the service.
    /// @return Returns #RESULT_ERROR_SERVICE_ALREADY_REGISTERED if a service is already
    /// registered with this id, #RESULT_ERROR_SERVICE_CONTAINER_IS_FULL if the service
    /// container is full, #RESULT_OK otherwise.
    register_service_f registerService;

    /// @brief Gets the service instance.
    /// @param id The service id.
    /// @return Returns the pointer to the service, #DIV::NULL if the id is not found.
    get_service_f getService;

    /// @brief Gets the number of registered services.
    /// @return Returns the number of registered services in the container.
    get_registered_services_count getCount;

    /// @brief Gets the max number of services that service provider can register.
    /// @return Returns the capacity of the service provider.
    get_service_provider_capacity_f getCapacity;
} service_provider_t;

/// @brief Access to the shared service provider instance.
/// @returns Returns a pointer to the shared service provider instance.
/// @remarks See @see SERVICES.CPP file to known the reason to use DIV Games Studio NET struct
/// location in memory.
#define SERVICES ((service_provider_t *)NET)

#endif