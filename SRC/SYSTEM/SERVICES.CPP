//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#include <assert.h>
#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\SYSTEM\LIST.H"

const int MAX_SERVICES = 64;

list_t *serviceContainer;

static bool serviceIdComparer(void *item, va_list args)
{
    service_t *service = (service_t *)item;
    service_id_t id = va_arg(args, service_id_t);

    return service->id == id;
}

static int getServiceProviderCapacity()
{
    return serviceContainer->capacity;
}

static int getServiceProviderCount()
{
    return serviceContainer->count;
}

static const void *findService(service_id_t id)
{
    void *servicePointer = NULL;
    service_t *item = (service_t *)findListItem(serviceContainer, serviceIdComparer, id);

    if (item)
        servicePointer = item->service;
    // TODO: Assert service id not found.

    return servicePointer;
}

static int registerService(service_id_t id, void *service)
{
    if (isListFull(serviceContainer))
        return RESULT_ERROR_SERVICE_CONTAINER_IS_FULL;

    if (isListItemExists(serviceContainer, serviceIdComparer, id))
        return RESULT_ERROR_SERVICE_ALREADY_REGISTERED;

    service_t *slot = (service_t *)createListItem(serviceContainer);

    slot->id = id;
    slot->service = service;

    // TODO: Assert failed register service (check if pointer is null).

    return RESULT_OK;
}

void initializeServiceProvider()
{
    // Create and initialize the service container:
    serviceContainer = createList(MAX_SERVICES, sizeof(service_t));

    // Create and initialize the service provider:
    engine->services = (service_provider_t *)malloc(sizeof(service_provider_t));
    {
        service_provider_t *services = engine->services;

        services->getCapacity = getServiceProviderCapacity;
        services->getCount = getServiceProviderCount;
        services->getService = findService;
        services->registerService = registerService;
    }
}