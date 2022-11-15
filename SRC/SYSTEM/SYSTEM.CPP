//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine base members and service provider.
*/

#include <string.h>
#include "..\H\SYSTEM.H"
#include "MATH\DIVFNEXP.H"

const int MAX_SERVICES = 64;

typedef struct service_t
{
    service_id_t id;
    const void* service;
} service_t;

typedef struct service_container_t
{
    service_t* services[MAX_SERVICES];
    int count;
} service_container_t;

service_container_t* serviceContainer;

static bool isContainerFull()
{
    return serviceContainer->count == MAX_SERVICES;
}

static service_t* searchService(service_id_t id)
{
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        service_t* service = serviceContainer->services[i];
        
        if (service->id == id)
            return service;
    }

    return NULL;
}

static bool containsService(service_id_t id)
{
    return searchService(id) == NULL;
}

void initializeServiceContainer()
{
    // Use DIV Games Studio 2 NET struct as shared pointer to store the service container.
    // The reason to use NET struct instead other DIV struct if because I don't want to use the DIV network
    // system for my project. If I used the network system I can use other shared struct like M7 or M8 if also
    // I don't want to use these systems.
    serviceContainer = ((service_container_t*)NET);

    // Initialize service container:
    memset(serviceContainer->services, NULL, arraylen(serviceContainer->services));
    serviceContainer->count = 0;
}

int registerService(service_id_t id, const void* service)
{
    if (isContainerFull())
        return RESULT_ERROR_SERVICE_CONTAINER_IS_FULL;

    if (containsService(id))
        return RESULT_ERROR_SERVICE_ALREADY_REGISTERED;

    service_t* slot = serviceContainer->services[serviceContainer->count];

    slot->id = id;
    slot->service = service;

    serviceContainer->count++;

    return RESULT_OK;
}

const void* getService(service_id_t id)
{
    return searchService(id);
}

int getServiceProviderCount()
{
    return serviceContainer->count;
}

int getServiceProviderCapacity()
{
    return MAX_SERVICES;
}

static void initialize()
{
    initializeServiceContainer();
    registerMathService();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Register DIV functions.
    exportMathService(LIBRARY_PARAMS);
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    initialize(); // Initialize services.
    // Register DIV callbacks.
}

void __export divend(COMMON_PARAMS)
{
    // Terminate services.
}
