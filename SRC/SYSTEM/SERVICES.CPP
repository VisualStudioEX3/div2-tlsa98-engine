//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#include <assert.h>
#include "../H/SYSTEM/SERVICES.H"
#include "../H/SYSTEM/LIST.H"

static const int MAX_SERVICES = 64;

typedef struct
{
    register_service_f registerService;
    get_service_f getService;
    get_registered_services_count getCount;
    get_service_provider_capacity_f getCapacity;
} _service_provider_t;

typedef struct
{
    service_id_t id;
    const void *service;
} service_t;

static list_t *serviceContainer;

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

static const void *findService(const service_id_t id)
{
    const void *servicePointer = NULL;
    service_t *item = (service_t *)findListItem(serviceContainer, serviceIdComparer, id);

    if (item)
        servicePointer = item->service;
    // TODO: Assert service id not found.

    return servicePointer;
}

static int registerService(const service_id_t id, const void *service)
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

service_provider_t *initializeServiceProvider()
{
    // Create and initialize the service container:
    serviceContainer = createList(MAX_SERVICES, sizeof(service_t));

    // Create and initialize the service provider:
    _service_provider_t *provider = (_service_provider_t *)malloc(sizeof(_service_provider_t));
    {
        provider->getCapacity = getServiceProviderCapacity;
        provider->getCount = getServiceProviderCount;
        provider->getService = findService;
        provider->registerService = registerService;
    }

    return (service_provider_t *)provider;
}
