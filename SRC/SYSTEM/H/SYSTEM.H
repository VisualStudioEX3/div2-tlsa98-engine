//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Main engine library and access to all core services.
*/

#ifndef __SYSTEM_DLL_H_
#define __SYSTEM_DLL_H_

#define DEBUG

#include <assert.h>
#include <stdarg.h>
#include <string.h>

// Core dependencies:
#include "DIV2API.H"
#include "SERVICES.H"
#include "SERVICES.H"
#include "LIST.H"

// Core services:
#include "SERVICES/MEM.H"
#include "SERVICES/STRING.H"
#include "SERVICES/DATETIME.H"
#include "SERVICES/LOGGER.H"

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

/// @brief Default function success result.
#define RESULT_OK 0

/// @brief Default function error result.
#define RESULT_ERROR -1

/**
 * @brief Boolean alias.
 * @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
 */
typedef int bool;

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

/**
 * @brief BYTE type in DIV Games Studio 2.
 * @remarks You can use this alias instead of normal char (-127 to 127) to
 * manage memory stream data, ensuring that all values are valid byte values (0
 * to 255).
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
 * @return Returns [true] if engine instance major and minor version are major
 * or equal than requiured [_major] and [_minor] parameters, [false] otherwise.
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

#endif
