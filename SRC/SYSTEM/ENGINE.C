//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine interface.
*/

#include "H/ENGINE.H"
#include "H/FILELOG.H"
#include "H/SERVICES/MEM.H"
#include "H/SERVICES/STRING.H"
#include "H/SERVICES/DATETIME.H"
#include "H/SERVICES/LOGGER.H"

typedef struct
{
    register_service_f add;
    get_service_f get;
    get_registered_services_count count;
} _service_provider_t;

typedef struct
{
    service_id_t id;
    void *service;
} service_t;

typedef struct
{
    int signature;
    version_t *version;
    _service_provider_t *services;
} _tlsa98_engine_t;

static int servicesCount = 0;
static service_t servicesContainer[32];
static _tlsa98_engine_t *_engine;

// Service provider //

static int getServiceProviderCount()
{
    return servicesCount;
}

static const void *findService(const service_id_t id)
{
    int i;

    logMessage(LOG_DEBUG, "Request service %d...", id);

    for (i = 0; i < servicesCount; i++)
    {
        if (servicesContainer[i].id == id)
        {
            logMessage(LOG_DEBUG, "Service %d found.", id);

            return servicesContainer[i].service;
        }
    }

    logMessage(LOG_DEBUG, "Service %d not found.", id);

    return NULL;
}

static bool registerService(const service_id_t id, const void *service)
{
    if (servicesCount < 32 && findService(id) == NULL)
    {
        logMessage(LOG_DEBUG, "Registering service %d...", id);
        {
            servicesContainer[servicesCount].id = id;
            servicesContainer[servicesCount].service = (void *)service;
            servicesCount++;
        }
        logMessage(LOG_DEBUG, "Service %d registered.", id);

        return true;
    }
    else
    {
        logMessage(LOG_CRITICAL, "Error registering service %d.", id);
        return false;
    }
}

void initializeServiceProvider()
{
    // Create and initialize the service provider:
    _engine->services = (_service_provider_t *)malloc(sizeof(_service_provider_t));
    {
        _engine->services->add = registerService;
        _engine->services->get = findService;
        _engine->services->count = getServiceProviderCount;
    }
}

// Engine initialization //

static void setEngineSignature()
{
    _engine->signature = TLSA98_ENGINE_SIGNATURE;

    logMessage(LOG_INFO, "Engine signature: 0x%x", _engine->signature);
}

static void setEngineVersion()
{
    _engine->version = (version_t *)malloc(sizeof(version_t));
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
    _engine = ((_tlsa98_engine_t *)(void *)NET);
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
    {
        registerLoggerService();
        registerMemService();
        registerStringService();
        registerDateTimeService();
    }
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
