//! FOO.DLL - Test library.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Test library to perform tests over the engine libraries.
*/

#ifndef __FOO_DLL_H_
#define __FOO_DLL_H_

#include "..\H\SYSTEM.H"

#define FOO_SERVICE 0x00464F4F

typedef const string (*hello_world_f)();

/// @brief Test service.
typedef struct
{
    /// @brief Gets a Hello World message.
    hello_world_f getHelloWorldMessage;
} foo_service_t;

/// @brief Register test foo service.
void registerFooService();

/// @brief Export test foo function in DIV language.
void exportFooService(void (*COM_export)(char *name, void *obj, int nparms));

#endif