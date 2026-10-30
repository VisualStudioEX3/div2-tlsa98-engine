//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Main engine header.

    Global definitions, macros and types, and DIV Games Studio 2 API include and extensions.
*/

#ifndef __SYSTEM_DLL_GLOBALS_H_
#define __SYSTEM_DLL_GLOBALS_H_

#define DEBUG

#include <stdarg.h>            // Required for va_copy macro.
#include <string.h>            // Required for va_copy macro.
#include "../SYSTEM/DIV2API.H" // DIV Games Studio 2 API abstraction.
#include "SERVICES.H"

/**
 * @brief True constant value.
 * @remarks In DIV Games Studio, all odd values are considered as true value.
 */
#define true 1

/**
 * @brief False constant value.
 * @remarks In DIV Games Studio, all even values are considered as false value.
 */
#define false 0

/// @brief Default function success result.
#define RESULT_OK 0

/// @brief Default function error result.
#define RESULT_ERROR -1

/**
 * @brief The engine signature to identify the runtime instance.
 * @remarks Integer value that contains "TLSA" characters in hexadecimal format.
 */
#define TLSA98_ENGINE_SIGNATURE 0x544c5341

/// @brief Major engine version.
#define TLSA98_ENGINE_VERSION_MAJOR 0

/// @brief Minor engine version.
#define TLSA98_ENGINE_VERSION_MINOR 1

/// @brief Revision engine version.
#define TLSA98_ENGINE_VERSION_REVISION 0

/**
 * @brief Boolean alias.
 * @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
 */
typedef int bool;

/**
 * @brief BYTE type in DIV Games Studio 2.
 * @remarks You can use this alias instead of normal char (-127 to 127) to manage
 * memory stream data, ensuring that all values are valid byte values (0 to 255).
 */
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief Unsigned integer alias.
typedef unsigned int uint;

/// @brief Unsigned long alias.
typedef unsigned long ulong;

/**
 * @brief STRING type in DIV Games Studio 2.
 * @remarks An alias for char pointer type. All DIV parameters, even the string
 * values, are received as integer values as a position in DIV managed memory of
 * the parameter is stored.
 */
typedef char *string;

/**
 * @brief Semantic version.
 * @remarks Used to identify an API changes and feature evolution, and to
 * control compatibility level of third party libraries that interacts with the
 * API.
 */
typedef struct
{
    /**
     * @brief Major version. Represents major changes on API.
     * @remarks This number must be updated when the API implements a major
     * changes, like a new main service or third party libraries, or even a
     * broken compatibility with previous versions. When a major version is
     * updated, minor version an revision number must be set to zero.
     */
    byte major;

    /**
     * @brief Minor version. Represents a feature changes on the current major
     * version of the API.
     * @remarks This number must be updated when, in the current major version,
     * the API upgrade an existing service, add a new services as dependency of
     * main ones (a service that not should be a main service) and minor changes
     * that not broken compatibility with previous versions. When a minor
     * version is updated, revision number must be set to zero.
     */
    byte minor;

    /**
     * @brief Revision number. Represents a patch or bugfix applied on current
     * minor version of the API.
     * @remarks This number must be updated only when, on a current minor
     * version, it required apply a bugfix or patch to solve problems whitout
     * require make changes on API or current behaviours. If the fix implies
     * implement new features, new top services or change any current expected
     * behaviour, this should be considered as new minor version. If the fix
     * implies remove or create new feature that broken the API compatibility,
     * must be considered as new major version.
     */
    byte revision;

    /// @brief Value reserved for future purposes.
    byte reserved;
} version_t;

/**
 * @brief TLSA98 Engine main interface.
 * @remarks This interface exposes the main access to engine services and other
 * relevant data or implementations across the different engine libraries. The
 * struct setup is designed to remplace the DIV Games Studio _net struct,
 * occuping the same space.
 */
typedef struct
{
    /**
     * @brief Interface signature.
     * @remarks Use it to check if the pointer address this interface and avoid
     * errors if the engine is not properly initialized.
     */
    const int signature;

    /**
     * @brief Engine version.
     * @remarks Identifies the engine version. Use it to ensure if your code is
     * compatible with the engine version.
     */
    const version_t *version;

    /// @brief DIV Games Studio 2 API abstraction.
    const div2_api_t *div2API;

    /// @brief Engine services provider.
    const service_provider_t *services;
} tlsa98_engine_t;

