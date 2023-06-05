//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\SYSTEM\LIST.H"

const int MAX_SERVICES = 64;

typedef struct
{
    service_id_t id;
    void *service;
} service_t;

list_t *serviceContainer;
service_provider_t *serviceProvider;

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
    // Create and initialize the service container:
    serviceContainer = createList(MAX_SERVICES, sizeof(service_t));

    // Create and initialize the service provider:
    serviceProvider = (service_provider_t *)malloc(sizeof(service_provider_t));
    {
        serviceProvider->getCapacity = getServiceProviderCapacity;
        serviceProvider->getCount = getServiceProviderCount;
        serviceProvider->getService = getService;
        serviceProvider->registerService = registerService;
    }

    /*
     * MS-DOS does not supports dynamic link libraries (DLLs) like Windows systems.
     * DIV Games Studio implements a custom system to map Windows COM DLLs functions, but not
     * supports to comunicate between them. These DLLs works as isolated libraries only 
     * visibles by DIV Games Studio runtime.
     *
     * As a solution to share the services between different DLLs, not only with
     * DIV Games Studio runtime, we used a little trick to store the service provider directly
     * in the DIV Games Studio runtime session, using one of the not used structures like NET
     * (because this project not require the network system).
     *
     * In this case, the NET struct memory is reserved in the DIV Games Studio runtime memory
     * but not initialized until the game code tries to initialize the network system. This
     * allow us to use this memory to store the pointer to the service provider, and be
     * accessible for all DLLs that uses the SYSTEM.H header file.
     */

    memcpy(NET, &serviceProvider, sizeof(service_provider_t *));
}