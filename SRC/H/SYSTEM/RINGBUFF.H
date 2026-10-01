//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Ring buffer.
*/

#ifndef __SYSTEM_DLL_RING_BUFFER_H_
#define __SYSTEM_DLL_RING_BUFFER_H_

#include "GLOBALS.H"
#include "LIST.H"

/**
 * @brief Ring buffer.
 * @remarks Represents a buffer with fixed capacity as if it were connected
 * end-to-end. The buffer allocated all memory aligned since is created used to
 * store each item data instead of a single pointer to source, in fact, the
 * buffer works as a data container, like an array.
 */
typedef struct
{
    /**
     * @brief Buffer capacity.
     * @return Returns the max number of elements that can storage the buffer.
     */
    list_t *list;

    /**
     * @brief Index in the ring buffer to create the next item.
     * @return Returns the index in the ring buffer to create the next item.
     */
    uint insertIndex;
} ring_buffer_t;

/**
 * @brief Callback predicate to define an action to execute before the item is created.
 * @param buffer Pointer to the ring buffer.
 * @param args Callback arguments.
 *
 * @return bool - Returns #true to create the item, #false otherwise.
 */
typedef bool (*create_ring_buffer_item_callback)(ring_buffer_t *, va_list);

/**
 * @brief Callback delegate to define an action to execute for each item in the ring
 * buffer.
 * @param index Index of the item.
 * @param item Pointer to the item.
 * @param args Callback arguments.
 */
typedef void (*foreach_ring_buffer_item_callback)(int, void *, va_list);

/**
 * @brief Gets the max number of items that can be stored in the ring buffer.
 * @param buffer Pointer to the ring buffer.
 * @return Returns the capacity or #RESULT_ERROR if the buffer is #NULL.
 */
int getRingBufferCapacity(const ring_buffer_t *buffer);

/**
 * @brief Gets the number of items stored in the ring buffer.
 * @param buffer Pointer to the ring buffer.
 * @return Returns the number of items stored or #RESULT_ERROR if the
 * ring buffer is #NULL.
 */
int getRingBufferCount(const ring_buffer_t *buffer);

/**
 * @brief Gets if the ring buffer is empty.
 * @param buffer Pointer to the ring buffer.
 * @return Returns #true if the ring buffer is empty, #false otherwise.
 */
bool isRingBufferEmpty(const ring_buffer_t *buffer);

/**
 * @brief Gets if the ring buffer is full.
 * @param buffer Pointer to the ring buffer.
 * @return Returns #true if the ring buffer is full, #false otherwise.
 */
bool isRingBufferFull(const ring_buffer_t *buffer);

/**
 * @brief Creates a new ring buffer.
 * @param capacity Max number of items that can be stored.
 * @param itemSize The size in bytes of the item type.
 * @return Returns the pointer to the new ring buffer, or #NULL if the
 * capacity and/or itemSize is zero or below.
 */
ring_buffer_t *createRingBuffer(uint capacity, size_t itemSize);

/**
 * @brief Clears the content of the ring buffer.
 * @param buffer - Pointer to the ring buffer.
 * @remarks This function reset the ring buffer counter to zero allowing to
 * reuse the ring buffer for store new items. This function not free the memory
 * used by the ring buffer.
 */
void clearRingBuffer(ring_buffer_t *buffer);

/**
 * @brief Clears the content of the ring buffer and execute a callback on each item
 * of the ring buffer.
 * @param buffer Pointer to the ring buffer.
 * @param onItem Callback to execute on each item.
 * @remarks Like the clearRingBuffer function, this function only reset the counter
 * to zero, but allow to execute a callback on each item in the ring buffer (e.g.
 * free memory of an inner pointer).
 */
void clearRingBufferEx(ring_buffer_t *buffer, foreach_ring_buffer_item_callback onItem);

/**
 * @brief Destroys the ring buffer.
 * @param list Pointer to the ring buffer.
 * @remarks This function free the memory ocuped by the ring buffer and by the
 * pointer itself.
 */