/**
 * @brief Gets the TLSA98 Engine runtime instance.
 * @remarks MS-DOS does not supports dynamic link libraries (DLLs) like Windows
 * systems. DIV Games Studio implements a custom system to map Windows COM DLLs
 * functions, but not supports to comunicate between them. These DLLs works as
 * isolated libraries only visibles by DIV Games Studio runtime.
 *
 * As a solution to share the services between different DLLs, not only with
 * DIV Games Studio runtime, we used a little trick to store the service
 * provider and another data directly in the DIV Games Studio runtime memory
 * session, using one of the unused structures like [_net] (because this project
 * not require the network system).
 *
 * In this case, the [_net] struct memory is reserved in the DIV Games Studio
 * runtime memory but not initialized until the game code tries to initialize
 * the network system. This allow us to use this memory to store the pointer to
 * the main engine interface, and be accessible for all DLLs that uses the
 * [SYSTEM.H] header file.
 */
const tlsa98_engine_t *engine;

/**
 * @brief Returns [true] if engine instance signature matches with header
 * definition signature, [false] otherwise.
 */
#define TLSA98_ENGINE_SIGNATURE_EQUALS \
    (engine->signature == TLSA98_ENGINE_SIGNATURE)

/**
 * @brief Checks if engine instance major and minor version are major or equal
 * than major and minor parameters.
 * @param _major Required major version.
 * @param _minor Required minor version.
 * @return Returns [true] if engine instance major and minor version are major or
 * equal than requiured [_major] and [_minor] parameters, [false] otherwise.
 */
#define TLSA98_ENGINE_VERSION_MAJOR_OR_EQUALS(_major, _minor) \
    engine->version->major >= _major && engine->version->minor >= _minor

/**
 * @brief Gets the size of an array.
 * @param a Array to measure.
 * @return Returns the array size.
 */
#define arraylen(a) sizeof(a) / sizeof(a[0])

/**
 * @brief Custom implemnetation of ANSI C99 va_copy macro.
 * @remarks Watcom C++ 10.6 (C89/ANSI C) not implements [va_copy] macro.
 */
#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list));

/**
 * @brief [malloc] alias to DIV implementation.
 * @param size Size of the memory region to allocate.
 * @return Returns the pointer to the new allocated memory region.
 * @remarks DIV Games Studio runtime has his own [malloc] implementation to
 * manage his memory allocations. If you try to use the standard [malloc] the
 * program starts to generate memory corruption and even crashes. This macro
 * allows you to use safe [malloc] calls but using the DIV implementation.
 */
#define malloc(size) engine->div2API->allocateMemory(size)

/**
 * @brief [free] alias to DIV implementation.
 * @param ptr Pointer of the memory region to release.
 * @remarks DIV Games Studio runtime has his own [free] implementation to
 * manage his memory deallocations. If you try to use the standard [free] the
 * program starts to generate memory corruption and even crashes. This macro
 * allows you to use safe [free] calls but using the DIV implementation.
 */
#define free(ptr) engine->div2API->freeMemory(ptr)

/**
 * @brief [fopen] alias to DIV implementation.
 * @param filename The path and name of the file to open.
 * @param mode File access mode. See standard fopen documentation to know the
 * avaiable modes: https://cplusplus.com/reference/cstdio/fopen/.
 * @return Returns the pointer to the opened file, [NULL] otherwise.
 * @remarks DIV Games Studio runtime has his own [fopen] implementation to
 * manage his file open operations. If you try to use the standard [fopen] the
 * program starts to generate memory corruption and even crashes. This macro
 * allows you to use safe [fopen] calls but using the DIV implementation.
 */
#define fopen(filename, mode) engine->div2API->openFile(filename, mode)

/**
 * @brief [fclose] alias to DIV implementation.
 * @param file The pointer to file to close.
 * @remarks DIV Games Studio runtime has his own [fclose] implementation to
 * manage his file close operations. If you try to use the standard [fclose]
 * the program starts to generate memory corruption and even crashes. This
 * macro allows you to use safe [fclose] calls but using the DIV implementation.
 */
#define fclose(file) engine->div2API->closeFile(file)

/**
 * @brief Gets the service instance.
 * @param id The service id.
 * @return Returns the pointer to the service, [NULL] if the id is not found.
 * @remarks Shortcut to [engine->services->getService] function.
 */
#define getService(id) engine->services->getService(id)

/**
 * @brief Registers a new service.
 * @param id Unique id used to identify the service.
 * @param service Pointer to the service.
 * @return Returns [RESULT_ERROR_SERVICE_ALREADY_REGISTERED] if a service is
 * already registered with this id, [RESULT_ERROR_SERVICE_CONTAINER_IS_FULL]
 * if the service container is full, [RESULT_OK] otherwise.
 * @remarks Shortcut to [engine->services->registerService] function.
 */
#define addService(id, service) engine->services->registerService(id, service)

#endif
