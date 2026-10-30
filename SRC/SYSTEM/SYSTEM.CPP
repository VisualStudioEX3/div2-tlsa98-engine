//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System library entry point.
*/

#include "../H/DIV2.H"
#include "../H/SYSTEM.H"
#include "../H/SYSTEM/FILELOG.H"
#include "../H/SYSTEM/SERVICES.H"

typedef struct
{
    int signature;
    version_t *version;
    div2_api_t *div2API;
    service_provider_t *services;
} _tlsa98_engine_t;

static _tlsa98_engine_t *_engine;

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

        logMessage(LOG_INFO, "Engine version: %i.%i.%i", version->major, version->minor, version->revision);
    }
}

static void initializeEngineInterface()
{
    logMessage(LOG_DEBUG, "Initializing engine interface...");

    _engine = (_tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;
    {
        memset(_engine, NULL, sizeof(_tlsa98_engine_t));

        setEngineSignature();
        setEngineVersion();

        _engine->div2API = registerDIV2API();
        _engine->services = initializeServiceProvider();

        engine = (const tlsa98_engine_t *)_engine;
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
