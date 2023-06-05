//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2023
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Fixed allocated list.

    Source: https://github.com/VisualStudioEX3/div2-framework/blob/master/SHARED/_LIST.CPP
*/

#include "..\H\SYSTEM\LIST.H"

static void *getItemPointer(const list_t *list, int index)
{
    return (void *)&list->items[index * list->itemSize];
}

int getListCapacity(const list_t *list)
{
    return list
               ? list->capacity
               : RESULT_ERROR;
}

int getListCount(const list_t *list)
{
    return list
               ? list->count
               : RESULT_ERROR;
}

bool isListEmpty(const list_t *list)
{
    return list
               ? list->count <= 0
               : false;
}

bool isListFull(const list_t *list)
{
    return list
               ? list->count == list->capacity
               : false;
}

list_t *createList(uint capacity, size_t itemSize)
{
    list_t *list = NULL;

    if (capacity > 0 && itemSize > 0)
    {
        list = (list_t *)malloc(sizeof(list_t));

        if (list)
        {
            list->capacity = capacity;
            list->count = 0;
            list->itemSize = itemSize;
            list->items = (byte *)malloc(list->capacity * list->itemSize);

            if (list->items == NULL)
            {
                free(list);
                list = NULL;
            }
        }
    }

    return list;
}

void clearList(list_t *list)
{
    clearListEx(list, NULL);
}

void clearListEx(list_t *list, foreach_list_item_callback onItem)
{
    if (list)
    {
        forEachList(list, onItem);
        list->count = 0;
    }
}

void destroyList(list_t *list)
{
    destroyListEx(list, NULL);
}

void destroyListEx(list_t *list, foreach_list_item_callback onItem)
{
    if (list)
    {
        clearListEx(list, onItem);
        free(list->items);
        free(list);
    }
}

void *createListItem(list_t *list)
{
    return createListItemEx(list, NULL);
}

void *createListItemEx(list_t *list, create_list_item_callback onBeforeCreate, ...)
{
    va_list args;

    va_start(args, onBeforeCreate);

    void *ret = createListItemExArgs(list, onBeforeCreate, args);

    va_end(args);

    return ret;
}

void *createListItemExArgs(list_t *list, create_list_item_callback onBeforeCreate, va_list args)
{
    void *item = NULL;
    bool canCreate = true;

    if (!isListFull(list))
    {
        if (onBeforeCreate)
            canCreate = onBeforeCreate(list, args);

        if (canCreate)
        {
            item = getItemPointer(list, list->count);
            list->count++;
        }
    }

    return item;
}

// TODO: Remove this and replace the call below using the future Math service.
#define isClamped(v, a, b) v >= a &&v <= b

void *getListItem(const list_t *list, int index)
{
    void *item = NULL;

    if (!isListEmpty(list) && isClamped(index, 0, list->count - 1))
        item = getItemPointer(list, index);

    return item;
}

void forEachList(const list_t *list, foreach_list_item_callback onItem, ...)
{
    va_list args;

    va_start(args, onItem);
    forEachListArgs(list, onItem, args);
    va_end(args);
}

void forEachListArgs(const list_t *list, foreach_list_item_callback onItem, va_list args)
{
    if (!isListEmpty(list) && onItem)
        for (int i = 0; i < list->count; i++)
            onItem(i, getItemPointer(list, i), args);
}

void *findListItem(const list_t *list, find_list_item_callback predicate, ...)
{
    va_list args;

    va_start(args, predicate);

    void *ret = findListItemArgs(list, predicate, args);

    va_end(args);

    return ret;
}

void *findListItemArgs(const list_t *list, find_list_item_callback predicate, va_list args)
{
    void *item = NULL;

    if (!isListEmpty(list) && predicate)
        for (int i = 0; i < list->count; i++)
        {
            void *iter = getListItem(list, i);

            if (predicate(iter, args))
            {
                item = iter;

                break;
            }
        }

    return item;
}

bool isListItemExists(const list_t *list, find_list_item_callback predicate, ...)
{
    va_list args;

    va_start(args, predicate);

    bool ret = isListItemExistsArgs(list, predicate, args);

    va_end(args);

    return ret;
}

bool isListItemExistsArgs(const list_t *list, find_list_item_callback predicate, va_list args)
{
    return findListItemArgs(list, predicate, args) != NULL;
}
