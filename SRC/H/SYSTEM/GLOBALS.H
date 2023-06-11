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

/// @brief The engine signature to identify the runtime instance.
/// @remarks Integer value that contains "TLSA" characters in hexadecimal format.
#define TLSA98_ENGINE_SIGNATURE 0x544c5341

/// @brief Major engine version.
#define TLSA98_ENGINE_VERSION_MAJOR 0

/// @brief Minor engine version.
#define TLSA98_ENGINE_VERSION_MINOR 1

/// @brief Build engine version.
#define TLSA98_ENGINE_VERSION_BUILD 0

/// @brief Revision engine version.
#define TLSA98_ENGINE_VERSION_REVISION 0

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

/// @brief Semantic version.
typedef struct
{
    /// @brief Major version.
    byte major;
    /// @brief Minor version.
    byte minor;
    /// @brief Build number.
    byte build;
    /// @brief Revision number.
    byte revision;
} version_t;

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

/// @brief TLSA98 Engine main interface.
/// @remarks This interface exposes the main access to engine services and other relevant
/// data or implementations across the different engine libraries. The struct setup is 
/// designed to remplace the DIV Games Studio _net struct, occuping the same space.
typedef struct
{
    /// @brief Interface signature.
    /// @remarks Use it to check if the pointer address this interface and avoid errors
    /// if the engine is not properly initialized.
    int signature;
    /// @brief Engine version.
    /// @remarks Identifies the engine version. Use it to ensure if your code is 
    /// compatible with the engine version.
    version_t *version;
    /// @brief Engine services provider.
    service_provider_t *services;
    /// @brief Reserved for future implementations.
    void *reserved1;
    /// @brief Reserved for future implementations.
    void *reserved2;
} tlsa98_engine_t;

/// @brief Gets the TLSA98 Engine runtime instance.
/// @remarks MS-DOS does not supports dynamic link libraries (DLLs) like Windows systems.
/// DIV Games Studio implements a custom system to map Windows COM DLLs functions, but not
/// supports to comunicate between them. These DLLs works as isolated libraries only 
/// visibles by DIV Games Studio runtime.
///
/// As a solution to share the services between different DLLs, not only with
/// DIV Games Studio runtime, we used a little trick to store the service provider and another 
/// data directly in the DIV Games Studio runtime memory session, using one of the unused 
/// structures like _net (because this project not require the network system).
///
/// In this case, the _net struct memory is reserved in the DIV Games Studio runtime memory
/// but not initialized until the game code tries to initialize the network system. This
/// allow us to use this memory to store the pointer to the main eneigne interface, and be
/// accessible for all DLLs that uses the SYSTEM.H header file.
#define ENGINE ((const tlsa98_engine_t *)NET)

/// @brief Gets the signature of the TLSA98 Engine runtime instance.
/// @remarks Use with TLSA98_ENGINE_SIGNATURE definition to check if the ENGINE access is
/// properly initialized.
#define SIGNATURE (ENGINE->signature)

/// @brief Gets the version of the TLSA98 Engine runtime instance.
/// @remarks Use TLSA98_ENGINE_VERSION_MAJOR and TLSA98_ENGINE_VERSION_MINOR to check API 
/// compatibility. TLSA98_ENGINE_VERSION_BUILD and TLSA98_ENGINE_VERSION_REVISION should not 
/// be taking in count when you check the API compatibility.
#define VERSION ((const version_t *)ENGINE->version)

/// @brief Access to TLSA98 Engine services.
#define SERVICES ((const service_provider_t *)ENGINE->services)

/// @brief Returns true if engine instance signature matches with header definition signature.
#define TLSA98_ENGINE_SIGNATURE_EQUALS (SIGNATURE == TLSA98_ENGINE_SIGNATURE)

/// @brief Checks if engine instance major and minor version are major or equal than 
/// major and minor parameters.
/// @param _major Required major version.
/// @param _minor Required minor version.
/// @return Returns true if engine instance major and minor version are major or equal than 
/// requiured _major and _minor parameters, false otherwise.
#define TLSA98_ENGINE_VERSION_MAJOR_OR_EQUALS(_major, _minor) \
    VERSION->major >= _major && \
    VERSION->minor >= _minor

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

#endif