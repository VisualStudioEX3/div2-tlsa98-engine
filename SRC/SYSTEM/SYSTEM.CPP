//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Main engine file and access to all core services.
*/

#include "..\H\SYSTEM.H"
#include "DEBUG\DEBUG.H"

static void initialize()
{
    initializeDebugSystem();
    initializeServiceProvider();

    registerMemService();
    registerStringService();
    registerDIVFunctionExporterService();
    registerMathService();
}

void __export divmain(COMMON_PARAMS)
{
    GLOBAL_IMPORT();
    initialize();
    // Register DIV callbacks.
}

void __export divlibrary(LIBRARY_PARAMS)
{
    div_function_exporter_service_t* service = 
        (div_function_exporter_service_t*)getService(DIV_FUNCTION_EXPORTER_SERVICE);

    exportMathService(service);

    service->commit(COM_export);
}

void __export divend(COMMON_PARAMS)
{
    // Terminate services.
    terminateDebugSystem();
}