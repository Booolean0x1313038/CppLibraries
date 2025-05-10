#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
void _Boolean::Collections::RingQueue::EnqueueMultipleBytes(RingQueueElement* dataPtr, uint16_t length)
{
    while(length--)
    {
        Enqueue(*(dataPtr++));
    }
}
#else
void RingQueue_EnqueueMultipleBytes(RingQueue* RINGQUEUE_THISPTR, RingQueueElement* dataPtr, uint16_t length)
{
    while(length--)
    {
        RingQueue_Enqueue(RINGQUEUE_THISPTR, *(dataPtr++));
    }
}
#endif
