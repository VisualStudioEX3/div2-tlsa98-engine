//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Main engine file and access to all core services.
*/

#include <string.h>
#include "..\H\SYSTEM.H"
#include "MATH\DIVFNEXP.H"

static void initialize()
{
    initializeServiceProvider();
    registerDIVFunctionExporterService();
    registerMathService();
}

void __export divlibrary(LIBRARY_PARAMS)
{
    // Register DIV functions.
    exportMathService(LIBRARY_PARAMS);
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    initialize();
    // Register DIV callbacks.
}

void __export divend(COMMON_PARAMS)
{
    // Terminate services.
}