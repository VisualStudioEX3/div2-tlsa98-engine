//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#ifndef __SYSTEM_DLL_SERVICES_H_
#define __SYSTEM_DLL_SERVICES_H_

#include "GLOBALS.H"

/// @brief A service is already registered with the used id.
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED 1000

/// @brief Service container is full.
#define RESULT_ERROR_SERVICE_CONTAINER_IS_FULL 1001

/// @brief Service id type.
typedef int service_id_t;

typedef int (*register_service_f)(const service_id_t, const void *);
typedef const void *(*get_service_f)(const service_id_t);
typedef int (*get_registered_services_count)();
typedef int (*get_service_provider_capacity_f)();

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

    /**
     * @brief Gets the max number of services that service provider can register.
     * @return Returns the capacity of the service provider.
     */
    const get_service_provider_capacity_f getCapacity;
} service_provider_t;

/**
 * @brief Initializes the service provider.
 * @returns The service provider instance.
 */
service_provider_t *initializeServiceProvider();

#endif
