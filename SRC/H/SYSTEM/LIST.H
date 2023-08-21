//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Fixed allocated list.

    Source: https://github.com/VisualStudioEX3/div2-framework/blob/master/SHARED/_LIST.H
*/

#ifndef __SYSTEM_DLL_LIST_H_
#define __SYSTEM_DLL_LIST_H_

#include "GLOBALS.H"

/**
 * @brief Fixed typed allocated list.
 * @remarks Represents a list with fixed capacity. The list allocated all memory
 * aligned since is created used to store each item data instead of a single
 * pointer to source, in fact, the list works as a data container, like an array.
 */
typedef struct
{
    /**
     * @brief List capacity.
     * @return Returns the max number of elements that can storage the list.
     */
    uint capacity;

    /**
     * @brief Items count.
     * @return Returns the current number of elements stored in the list.
     */
    uint count;

    /**
     * @brief Item size.
     * @return Returns the size of the each element in the list.
     * @remarks This value is used allocated the memory when the list is created
     * and to read the position of each item in the list using his index.
     */
    size_t itemSize;

    /**
     * @brief Reserved allocated memory to store the items.
     * @return Returns the pointer to the first item in the reserved memory.
     */
    byte *items;
} list_t;

/**
 * @brief Callback predicate to define an action to execute before the item is created.
 * @param list Pointer to the list.
 * @param args Callback arguments.
 *
 * @return bool - Returns #true to create the item, #false otherwise.
 */
typedef bool (*create_list_item_callback)(list_t *, va_list);

/**
 * @brief Callback delegate to define an action to execute for each item in the list.
 * @param index Index of the item.
 * @param item Pointer to the item.
 * @param args Callback arguments.
 */
typedef void (*foreach_list_item_callback)(int, void *, va_list);

/**
 * @brief Callback predicate to define an action to check if an item match with a condition.
 * @param item Pointer to the item.
 * @param args Callback arguments.
 * @return Returns #true if the predicate match an item, #false otherwise.
 */
typedef bool (*find_list_item_callback)(void *, va_list);

/**
 * @brief Gets the max number of items that can be stored in the list.
 * @param list Pointer to the list.
 * @return Returns the capacity or #RESULT_ERROR if the list is #NULL.
 */
int getListCapacity(const list_t *list);

/**
 * @brief Gets the number of items stored in the list.
 * @param list Pointer to the list.
 * @return Returns the number of items stored or #RESULT_ERROR if the
 * list is #NULL.
 */
int getListCount(const list_t *list);

/**
 * @brief Gets if the list is empty.
 * @param list Pointer to the list.
 * @return Returns #true if the list is empty, #false otherwise.
 */
bool isListEmpty(const list_t *list);

/**
 * @brief Gets if the list is full.
 * @param list Pointer to the list.
 * @return Returns #true if the list is full, #false otherwise.
 */
bool isListFull(const list_t *list);

/**
 * @brief Creates a new list.
 * @param capacity Max number of items that can be stored.
 * @param itemSize The size in bytes of the item type.
 * @return Returns the pointer to the new list, or #NULL if the
 * capacity and/or itemSize is zero or below.
 */
list_t *createList(uint capacity, size_t itemSize);

/**
 * @brief Clears the content of the list.
 * @param list - Pointer to the list.
 * @remarks This function reset the list counter to zero allowing to reuse the
 * list for store new items. This function not free the memory used by the list.
 */
void clearList(list_t *list);

/**
 * @brief Clears the content of the list and execute a callback on each item of the list.
 * @param list Pointer to the list.
 * @param onItem Callback to execute on each item.
 * @remarks Like the clearList function, this function only reset the counter to
 * zero, but allow to execute a callback on each item in the list (e.g. free memory
 * of an inner pointer).
 */
void clearListEx(list_t *list, foreach_list_item_callback onItem);

/**
 * @brief Destroys the list.
 * @param list Pointer to the list.
 * @remarks This function free the memory ocuped by the list and by the pointer
 * itself.
 */
void destroyList(list_t *list);

/**
 * @brief Destroys the list and execute a callback on each item of the list.
 * @param list Pointer to the list.
 * @param onItem Callback to execute on each item.
 * @remarks Like the destroyList function, this function free the mmeory ocuped
 * by the list and by the pointer itself, and allow to execute first a clean up
 * operation on each item, like in clearListEx function.
 */
void destroyListEx(list_t *list, foreach_list_item_callback onItem);

/**
 * @brief Creates a new item in the list.
 * @param list Pointer to the list.
 * @returns Returns the pointer to the new item in the list, or #NULL if the list is
 * full or if the list is #NULL.
 * @remarks This function not allocated new memory for the item, only point to the
 * next available position in the reserved memory.
 */
void *createListItem(list_t *list);

