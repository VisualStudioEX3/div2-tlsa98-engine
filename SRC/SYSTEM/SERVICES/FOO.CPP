//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test service.
*/

#include <assert.h>
#include "..\..\H\SYSTEM\FOO.H"
#include "..\..\H\SYSTEM\GLOBALS.H"


foo_service_t service;

static string foo()
{
    return "Hello, World!";
}

static void div_foo()
{
    string arg = getstrparm();

    strcpy(arg, foo());

    retval(0);
}

void registerFooService()
{
    service.foo = foo;

    int result = SERVICES->registerService(FOO_SERVICE, &service);

    assert(result == RESULT_OK);
}

void registerFooService(void (*COM_export)(char *name,void *obj,int nparms))
{
    COM_export("foo", div_foo, 1);
}