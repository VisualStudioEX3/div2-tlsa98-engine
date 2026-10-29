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

static int *div_getProgramMemoryArray()
{
    return mem;
}

static int div_getParameterAsInteger()
{
    return getparm();
}

static string div_getParameterAsString()
{
    return (char *)(&mem[text_offset + div_getParameterAsInteger()]);
}

static void div_returnValue(int value)
{
    retval(value);
}

static void setEngineSignature()
{
    engine->signature = TLSA98_ENGINE_SIGNATURE;

    logMessage(LOG_INFO, "Engine signature: 0x%x", engine->signature);
}

static void setEngineVersion()
{
    engine->version = (version_t *)div_malloc(sizeof(version_t));
    {
        version_t *version = engine->version;

        version->major = TLSA98_ENGINE_VERSION_MAJOR;
        version->minor = TLSA98_ENGINE_VERSION_MINOR;
        version->revision = TLSA98_ENGINE_VERSION_REVISION;
        version->reserved = 0;

        logMessage(LOG_INFO, "Engine version: %i.%i.%i", version->major, version->minor, version->revision);
    }
}

static void registerDIV2API()
{
    engine->div2API = (div2_api_t *)div_malloc(sizeof(div2_api_t));

    engine->div2API->getProgramMemory = div_getProgramMemoryArray;
    engine->div2API->allocateMemory = div_malloc;
    engine->div2API->freeMemory = div_free;
    engine->div2API->getParameterAsInteger = div_getParameterAsInteger;
    engine->div2API->getParameterAsString = div_getParameterAsString;
    engine->div2API->setReturnValue = div_returnValue;
    engine->div2API->openFile = div_fopen;
    engine->div2API->closeFile = div_fclose;
}

static void initializeEngineInterface()
{
    logMessage(LOG_DEBUG, "Initializing engine interface...");

    engine = (tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;

    memset(engine, 0, sizeof(tlsa98_engine_t));

    setEngineSignature();
    setEngineVersion();
    registerDIV2API();
    initializeServiceProvider();

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
