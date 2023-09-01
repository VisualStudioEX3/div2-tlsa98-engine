//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System library entry point.
*/

#include "..\H\SYSTEM.H"
#include "..\H\SYSTEM\SERVICES.H"
#include "..\H\DIV2.H"

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

static void initializeDIV2APIService()
{
    logMessage("Initializing DIV2 API service...");

    engine->div2API = (div2_api_t *)div_malloc(sizeof(div2_api_t));

    engine->div2API->getProgramMemory = div_getProgramMemoryArray;
    engine->div2API->allocateMemory = div_malloc;
    engine->div2API->freeMemory = div_free;
    engine->div2API->getParameterAsInteger = div_getParameterAsInteger;
    engine->div2API->getParameterAsString = div_getParameterAsString;
    engine->div2API->setReturnValue = div_returnValue;
    engine->div2API->openFile = div_fopen;
    engine->div2API->closeFile = div_fclose;

    logMessage("DIV2 API service initialized.");
}

static void initializeFileLoggerService()
{
    logMessage("Initializing File Logger service...");

    engine->fileLogger = (file_logger_service_t *)malloc(sizeof(file_logger_service_t));
    {
        file_logger_service_t *fileLogger = engine->fileLogger;

        fileLogger->log = logMessage;
        fileLogger->logArgs = logMessageArgs;
        fileLogger->logSingleLine = logSingleSeparator;
        fileLogger->logDoubleLine = logDoubleSeparator;
    }

    logMessage("File Logger service intialized.");
}

static void initializeEngineInterface()
{
    logMessage("Initializing engine interface...");

    memset(engine, NULL, sizeof(tlsa98_engine_t));

    engine->signature = TLSA98_ENGINE_SIGNATURE;
    logMessage("Engine signature: %i (0x%x)", engine->signature, engine->signature);

    engine->version = (version_t *)div_malloc(sizeof(version_t));
    {
        version_t *version = engine->version;

        version->major = TLSA98_ENGINE_VERSION_MAJOR;
        version->minor = TLSA98_ENGINE_VERSION_MINOR;
        version->revision = TLSA98_ENGINE_VERSION_REVISION;

        logMessage("Engine version: %i.%i.%i", version->major, version->minor, version->revision);
    }

    initializeDIV2APIService();
    initializeFileLoggerService();
    initializeServiceProvider();

    logMessage("Engine interface initialized.");
    logSingleSeparator();
}

static void initializeServices()
{
    logMessage("Initializing core services...");

    registerMemService();
    registerStringService();
    registerDateTimeService();

    logMessage("Core services initialized.");
    logSingleSeparator();
}

static void initializeDIVCallbacks()
{
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    engine = (tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;

    openLogFile(div_fopen);

    initializeEngineInterface();
    initializeServices();
    initializeDIVCallbacks();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Export here all services to DIV language:
    // ...

    logMessage("Engine initialized.");
    logDoubleSeparator();
}

void __export divend(COMMON_PARAMS)
{
    // FYI: Testing FOO.DLL we get the DIV2 runtime perform the divend calls in inverse order
    // of the libraries are initialized. For the "terminating engine" logs and actions, maybe
    // is a good idea to create an event of "engine termination" to do this.
    logDoubleSeparator();
    logMessage("Terminating engine...");

    // Terminate here services:
    // ...

    logMessage("Engine terminated.");
    closeLogFile(div_fclose);
}