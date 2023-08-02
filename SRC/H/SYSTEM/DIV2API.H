//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    DIV Games Studio 2 API abstraction.
*/

#ifndef __SYSTEM_DLL_DIV2_API_H_
#define __SYSTEM_DLL_DIV2_API_H_

#include <stdio.h>

typedef void *(*div2_malloc_f)(size_t);
typedef void (*div2_free_f)(void *);

/// @brief DIV Games Studio 2 memory functions and members.
typedef struct
{
    /// @brief Access to DIV Games Studio 2 session memory (the mem[] array).
    int *session;

    /// @brief DIV version of malloc.
    div2_malloc_f _malloc;

    /// @brief DIV version of free.
    div2_free_f _free;
} div2_api_memory_t;

typedef FILE *(*div2_fopen_f)(char *, char *);
typedef void (*div2_fclose_f)(FILE *);

/// @brief DIV Games Studio 2 file system functions and members.
typedef struct
{
    /// @brief DIV version of fopen.
    div2_fopen_f _fopen;

    /// @brief DIV version of fclose.
    div2_fclose_f _fclose;
} div2_api_file_system_t;

/// @brief DIV Games Studio 2 API abstraction.
/// @remarks This implementation not only ease use the DIV2.H code, is also a way to avoid
/// the linker warning 1027 issue with some parts of DIV2.H that always are redefined when you
/// include the header in several files.
typedef struct
{
    /// @brief DIV Games Studio 2 memory functions and members.
    div2_api_memory_t *memory;

    /// @brief DIV Games Studio 2 file system functions and members.
    div2_api_file_system_t *fileSystem;
} div2_api_t;

#endif