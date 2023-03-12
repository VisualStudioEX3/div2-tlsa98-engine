//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Memory functions.
*/

#ifndef __SYSTEM_MEM_H_
#define __SYSTEM_MEM_H_

#include "..\..\H\GLOBAL.H"

/// @brief Sets all bytes to null.
/// @param ptr Pointer to a memory region.
/// @param size Size of the memory region.
/// @remarks This function not releases allocated memory regions. Use #free instead.
void memoryClear(void* ptr, size_t size);

/// @brief Allocates a memory region and filled with null values.
/// @param size Size of the memory region to allocate.
/// @return Returns the pointer to the allocated memory region, #DIV::NULL otherwise.
void* memoryCalloc(size_t size);

/// @brief Reallocates a memory region.
/// @param ptr Pointer to a memory region.
/// @param size New size of the memory region.
/// @param useCalloc Use #MEM::memoryCalloc function instead of #GLOBAL::malloc.
/// @return Returns the pointer to the reallocated memory region, #DIV::NULL otherwise.
void* memoryRealloc(void* ptr, size_t size, bool useCalloc);

/// @brief Creates a copy of the region memory.
/// @param ptr Pointer to the memory region to copy.
/// @param size Size of the memory region to copy.
/// @return Returns a new pointer to the copied memory region, #DIV::NULL otherwise.
void* memoryCopy(const void* ptr, size_t size);

/// @brief Copies a block of bytes to another memory region.
/// @param from Pointer to the memory region from copy the bytes.
/// @param to Pointer to the memory region to copy the bytes.
/// @param size Size of the memory region to copy.
/// @remarks The source memory region keeps the values after the copy.
/// Also ensure that both memory regions has the same size, otherwise, will overwrite 
/// data of other memory regions.
void memoryCopyTo(const void* from, void* to, size_t size);

/// @brief Determine if both memory regions are equals.
/// @param ptr1 First pointer.
/// @param ptr2 Second pointer.
/// @param size Size of the memory region. This value is for both pointers.
/// @returns Returns #SYSTEM::true if all bytes of both memory regions are equals, 
/// #SYSTEM::false otherwise.
/// @remarks Ensure that both memory regions has the same size, otherwise, the comparison
/// may return wrong results.
bool memoryEquals(const void* ptr1, const void* ptr2, size_t size);

#endif