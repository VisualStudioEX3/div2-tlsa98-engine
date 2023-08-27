//! FOO.DLL - Test library.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test library to perform tests over the engine libraries.
*/

#include <assert.h>
#include "..\H\FOO.H"
#include "..\H\DIV2.H"

const int TLSA_ENGINE_MAJOR_VERSION = 0;
const int TLSA_ENGINE_MINOR_VERSION = 1;
const string HELLO_WORLD_MESSAGE = "Hello, World!";

foo_service_t service;

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

    engine->fileLogger->log("div_getHelloWorldMessage() called.");
}

void registerFooService()
{
    engine->fileLogger->log("Initializating FOO service...");

    service.getHelloWorldMessage = getHelloWorldMessage;

    int result = engine->services->registerService(FOO_SERVICE, &service);

    assert(result == RESULT_OK);

    engine->fileLogger->log("FOO service initialized.");
}

void exportFooService(void (*COM_export)(char *name, void *obj, int nparms))
{
    COM_export("getHelloWorldMessage", div_getHelloWorldMessage, 1);
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT(); // Required to get TLSA98_ENGINE_ADDRESS pointer address from _net struct.
    engine = (tlsa98_engine_t *)TLSA98_ENGINE_ADDRESS;

    engine->fileLogger->log("Initializing FOO.DLL...");

    // TODO: Implement own assert to allow custom assertion messages, outputs like the future 
    // built-in game console or error reporter, and termination action (end program or 
    // terminate current level and return to game console).
    assert(TLSA98_ENGINE_SIGNATURE_EQUALS);
    assert(TLSA98_ENGINE_VERSION_MAJOR_OR_EQUALS(TLSA_ENGINE_MAJOR_VERSION, TLSA_ENGINE_MINOR_VERSION));

    // Register services:
    registerFooService();

    // Register DIV callbacks:
    // ...

    engine->fileLogger->log("FOO.DLL initialized.");
    engine->fileLogger->logSingleLine();
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
    engine->fileLogger->log("Terminating FOO.DLL...");

    // Terminate here services:
    // ...

    engine->fileLogger->log("FOO.DLL terminated.");
}