/* ----------------------------------------------------------------------------
 * SYSTEM.DLL - System library for DIV Games Studio.
 * (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
 * DIV Games Studio 2 (C) Hammer Technologies - 1998, 1999
 * ---------------------------------------------------------------------------- */

#ifndef _SYSTEM_SERVICES_
#define _SYSTEM_SERVICES_

#include "..\SYSTEM.H"

/**
 * A service is already registered with the used id.
 */
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED     1000

/**
 * Service container is full.
 */
#define RESULT_ERROR_SERVICE_CONTAINER_IS_FULL      1001

/**
 * Service id.
 */
typedef int service_id_t;

/**
 * Registers a new service.
 * 
 * @param id        Unique id used to identify the service.
 * @param service   Pointer to the service.
 * 
 * @return Returns {RESULT_ERROR_SERVICE_ALREADY_REGISTERED} if a service is already 
 * registered with this id, {RESULT_ERROR_SERVICE_CONTAINER_IS_FULL} if the service 
 * container is full, {RESULT_OK} otherwise.
 */
int registerService(service_id_t id, const void* service);

/**
 * Gets the service instance.
 * 
 * @param id        The service id.
 * 
 * @return Returns the pointer to the service, {NULL} if the id is not found.
 */
const void* getService(service_id_t id);

/**
 * Gets the number of registered services.
 * 
 * @return Returns the number of registered services in the container.
 */
int getServiceCount();

#endif
