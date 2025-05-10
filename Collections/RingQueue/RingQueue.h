#ifndef __RINGQUEUE_SEND_H__
#define __RINGQUEUE_SEND_H__
#pragma once

#include "RingQueue_Configuration.h"
#include <stdbool.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
#define RINGQUEUE_THISPTR this
namespace _Boolean::Collections
{
class RingQueue
{
#else
typedef struct
{
#endif
    uint16_t _QueueFront;
    uint16_t _QueueRear;
    uint16_t _ElementsArrayLength;
    RingQueueElement* _ElementsArray;
#ifndef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
} RingQueue;

inline bool RingQueue_IsEmpty(RingQueue *RINGQUEUE_THISPTR) { return RINGQUEUE_THISPTR->_QueueFront == RINGQUEUE_THISPTR->_QueueRear; }
void RingQueue_Initialize(RingQueue *RINGQUEUE_THISPTR, RingQueueElement* elementsArray, uint16_t elementsAttayLength);
bool RingQueue_IsFull(RingQueue *RINGQUEUE_THISPTR);
void RingQueue_Clear(RingQueue *RINGQUEUE_THISPTR);
void RingQueue_Remove(RingQueue *RINGQUEUE_THISPTR);
void RingQueue_Enqueue(RingQueue *RINGQUEUE_THISPTR, RingQueueElement data);
void RingQueue_EnqueueMultipleBytes(RingQueue* RINGQUEUE_THISPTR, RingQueueElement* dataPtr, uint16_t length);
RingQueueElement RingQueue_Get(RingQueue *RINGQUEUE_THISPTR, uint16_t offset);
RingQueueElement RingQueue_Dequeue(RingQueue *RINGQUEUE_THISPTR);
uint16_t RingQueue_Length(RingQueue *RINGQUEUE_THISPTR);
uint16_t RingQueue_RemoveMultipleBytes(RingQueue* RINGQUEUE_THISPTR, uint16_t length);
uint16_t RingQueue_GetMultipleBytes(RingQueue* RINGQUEUE_THISPTR, uint16_t offset, RingQueueElement* dataPtr, uint16_t length);
uint16_t RingQueue_DequeueMultipleBytes(RingQueue* RINGQUEUE_THISPTR, RingQueueElement* dataPtr, uint16_t length);
#else
public:
    RingQueue(RingQueueElement* elementsArray, uint16_t elementsAttayLength);
    inline bool IsEmpty() { return RINGQUEUE_THISPTR->_QueueFront == RINGQUEUE_THISPTR->_QueueRear; }
    bool IsFull();
    void Clear();
    void Remove();
    void Enqueue(RingQueueElement data);
    void EnqueueMultipleBytes(RingQueueElement* dataPtr, uint16_t length);
    RingQueueElement Get(uint16_t offset);
    RingQueueElement Dequeue();
    uint16_t Length();
    uint16_t RemoveMultipleBytes(uint16_t length);
    uint16_t GetMultipleBytes(uint16_t offset, RingQueueElement* dataPtr, uint16_t length);
    uint16_t DequeueMultipleBytes(RingQueueElement* dataPtr, uint16_t length);
#endif

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
};
}
#endif
#endif
