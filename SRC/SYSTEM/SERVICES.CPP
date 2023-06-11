//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#include <assert.h>
#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\SYSTEM\LIST.H"

list_t *serviceContainer;

static bool serviceIdComparer(void *item, va_list args)
{
    return ((service_t *)item)->id == va_arg(args, service_id_t);
}

static int getServiceProviderCapacity()
{
    return serviceContainer->capacity;
}

static int getServiceProviderCount()
{
    return serviceContainer->count;
}

static const void *getService(service_id_t id)
{
    return findListItem(serviceContainer, serviceIdComparer, id);
    // TODO: Assert service id not found.
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
    // TODO: Implement own assert to allow custom assertion messages, outputs like the future built-in
    // game console or error reporter, and termination action (end program or terminate current level and 
    // return to game console).
    assert(TLSA98_ENGINE_SIGNATURE_EQUALS);
    assert(TLSA98_ENGINE_VERSION_MAJOR_OR_EQUALS(0, 1));

    // Create and initialize the service container:
    serviceContainer = createList(MAX_SERVICES, sizeof(service_t));

    tlsa98_engine_t *engine = (tlsa98_engine_t *)NET;

    // Create and initialize the service provider:
    engine->services = (service_provider_t *)malloc(sizeof(service_provider_t));
    {
        service_provider_t *services = engine->services;

        services->getCapacity = getServiceProviderCapacity;
        services->getCount = getServiceProviderCount;
        services->getService = getService;
        services->registerService = registerService;
    }
}