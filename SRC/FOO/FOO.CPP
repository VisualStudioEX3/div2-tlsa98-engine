//! FOO.DLL - Test library.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test library to perform tests over the engine libraries.
*/

#include <assert.h>
#include "../H/FOO.H"
#include "../H/DIV2.H"
#include "../H/SYSTEM/SERVICES/LOGGER.H"

static const int TLSA_ENGINE_MAJOR_VERSION = 0;
static const int TLSA_ENGINE_MINOR_VERSION = 1;
static const string HELLO_WORLD_MESSAGE = "Hello, World!";

static foo_service_t service;
static logger_service_t *logger;

static const string getHelloWorldMessage()
{
    return HELLO_WORLD_MESSAGE;
}

static void div_getHelloWorldMessage()
{
    foo_service_t *fooService = (foo_service_t *)getService(FOO_SERVICE);

    assert(fooService != NULL);
    assert(fooService->getHelloWorldMessage != NULL);

    string arg = engine->div2API->getParameterAsString();

    strcpy(arg, fooService->getHelloWorldMessage());

    engine->div2API->setReturnValue(0);

    logger->info("div_getHelloWorldMessage() called.");
}

void registerFooService()
{
    logger->debug("Initializating FOO service...");

    service.getHelloWorldMessage = getHelloWorldMessage;

    int result = engine->services->registerService(FOO_SERVICE, &service);

    assert(result == RESULT_OK);

    logger->debug("FOO service initialized.");
}

void exportFooService(void (*COM_export)(char *name, void *obj, int nparms))
{
    COM_export("getHelloWorldMessage", div_getHelloWorldMessage, 1);
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT(); // Required to get TLSA98_ENGINE_ADDRESS pointer address from _net struct.
    engine = (tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;
    logger = (logger_service_t *)getService(LOGGER_SERVICE);

    logger->debug("Initializing FOO.DLL...");

    // TODO: Implement own assert to allow custom assertion messages, outputs like the future
    // built-in game console or error reporter, and termination action (end program or
    // terminate current level and return to game console).
    assert(TLSA98_ENGINE_SIGNATURE_EQUALS);
    assert(TLSA98_ENGINE_VERSION_MAJOR_OR_EQUALS(TLSA_ENGINE_MAJOR_VERSION, TLSA_ENGINE_MINOR_VERSION));

    // Register services:
    registerFooService();

    // Register DIV callbacks:
    // ...

    logger->debug("FOO.DLL initialized.");
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Export here all services to DIV language:
    exportFooService(COM_export);

    // BUG: FileLogger service crash program when you try to log any message from here or any child
    // function call from here. Because SYSTEM.DLL should implements in a near future a service to
    // register there the functions to DIV language, this bug seems to be avoided, because divlibrary()
    // is not required in the child libraries, only in SYSTEM.DLL, where this bug not ocurr.
}

void __export divend(COMMON_PARAMS)
{
    logger->debug("Terminating FOO.DLL...");

    // Terminate here services:
    // ...

    logger->debug("FOO.DLL terminated.");
}
