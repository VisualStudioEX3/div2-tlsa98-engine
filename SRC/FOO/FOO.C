//! FOO.DLL - Test library.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test library to perform tests over the engine libraries.
*/

#include "H/FOO.H"

#define TLSA_ENGINE_MAJOR_VERSION 0
#define TLSA_ENGINE_MINOR_VERSION 1

static const logger_service_t *logger;

static foo_service_t service;

static const string getHelloWorldMessage()
{
    return "Hello, World!";
}

static void div_getHelloWorldMessage()
{
    string arg;

    foo_service_t *fooService = (foo_service_t *)getService(FOO_SERVICE);

    assert(fooService != NULL);
    assert(fooService->getHelloWorldMessage != NULL);

    arg = div_readStringParameter();

    // Copy string value returned by C functon to DIV argument address:
    strcpy(arg, fooService->getHelloWorldMessage());

    div_return(0);

    logger->info("div_getHelloWorldMessage() called.");
}

void registerFooService()
{
    logger->debug("Initializating FOO service...");

    service.getHelloWorldMessage = getHelloWorldMessage;
    assert(addService(FOO_SERVICE, &service));

    logger->debug("FOO service initialized.");
}

void exportFooService(void (*COM_export)(char *name, void *obj, int nparms))
{
    COM_export("getHelloWorldMessage", div_getHelloWorldMessage, 1);
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT(); // Required to get TLSA98_ENGINE_ADDRESS pointer address from _net struct.

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
