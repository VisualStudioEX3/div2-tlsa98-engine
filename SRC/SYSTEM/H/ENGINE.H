//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine interface.
*/

#ifndef __SYSTEM_DLL_ENGINE_H_
#define __SYSTEM_DLL_ENGINE_H_

#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include "TYPES.H"
#include "DIV2.H"

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

/// @brief A service is already registered with the used id.
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED 1000

/// @brief Service id type.
typedef int service_id_t;

typedef int (*register_service_f)(const service_id_t, const void *);
typedef const void *(*get_service_f)(const service_id_t);
typedef int (*get_registered_services_count)();

/// @brief Service provider.
typedef struct
{
    /**
     * @brief Registers a new service.
     * @param id Unique id used to identify the service.
     * @param service Pointer to the service.
     * @return Returns [RESULT_ERROR_SERVICE_ALREADY_REGISTERED] if a service is
     * already registered with this id, [RESULT_ERROR_SERVICE_CONTAINER_IS_FULL]
     * if the service container is full, [RESULT_OK] otherwise.
     */
    const register_service_f registerService;

    /**
     * @brief Gets the service instance.
     * @param id The service id.
     * @return Returns the pointer to the service, [NULL] if the id is not found.
     */
    const get_service_f getService;

    /**
     * @brief Gets the number of registered services.
     * @return Returns the number of registered services in the container.
     */
    const get_registered_services_count getCount;
} service_provider_t;

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
const tlsa98_engine_t *engine = (const tlsa98_engine_t *)NET;

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
 * @param array Array to measure.
 * @return Returns the array size.
 */
#define arraylen(array) sizeof(array) / sizeof(array[0])

/**
 * @brief [malloc] alias to DIV implementation.
 * @param size Size of the memory region to allocate.
 * @return Returns the pointer to the new allocated memory region.
 * @remarks DIV Games Studio runtime has his own [malloc] implementation to
 * manage his memory allocations. If you try to use the standard [malloc] the
 * program starts to generate memory corruption and even crashes. This macro
 * allows you to use safe [malloc] calls but using the DIV implementation.
 */
#define malloc(size) div_malloc(size)

/**
 * @brief [free] alias to DIV implementation.
 * @param ptr Pointer of the memory region to release.
 * @remarks DIV Games Studio runtime has his own [free] implementation to
 * manage his memory deallocations. If you try to use the standard [free] the
 * program starts to generate memory corruption and even crashes. This macro
 * allows you to use safe [free] calls but using the DIV implementation.
 */
#define free(ptr) div_free(ptr)

/**
 * @brief Custom implementation of ANSI C99 va_copy macro.
 * @remarks Watcom C++ 10.6 (C89/ANSI C) not implements [va_copy] macro.
 */
#define va_copy(dst, src) memcpy((void *)dst, (void *)src, sizeof(va_list));

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
#define fopen(filename, mode) div_fopen(filename, mode)

/**
 * @brief [fclose] alias to DIV implementation.
 * @param file The pointer to file to close.
 * @remarks DIV Games Studio runtime has his own [fclose] implementation to
 * manage his file close operations. If you try to use the standard [fclose]
 * the program starts to generate memory corruption and even crashes. This
 * macro allows you to use safe [fclose] calls but using the DIV implementation.
 */
#define fclose(file) div_fclose(file)

/**
 * @brief Registers a new service.
 * @param id Unique id used to identify the service.
 * @param service Pointer to the service.
 * @return Returns [RESULT_ERROR_SERVICE_ALREADY_REGISTERED] if a service is
 * already registered with this id, [RESULT_OK] otherwise.
 * @remarks Shortcut to [engine->services->registerService] function.
 */
#define addService(id, service) engine->services->registerService(id, service)

/**
 * @brief Gets the service instance.
 * @param id The service id.
 * @return Returns the pointer to the service, [NULL] if the id is not found.
 * @remarks Shortcut to [engine->services->getService] function.
 */
#define getService(id) engine->services->getService(id)

/**
 * @brief Gets next parameter as integer value from an exported DIV function.
 * @return Returns [int] value.
 * @remarks Remember that parameters are readed from a stack, from last to first.
 */
#define div_readIntParameter getparm()

/**
 * @brief Gets next parameter as string pointer from an exported DIV function.
 * @return Returns [char] pointer.
 * @remarks Remember that parameters are readed from a stack, from last to first.
 */
#define div_readStringParameter (string)(&mem[text_offset + getparm()])

/**
 * @brief Finalizes and setup the return value of an exported DIV function.
 * @param value Integer value to return.
 * @remarks This functions always must be called at the end of an exported function to
 * DIV program.
 */
#define div_return(value) retval(value)

#endif
