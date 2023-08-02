//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System library entry point.
*/

#include "..\H\SYSTEM.H"
#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\DIV2.H"

static void initializeDIV2APIService()
{
    engine->div2API = (div2_api_t *)div_malloc(sizeof(div2_api_t));

    div2_api_t *div2 = engine->div2API;

    div2->memory = (div2_api_memory_t *)div_malloc(sizeof(div2_api_memory_t));

    div2_api_memory_t *memory = div2->memory;
    {
        memory->session = mem;
        memory->_malloc = div_malloc;
        memory->_free = div_free;
    }

    div2->fileSystem = (div2_api_file_system_t *)malloc(sizeof(div2_api_file_system_t));

    div2_api_file_system_t *fileSystem = div2->fileSystem;
    {
        fileSystem->_fopen = div_fopen;
        fileSystem->_fclose = div_fclose;
    }
}

static void initializeEngineInterface()
{
    memset(engine, NULL, sizeof(tlsa98_engine_t));

    engine->signature = TLSA98_ENGINE_SIGNATURE;
    engine->version = (version_t *)div_malloc(sizeof(version_t));
    {
        version_t *version = engine->version;

        version->major = TLSA98_ENGINE_VERSION_MAJOR;
        version->minor = TLSA98_ENGINE_VERSION_MINOR;
        version->build = TLSA98_ENGINE_VERSION_BUILD;
        version->revision = TLSA98_ENGINE_VERSION_REVISION;
    }

    initializeDIV2APIService();
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
    engine = (tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;

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