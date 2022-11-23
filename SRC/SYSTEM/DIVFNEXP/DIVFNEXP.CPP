//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio function exporter service.
*/

#include <string.h>
#include "..\..\H\DIVFNEXP.H"
#include "DIV2RESN.H" // DIV Games Studio language reserved names list.

const string VALID_CHARS = "abcdefghijklmnopqrstuvwxyz_";
const int MAX_REGISTERED_FUNCTIONS = 32;

typedef struct divfnexp_function_t
{
    string name;
    uint params;
    div_function_template_f function;
} divfnexp_function_t;

div_function_exporter_service_t* service;
string_service_t* stringService;
divfnexp_function_t exportQueue[MAX_REGISTERED_FUNCTIONS];
int queueIndex;

static void clearExportQueue()
{
    const size_t QUEUE_SIZE = sizeof(divfnexp_function_t) * MAX_REGISTERED_FUNCTIONS;

    memset(exportQueue, NULL, QUEUE_SIZE);
    queueIndex = 0;
}

static void registerFunction(string name, uint params, div_function_template_f function)
{
    if (queueIndex < MAX_REGISTERED_FUNCTIONS)
    {
        divfnexp_function_t* queueItem = &exportQueue[queueIndex];

        queueItem->name     = stringService->toLower(name);
        queueItem->params   = params;
        queueItem->function = function;

        queueIndex++;
    }

    // TODO: Use future error reporter service to log the full queue error.
}

static bool isFullUnderscoreName(const string name)
{
    return stringService->all(name, '_');

    // TODO: Use future error reporter service to log this error.
}

static bool containIllegalChars(const string name)
{
    for (char* chr = name; chr != '\0'; chr++)
        if (!stringService->any(chr, VALID_CHARS))
            return true;
            // TODO: Use future error reporter service to log this error.

    return false;

}

static bool isReservedName(const string name)
{
    for (int i = 0; i < DIV_LANGUAGE_RESERVED_NAMES_COUNT; i++)
        if (stringService->equals(name, DIV2_LANGUAGE_RESERVED_NAMES[i]))
            return true;
            // TODO: Use future error reporter service to log this error.

    return false;
}

static bool validateName(const string name)
{
    return !stringService->isEmpty(name) 
        && !containIllegalChars(name) 
        && !isFullUnderscoreName(name) 
        && !isReservedName(name);
}

static bool validateFunction(divfnexp_function_t* f)
{
    return validateName(f->name)
        && f->function != NULL;

    // TODO: Use future error reporter service to log this error.
}

static void exportFunctionToDIV(divfnexp_function_t* f, div_function_com_export_f comExport)
{
    comExport(f->name, f->function, f->params);
}

static void commit(div_function_com_export_f comExport)
{
    for (int i = 0; i < MAX_REGISTERED_FUNCTIONS; i++)
    {
        divfnexp_function_t* queueItem = &exportQueue[i];

        if (validateFunction(queueItem))
            exportFunctionToDIV(queueItem, comExport);
    }

    clearExportQueue();
}

static void createService()
{
    size_t serviceSize = sizeof(div_function_exporter_service_t);

    service = (div_function_exporter_service_t*)malloc(serviceSize);
    service->registerFunction   = registerFunction;
    service->commit             = commit;

    clearExportQueue();
}

void registerDIVFunctionExporterService()
{
    stringService = (string_service_t*)getService(STRING_SERVICE);

    createService();
    registerService(DIV_FUNCTION_EXPORTER_SERVICE, service);
}