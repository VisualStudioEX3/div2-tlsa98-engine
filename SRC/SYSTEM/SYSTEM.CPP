//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System library entry point.
*/

#include "..\H\SYSTEM.H"
#include "..\H\SYSTEM\SERVICES.H"

static void initializeEngineInterface()
{
    tlsa98_engine_t *engine = (tlsa98_engine_t *)NET;

    memset(engine, NULL, sizeof(tlsa98_engine_t));

    engine->signature = TLSA98_ENGINE_SIGNATURE;
    engine->version = (version_t *)malloc(sizeof(version_t));
    {
        version_t *version = engine->version;

        version->major = TLSA98_ENGINE_VERSION_MAJOR;
        version->minor = TLSA98_ENGINE_VERSION_MINOR;
        version->build = TLSA98_ENGINE_VERSION_BUILD;
        version->revision = TLSA98_ENGINE_VERSION_REVISION;
    }

    initializeServiceProvider();
}

static void initializeServices()
{
}

static void initializeDIVCallbacks()
{
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();

    initializeEngineInterface();
    initializeServices();
    initializeDIVCallbacks();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Export here all services to DIV language:
    // ...
}

void __export divend(COMMON_PARAMS)
{
    // Terminate here services:
    // ...
}