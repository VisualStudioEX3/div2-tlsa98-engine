//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio 2 API abstraction.
*/

#include "../H/DIV2.H"
#include "../H/SYSTEM/DIV2API.H"

typedef struct
{
    div2_memory_array_f getProgramMemory;
    div2_malloc_f allocateMemory;
    div2_free_f freeMemory;
    div2_get_int_parameter_f getParameterAsInteger;
    div2_get_string_parameter_f getParameterAsString;
    div2_return_value_f setReturnValue;
    div2_fopen_f openFile;
    div2_fclose_f closeFile;
} _div2_api_t;

static int *div_getProgramMemoryArray()
{
    return mem;
}

static int div_getParameterAsInteger()
{
    return getparm();
}

static char *div_getParameterAsString()
{
    return (char *)(&mem[text_offset + div_getParameterAsInteger()]);
}

static void div_returnValue(int value)
{
    retval(value);
}

div2_api_t *registerDIV2API()
{
    _div2_api_t *api = (_div2_api_t *)div_malloc(sizeof(_div2_api_t));
    {
        api->getProgramMemory = div_getProgramMemoryArray;
        api->allocateMemory = div_malloc;
        api->freeMemory = div_free;
        api->getParameterAsInteger = div_getParameterAsInteger;
        api->getParameterAsString = div_getParameterAsString;
        api->setReturnValue = div_returnValue;
        api->openFile = div_fopen;
        api->closeFile = div_fclose;
    }

    return (div2_api_t *)api;
}
