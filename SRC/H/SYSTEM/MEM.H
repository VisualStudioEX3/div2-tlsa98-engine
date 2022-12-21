//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory service.
*/

#ifndef __SYSTEM_MEMORY_SERVICE
#define __SYSTEM_MEMORY_SERVICE

#include "BOOL.H"

/// @brief Memory service id.
#define MEM_SERVICE     1020

/// @brief BYTE type in DIV Games Studio 2.
typedef unsigned char byte;

typedef void  (*mem_clear_f)        (void* ptr, size_t size);
typedef void* (*mem_calloc_f)       (size_t size);
typedef void* (*mem_copy_f)         (const void* ptr, size_t size);
typedef void  (*mem_copy_to_f)      (const void* from, void* to, size_t size);
typedef bool  (*mem_equals_f)       (const void* ptr1, const void* ptr2, size_t size);

/// @brief Memory service interface.
typedef struct mem_service_t
{
    /// @brief Sets all bytes to null.
    /// @param ptr Pointer to a memory region.
    /// @param size Size of the memory region.
    /// @remarks This function not releases allocated memory regions. Use #free instead.
    mem_clear_f clear;

    /// @brief Allocates a memory region and filled with null values.
    /// @param size Size of the memory region to allocate.
    /// @return Returns the pointer to the allocated memory region, #DIV::NULL otherwise.
    mem_calloc_f calloc;

    /// @brief Creates a copy of the region memory.
    /// @param ptr Pointer to the memory region to copy.
    /// @param size Size of the memory region to copy.
    /// @return Returns a new pointer to the copied memory region, #DIV::NULL otherwise.
    mem_copy_f copy;

    /// @brief Copies a block of bytes to another memory region.
    /// @param from Pointer to the memory region from copy the bytes.
    /// @param to Pointer to the memory region to copy the bytes.
    /// @param size Size of the memory region to copy.
    /// @remarks The source memory region keeps the values after the copy.
    /// Also ensure that both memory regions has the same size, otherwise, will overwrite 
    /// data of other memory regions.
    mem_copy_to_f copyTo;

    /// @brief Determine if both memory regions are equals.
    /// @param ptr1 First pointer.
    /// @param ptr2 Second pointer.
    /// @param size Size of the memory region. This value is for both pointers.
    /// @returns Returns #SYSTEM::true if all bytes of both memory regions are equals, 
    /// #SYSTEM::false otherwise.
    /// @remarks Ensure that both memory regions has the same size, otherwise, the comparison
    /// may return wrong results.
    mem_equals_f equals;
} mem_service_t;

/// @brief Register and initializes the service.
void registerMemService();

#endif