//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine interface.
*/

#include "H/ENGINE.H"
#include "H/FILELOG.H"
#include "H/LIST.H"
#include "H/SERVICES/MEM.H"
#include "H/SERVICES/STRING.H"
#include "H/SERVICES/DATETIME.H"
#include "H/SERVICES/LOGGER.H"

static const int MAX_SERVICES = 64;

typedef struct
{
    register_service_f registerService;
    get_service_f getService;
    get_registered_services_count getCount;
} _service_provider_t;

typedef struct
{
    service_id_t id;
    const void *service;
} service_t;

typedef struct
{
    int signature;
    version_t *version;
    service_provider_t *services;
} _tlsa98_engine_t;

static list_t *serviceContainer;
static _tlsa98_engine_t *_engine;

// Service provider //

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
    _service_provider_t *provider = (_service_provider_t *)malloc(sizeof(_service_provider_t));
    {
        provider->getCount = getServiceProviderCount;
        provider->getService = findService;
        provider->registerService = registerService;
    }

    _engine->services = (service_provider_t *)provider;
}

// Engine initialization //

static void setEngineSignature()
{
    _engine->signature = TLSA98_ENGINE_SIGNATURE;

    logMessage(LOG_INFO, "Engine signature: 0x%x", _engine->signature);
}

static void setEngineVersion()
{
    _engine->version = (version_t *)div_malloc(sizeof(version_t));
    {
        version_t *version = _engine->version;

        version->major = TLSA98_ENGINE_VERSION_MAJOR;
        version->minor = TLSA98_ENGINE_VERSION_MINOR;
        version->revision = TLSA98_ENGINE_VERSION_REVISION;
        version->reserved = 0;

        logMessage(LOG_INFO, "Engine version: %i.%i.%i",
                   version->major, version->minor, version->revision);
    }
}

static void initializeEngineInterface()
{
    logMessage(LOG_DEBUG, "Initializing engine interface...");

    /*
     * Used DIV.H NET struct address to share the TLSA98 Engine address location
     * between different DLLs loaded into DIV Games Studio runtime.
     */
    _engine = (_tlsa98_engine_t *)NET;
    {
        memset(_engine, NULL, sizeof(_tlsa98_engine_t));

        setEngineSignature();
        setEngineVersion();
        initializeServiceProvider();
    }

    logMessage(LOG_DEBUG, "Engine interface initialized.");
}

static void initializeServices()
{
    logMessage(LOG_DEBUG, "Registering core services...");

    registerLoggerService();
    registerMemService();
    registerStringService();
    registerDateTimeService();

    logMessage(LOG_DEBUG, "Core services registered.");
}

static void initializeDIVCallbacks()
{
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();

    openLogFile("Initiatizing TLSA98 Engine...");

    initializeEngineInterface();
    initializeServices();
    initializeDIVCallbacks();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Export here all services to DIV language:
    // ...

    logMessage(LOG_INFO, "Engine initialized.");
}

void __export divend(COMMON_PARAMS)
{
    // FYI: Testing FOO.DLL we get the DIV2 runtime perform the divend calls in inverse order
    // of the libraries are initialized. For the "terminating engine" logs and actions, maybe
    // is a good idea to create an event of "engine termination" to do this.
    logMessage(LOG_INFO, "Terminating engine...");

    // Terminate here services:
    // ...

    closeLogFile("Engine terminated.");
}
