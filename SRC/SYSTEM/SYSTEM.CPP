//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine base members and shared entry point to service provider.
*/

#include "SYSTEM.H"

const void initialize()
{
    initializeServiceContainer();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Register DIV functions.
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    initialize(); // Initialize services.
    // Register DIV callbacks.
}

void __export divend(COMMON_PARAMS)
{
    // Terminate services.
}