void destroyRingBuffer(ring_buffer_t *buffer);

/**
 * @brief Destroys the ring buffer and execute a callback on each item of the ring
 * buffer.
 * @param buffer Pointer to the ring buffer.
 * @param onItem Callback to execute on each item.
 * @remarks Like the destroyRingBuffer function, this function free the mmeory ocuped
 * by the ring buffer and by the pointer itself, and allow to execute first a clean up
 * operation on each item, like in clearRingBufferEx function.
 */
void destroyRingBufferEx(ring_buffer_t *buffer, foreach_ring_buffer_item_callback onItem);

/**
 * @brief Creates a new item in the ring buffer and moves the cursor to the next
 * position.
 * @param buffer Pointer to the ring buffer.
 * @returns Returns the pointer to the new item in the ring buffer, or #NULL if or
 * if the ring buffer is #NULL.
 * @remarks This function not allocated new memory for the item, only point to the
 * next available position in the reserved memory.
 */
void *createRingBufferItem(ring_buffer_t *buffer);

/**
 * @brief Creates a new item in the ring buffer and moves the cursor to the next
 * position, with condition callback.
 * @param buffer Pointer to the ring buffer.
 * @param onBeforeCreate Function callback that define a condition to satisfy to
 * create the item.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the new item in the ring buffer, or #NULL if
 * onBeforeCreate function callback returns #false or if the list is #NULL.
 * @remarks The onBeforeCreate function must be return #true to able create the new
 * item. You can use this function to implement behaviours like a dictionary
 * item key check or another required condition to satify before create the item.
 *
 * Like the createRingBufferItem function, this function not allocated new memory for
 * the item, only point to the next available position in the reserved memory.
 */
void *createRingBufferItemEx(ring_buffer_t *buffer, create_ring_buffer_item_callback onBeforeCreate, ...);

/**
 * @brief Creates a new item in the ring buffer and moves the cursor to the next,
 * with condition callback (Variadic version).
 * @param buffer Pointer to the ring buffer.
 * @param onBeforeCreate Function callback that define a condition to satisfy to
 * create the item.
 * @param args List of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the new item in the ring buffer, or #NULL if
 * onBeforeCreate function callback returns #false or if the list is #NULL.
 * @remarks The onBeforeCreate function must be return #true to able create the new
 * item. You can use this function to implement behaviours like a dictionary
 * item key check or another required condition to satify before create the item.
 *
 * Like the createRingBufferItem function, this function not allocated new memory for
 * the item, only point to the next available position in the reserved memory.
 */
void *createRingBufferItemExArgs(ring_buffer_t *buffer, create_ring_buffer_item_callback onBeforeCreate, va_list args);

/**
 * @brief Gets the pointer to an item in the ring buffer.
 * @param buffer Pointer to a ring buffer.
 * @param index Index of the item. Must be a number between 0 and below of ring buffer
 * count.
 * @returns Returns the pointer to the new item in the ring buffer, or #NULL if the
 * index is over the ring buffer count or capacity or below zero, or if the list is
 * #NULL.
 */
void *getRingBufferItem(const ring_buffer_t *buffer, int index);

/**
 * @brief Loops the entire ring buffer and execute a callback in each item.
 * @param buffer Pointer to the ring buffer.
 * @param onItem Callback to execute in each item.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @remarks Use this function execute a callback on each item in the ring buffer
 * sequentially.
 */
void forEachRingBuffer(const ring_buffer_t *buffer, foreach_ring_buffer_item_callback onItem, ...);

/**
 * @brief Loops the entire ring buffer and execute a callback in each item (Variadic
 * version).
 * @param buffer Pointer to the ring buffer.
 * @param onItem Callback to execute in each item.
 * @param args List of arguments to use as extra parameters in the callback.
 * @remarks Use this function execute a callback on each item in the ring buffer
 * sequentially.
 */
void forEachRingBufferArgs(const ring_buffer_t *buffer, foreach_ring_buffer_item_callback onItem, va_list args);
#endif
