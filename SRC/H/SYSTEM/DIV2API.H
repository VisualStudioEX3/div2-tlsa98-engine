//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio 2 API abstraction.
*/

#ifndef __SYSTEM_DLL_DIV2_API_H_
#define __SYSTEM_DLL_DIV2_API_H_

#include <stdio.h>

typedef int *(*div2_memory_array_f)();
typedef void *(*div2_malloc_f)(size_t);
typedef void (*div2_free_f)(void *);
typedef int (*div2_get_int_parameter_f)();
typedef char *(*div2_get_string_parameter_f)();
typedef void (*div2_return_value_f)(int);
typedef FILE *(*div2_fopen_f)(char *, char *);
typedef void (*div2_fclose_f)(FILE *);

/// @brief DIV Games Studio 2 API abstraction.
/// @remarks DIV2.H header (the original DIV.H file) has member declarations that provokes
/// linker warning 1027, redefinition of member ignored, when you include the header in two 
/// or more files. This abstraction allows to point to required functions and macros from
/// DIV header from SYSTEM library, avoiding the requirement of include DIV2.H on another
/// files.
typedef struct
{
    /// @brief Gets pointer to the DIV program memory.
    /// @return Returns an integer pointer to program memory.
    /// @remarks DIV program memory is defined as an integer array.
    div2_memory_array_f getProgramMemory;

    /// @brief Allocates memory.
    /// @param size Size of the memory region to allocate.
    /// @return Returns the pointer to the new allocated memory region.
    /// @remarks DIV Games Studio runtime has his own malloc() implementation to manage his
    /// memory allocations. If you try to use the standard malloc() the program starts to
    /// generate memory corruption and even crashes.
    div2_malloc_f allocateMemory;

    /// @brief Releases allocated memory.
    /// @param ptr Pointer of the memory region to release.
    /// @remarks DIV Games Studio runtime has his own free() implementation to manage his
    /// memory deallocations. If you try to use the standard free() the program starts to
    /// generate memory corruption and even crashes.
    div2_free_f freeMemory;

    /// @brief Gets next parameter as integer value from an exported DIV function.
    /// @return Returns int value.
    /// @remarks Remember that parameters are readed from a stack, from last to first.
    div2_get_int_parameter_f getParameterAsInteger;

    /// @brief Gets next parameter as string pointer from an exported DIV function.
    /// @return Returns char pointer.
    /// @remarks Remember that parameters are readed from a stack, from last to first.
    div2_get_string_parameter_f getParameterAsString;

    /// @brief Finalizes and setup the return value of an exported DIV function.
    /// @param value Integer value to return.
    /// @remarks This functions always must be called at the end of an exported function to 
    /// DIV program.
    div2_return_value_f setReturnValue;

    /// @brief Opens or creates a file.
    /// @param mode File access mode. See standard fopen documentation to know the avaiable 
    /// modes: https://cplusplus.com/reference/cstdio/fopen/.
    /// @return Returns the pointer to the opened file, #NULL otherwise.
    /// @remarks DIV Games Studio runtime has his own fopen() implementation to manage his
    /// file open operations. If you try to use the standard fopen() the program starts to
    /// generate memory corruption and even crashes.
    div2_fopen_f openFile;
    
    /// @brief fclose() alias to DIV implementation.
    /// @param file The pointer to file to close.
    /// @remarks DIV Games Studio runtime has his own fclose() implementation to manage his
    /// file close operations. If you try to use the standard fclose() the program starts to
    /// generate memory corruption and even crashes.
    div2_fclose_f closeFile;
} div2_api_t;

#endif