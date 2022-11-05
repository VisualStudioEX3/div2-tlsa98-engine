/* ----------------------------------------------------------------------------
 * SYSTEM.DLL - System library for DIV Games Studio.
 * (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
 * DIV Games Studio 2 (C) Hammer Technologies - 1998, 1999
 * ---------------------------------------------------------------------------- */

#include "SERVICES.H"

typedef struct service_t
{
    service_id_t id;
    void* service;
} service_t;

const int MAX_SERVICES = 64;

service_t* services[MAX_SERVICES];
int count = 0;

static bool isContainerFull()
{
    return count == MAX_SERVICES;
}

static service_t* searchService(service_id_t id)
{
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        service_t* service = services[i];
        
        if (service->id == id)
            return service;
    }

    return NULL;
}

static bool containsService(service_id_t id)
{
    return searchService(id) == NULL;
}

int registerService(service_id_t id, const void* service)
{
    if (isContainerFull())
        return RESULT_ERROR_SERVICE_CONTAINER_IS_FULL;

    if (containsService(id))
        return RESULT_ERROR_SERVICE_ALREADY_REGISTERED;

    service_t* slot = services[count];

    slot->id = id;
    slot->service = (void*)service;

    count++;

    return RESULT_OK;
}

const void* getService(service_id_t id)
{
    return searchService(id);
}

int getServiceCount()
{
    return count;
}