/**
 * @brief Creates a new item in the list with condition callback.
 * @param list Pointer to the list.
 * @param onBeforeCreate Function callback that define a condition to satisfy to
 * create the item.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the new item in the list, or #NULL if
 * onBeforeCreate function callback returns #false, if the list is full or if the
 * list is #NULL.
 * @remarks The onBeforeCreate function must be return #true to able create the new
 * item. You can use this function to implement behaviours like a dictionary
 * item key check or another required condition to satify before create the item.
 *
 * Like the createListItem function, this function not allocated new memory for the
 * item, only point to the next available position in the reserved memory.
 */
void *createListItemEx(list_t *list, create_list_item_callback onBeforeCreate, ...);

/**
 * @brief Creates a new item in the list with condition callback (Variadic version).
 * @param list Pointer to the list.
 * @param onBeforeCreate Function callback that define a condition to satisfy to
 * create the item.
 * @param args List of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the new item in the list, or #NULL if
 * onBeforeCreate function callback returns #false, if the list is full or if the
 * list is #NULL.
 * @remarks The onBeforeCreate function must be return #true to able create the new
 * item. You can use this function to implement behaviours like a dictionary
 * item key check or another required condition to satify before create the item.
 *
 * Like the createListItem function, this function not allocated new memory for the
 * item, only point to the next available position in the reserved memory.
 */
void *createListItemExArgs(list_t *list, create_list_item_callback onBeforeCreate, va_list args);

/**
 * @brief Gets the pointer to an item in the list.
 * @param list Pointer to a list.
 * @param index Index of the item. Must be a number between 0 and below of list count.
 * @returns Returns the pointer to the new item in the list, or #NULL if the index is
 * over the list count or capacity or below zero, or if the list is #NULL.
 */
void *getListItem(const list_t *list, int index);

/**
 * @brief Loops the entire list and execute a callback in each item.
 * @param list Pointer to the list.
 * @param onItem Callback to execute in each item.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @remarks Use this function execute a callback on each item in the list sequentially.
 */
void forEachList(const list_t *list, foreach_list_item_callback onItem, ...);

/**
 * @brief Loops the entire list and execute a callback in each item (Variadic version).
 * @param list Pointer to the list.
 * @param onItem Callback to execute in each item.
 * @param args List of arguments to use as extra parameters in the callback.
 * @remarks Use this function execute a callback on each item in the list sequentially.
 */
void forEachListArgs(const list_t *list, foreach_list_item_callback onItem, va_list args);

/**
 * @brief Finds an item that match with the predicate.
 * @param list Pointer to the list.
 * @param predicate Function callback to execute in each item. This functions define a
 * predicate that an item must be match.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the found item in the list, or #NULL if predicate
 * function callback returns #false, if the list is empty or if the list is #NULL.
 * @remarks The predicate function must be return #true to tell the list what item match.
 * You can use this function to implement behaviours like a dictionary item key check or
 * another required condition to satify to find the desired item.
 */
void *findListItem(const list_t *list, find_list_item_callback predicate, ...);

/**
 * @brief Finds an item that match with the predicate (Variadic version).
 * @param list Pointer to the list.
 * @param predicate Function callback to execute in each item. This functions define a
 * predicate that an item must be match.
 * @param args List of arguments to use as extra parameters in the callback.
 * @returns Returns the pointer to the found item in the list, or #NULL if predicate
 * function callback returns #false, if the list is empty or if the list is #NULL.
 * @remarks The predicate function must be return #true to tell the list what item match.
 * You can use this function to implement behaviours like a dictionary item key check or
 * another required condition to satify to find the desired item.
 */
void *findListItemArgs(const list_t *list, find_list_item_callback predicate, va_list args);

/**
 * @brief Checks if an item exists.
 * @param list Pointer to the list.
 * @param predicate Function callback to execute in each item. This functions define a
 * predicate that an item must be match.
 * @param ... Optional list of arguments to use as extra parameters in the callback.
 * @returns Returns #true if the item exists in the list, or #false if not exists, if the list 
 * is empty or if the list is #NULL.
 * @remarks The predicate function must be return #true to tell the list what item match.
 */
bool isListItemExists(const list_t *list, find_list_item_callback predicate, ...);

/**
 * @brief Checks if an item exists (Variadic version).
 * @param list Pointer to the list.
 * @param predicate Function callback to execute in each item. This functions define a
 * predicate that an item must be match.
 * @param args List of arguments to use as extra parameters in the callback.
 * @returns Returns #true if the item exists in the list, or #false if not exists, if the list 
 * is empty or if the list is #NULL.
 * @remarks The predicate function must be return #true to tell the list what item match.
 */
bool isListItemExistsArgs(const list_t *list, find_list_item_callback predicate, va_list args);
#endif
