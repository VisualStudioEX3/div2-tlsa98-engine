//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022, 2026
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Ring buffer.
*/

#include "H/RINGBUFF.H"

static uint getCurrentFirstIndex(const ring_buffer_t *ringBuffer)
{
    int index = 0;

    if (isRingBufferFull(ringBuffer))
    {
        index = ringBuffer->insertIndex;

        if (index == getRingBufferCapacity(ringBuffer))
            index = 0;
    }

    return index;
}

int getRingBufferCapacity(const ring_buffer_t *ringBuffer)
{
    return ringBuffer
               ? getListCapacity(ringBuffer->list)
               : RESULT_ERROR;
}

int getRingBufferCount(const ring_buffer_t *ringBuffer)
{
    return ringBuffer
               ? getListCount(ringBuffer->list)
               : RESULT_ERROR;
}

bool isRingBufferEmpty(const ring_buffer_t *ringBuffer)
{
    return ringBuffer
               ? isListEmpty(ringBuffer->list)
               : false;
}

bool isRingBufferFull(const ring_buffer_t *ringBuffer)
{
    return ringBuffer
               ? isListFull(ringBuffer->list)
               : false;
}

ring_buffer_t *createRingBuffer(uint capacity, size_t itemSize)
{
    ring_buffer_t *ringBuffer = NULL;

    if (capacity > 0 && itemSize > 0)
    {
        ringBuffer = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));

        if (ringBuffer)
        {
            ringBuffer->list = createList(capacity, itemSize);
            ringBuffer->insertIndex = 0;

            if (ringBuffer->list == NULL)
            {
                free(ringBuffer);
                ringBuffer = NULL;
            }
        }
    }

    return ringBuffer;
}

void clearRingBuffer(ring_buffer_t *ringBuffer)
{
    clearRingBufferEx(ringBuffer, NULL);
}

void clearRingBufferEx(ring_buffer_t *ringBuffer, foreach_ring_buffer_item_callback onItem)
{
    if (ringBuffer)
    {
        forEachRingBuffer(ringBuffer, onItem);
        ringBuffer->insertIndex = 0;
    }
}

void destroyRingBuffer(ring_buffer_t *ringBuffer)
{
    destroyRingBufferEx(ringBuffer, NULL);
}

void destroyRingBufferEx(ring_buffer_t *ringBuffer, foreach_ring_buffer_item_callback onItem)
{
    if (ringBuffer)
    {
        clearRingBufferEx(ringBuffer, onItem);
        destroyList(ringBuffer->list);
        free(ringBuffer);
    }
}

void *createRingBufferItem(ring_buffer_t *ringBuffer)
{
    return createRingBufferItemEx(ringBuffer, NULL);
}

void *createRingBufferItemEx(ring_buffer_t *ringBuffer, create_ring_buffer_item_callback onBeforeCreate, ...)
{
    va_list args;

    va_start(args, onBeforeCreate);

    void *ret = createRingBufferItemExArgs(ringBuffer, onBeforeCreate, args);

    va_end(args);

    return ret;
}

void *createRingBufferItemExArgs(ring_buffer_t *ringBuffer, create_ring_buffer_item_callback onBeforeCreate, va_list args)
{
    void *item = NULL;
    bool canCreate = true;
    va_list copyArgs;

    if (ringBuffer)
    {
        if (onBeforeCreate)
        {
            va_copy(copyArgs, args);
            canCreate = onBeforeCreate(ringBuffer, copyArgs);
        }

        if (canCreate)
        {
            if (isRingBufferFull(ringBuffer))
                item = getListItem(ringBuffer->list, ringBuffer->insertIndex);
            else
                item = createListItem(ringBuffer->list);

            if (++ringBuffer->insertIndex == getRingBufferCapacity(ringBuffer))
                ringBuffer->insertIndex = 0;
        }
    }

    return item;
}

void *getRingBufferItem(const ring_buffer_t *ringBuffer, int index)
{
    void *item = NULL;

    if (ringBuffer)
    {
        int count = getRingBufferCount(ringBuffer);
        int bufferIndex = getCurrentFirstIndex(ringBuffer) + index;

        if (bufferIndex >= count)
            bufferIndex = bufferIndex - count;

        item = getListItem(ringBuffer->list, bufferIndex);
    }

    return item;
}

void forEachRingBuffer(const ring_buffer_t *ringBuffer, foreach_ring_buffer_item_callback onItem, ...)
{
    va_list args;

    va_start(args, onItem);
    forEachRingBufferArgs(ringBuffer, onItem, args);
    va_end(args);
}

void forEachRingBufferArgs(const ring_buffer_t *ringBuffer, foreach_ring_buffer_item_callback onItem, va_list args)
{
    va_list copyArgs;

    if (!isRingBufferEmpty(ringBuffer) && onItem)
    {
        int count = getRingBufferCount(ringBuffer);
        int bufferIndex = getCurrentFirstIndex(ringBuffer);

        for (int i = 0; i < count; i++)
        {
            va_copy(copyArgs, args);
            onItem(i, getListItem(ringBuffer->list, bufferIndex), copyArgs);

            if (++bufferIndex == count)
                bufferIndex = 0;
        }
    }
}
