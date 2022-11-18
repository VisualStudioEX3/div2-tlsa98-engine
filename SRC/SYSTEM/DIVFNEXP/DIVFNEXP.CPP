//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio function exporter service.
*/

#include "..\..\H\DIVFNEXP.H"
#include "DIV2RESN.H" // DIV Games Studio language reserved names list.

const char VALID_CHARS[] = "abcdefghijklmnopqrstuvwxyz_";

typedef struct divfnexp_function_t
{
    string name;
    int params;
    void* function;
} divfnexp_function_t;

div_function_exporter_service_t* service;

static void registerFunction(string name, int params, void* function)
{
    // TODO: Implement register function commit.
}

static void commit()
{
    // TODO: Implement commit logic.
}

void registerDIVFunctionExporterService()
{
    size_t serviceSize = sizeof(div_function_exporter_service_t);

    service = (div_function_exporter_service_t*)malloc(serviceSize);

    service->registerFunction   = registerFunction;
    service->commit             = commit;

    registerService(DIV_FUNCTION_EXPORTER_SERVICE, service);
}