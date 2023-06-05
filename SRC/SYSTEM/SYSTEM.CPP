//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    System library entry point.
*/

#include "..\H\SYSTEM.H"
#include "..\H\SYSTEM\SERVICES.H"

static void initialize()
{
    initializeServiceProvider();

    // TODO: Initialize here the all internal systems and services.
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    initialize();
    // Register DIV callbacks.
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // TODO: Export here all services to DIV runtime.
}

void __export divend(COMMON_PARAMS)
{
    // TODO: Terminate here services.
}