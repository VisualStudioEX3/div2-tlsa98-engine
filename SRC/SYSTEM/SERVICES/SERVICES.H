//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider that allow to shared different system implementations between DIV DLLs.
*/

#ifndef _SYSTEM_SERVICES_
#define _SYSTEM_SERVICES_

#include "..\SYSTEM.H"

/// @brief A service is already registered with the used id.
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED     1000

/// @brief Service container is full.
#define RESULT_ERROR_SERVICE_CONTAINER_IS_FULL      1001

/// @brief Service id.
typedef int service_id_t;

/// @brief Initialize the service provider.
void initializeServiceContainer();

/// @brief Registers a new service.
/// @param id Unique id used to identify the service.
/// @param service Pointer to the service.
/// @return Returns #SYSTEM::RESULT_ERROR_SERVICE_ALREADY_REGISTERED if a service is already 
/// registered with this id, #SYSTEM::RESULT_ERROR_SERVICE_CONTAINER_IS_FULL if the service 
/// container is full, #SYSTEM::RESULT_OK otherwise.
int registerService(service_id_t id, const void* service);

/// @brief Gets the service instance.
/// @param id The service id.
/// @return Returns the pointer to the service, #DIV::NULL if the id is not found. 
const void* getService(service_id_t id);

/// @brief Gets the number of registered services.
/// @return Returns the number of registered services in the container. 
int getServiceCount();

#endif
