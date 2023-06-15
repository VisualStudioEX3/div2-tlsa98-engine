//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test service.
*/

#ifndef __SYSTEM_FOO_SERVICE_
#define __SYSTEM_FOO_SERVICE_

#include "GLOBALS.H"

#define FOO_SERVICE 0x00464F4F

typedef string (*foo_bar_f)();

/// @brief Test service.
typedef struct
{
    /// @brief Test method.
    foo_bar_f foo;
} foo_service_t;

/// @brief Register test foo service.
void registerFooService();

/// @brief Register test foo function in DIV language.
void registerFooService(void (*COM_export)(char *name,void *obj,int nparms));

#endif