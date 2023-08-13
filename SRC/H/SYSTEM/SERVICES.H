//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Service provider.
*/

#ifndef __SYSTEM_DLL_SERVICES_H_
#define __SYSTEM_DLL_SERVICES_H_

#include "GLOBALS.H"

typedef struct
{
    service_id_t id;
    void *service;
} service_t;

/// @brief Initializes the service provider.
void initializeServiceProvider();

#endif