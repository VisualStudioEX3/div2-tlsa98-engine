//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio function exporter service.
*/

#ifndef __SYSTEM_DIV_FUNCTION_EXPORTER_SERVICE_DLL_
#define __SYSTEM_DIV_FUNCTION_EXPORTER_SERVICE_DLL_

#include "SYSTEM.H"

/// @brief DIV Games Studio function exporter service id.
#define DIV_FUNCTION_EXPORTER_SERVICE   1001

typedef void (*divfnexp_register_f) (string, int, void*);
typedef void (*divfnexp_commit_f)   ();

/// @brief DIV Games Studio function exporter service.
typedef struct div_function_exporter_service_t
{
    /// @brief Registers a new function for DIV Games Studio language.
    /// @param name Function name in DIV Games Studio language. Avoid using DIV Games Studio 
    /// language reserved names.
    /// @param params Number of parameters that function expects.
    /// @param function Pointer to the native function to export. All exported functions must 
    /// be return an integer value and be parameterless.
    /// @remarks This funciton only register the exported function. To complete and validate
    /// all registered functions, remember to call #div_function_exporter_service_t::commit 
    /// function.
    divfnexp_register_f registerFunction;

    /// @brief Commits the all new registered functions to DIV Games Studio runtime.
    /// @remarks This functions exports all new registered functions to DIV Games Studio
    /// runtime. The process check name collisions and report these errors.
    /// Call this function one time per DLL.
    divfnexp_commit_f commit;
} div_function_exporter_service_t;

/// @brief Register and initializes the service.
void registerDIVFunctionExporterService();

#endif