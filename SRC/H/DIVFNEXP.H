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
#define DIV_FUNCTION_EXPORTER_SERVICE       100

typedef void (*div_function_export_f)   (char*, void*, int);
typedef void (*divfnexp_register_f)     (string, uint, void*);
typedef void (*divfnexp_commit_f)       (div_function_export_f);

/// @brief DIV Games Studio function exporter service.
typedef struct div_function_exporter_service_t
{
    /// @brief Registers a new function to export for DIV Games Studio language.
    /// @param name Function name in DIV Games Studio language. Avoid using DIV Games Studio 
    /// language reserved names.
    /// @param params Number of parameters that function expects.
    /// @param function Pointer to the native function to export. All exported functions must 
    /// be parameterless void functions, and use #DIV::retval macro to return an integer 
    /// value.
    /// @return Returns #SYSTEM::false if the export queue is full, #SYSTEM::true otherwise.
    /// @remarks Use this function to register the DIV Games Studio function in the export 
    /// queue. After register all functions, call #div_function_exporter_service_t::commit
    /// function to export and validate them.
    divfnexp_register_f registerFunction;

    /// @brief Commits the all new registered functions to DIV Games Studio runtime.
    /// @param comExport Pointer to the DIV Games Studio #DIV::COM_export API function.
    /// Simply pass #DIV::COM_export as value when call it from #SYSTEM::div_library.
    /// @remarks This functions exports all new registered functions to DIV Games Studio
    /// runtime. The process check name collisions and report these errors.
    /// Call this function one time per DLL.
    divfnexp_commit_f commit;
} div_function_exporter_service_t;

/// @brief Register and initializes the service.
void registerDIVFunctionExporterService();

#endif