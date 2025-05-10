#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
void _Boolean::Collections::RingQueue::Enqueue(RingQueueElement data)
{
    if (IsFull())
    {
        Remove();
    }
#else
void RingQueue_Enqueue(RingQueue *RINGQUEUE_THISPTR, RingQueueElement data)
{
    if (RingQueue_IsFull(RINGQUEUE_THISPTR))
    {
        RingQueue_Remove(RINGQUEUE_THISPTR);
    }
#endif
    RINGQUEUE_THISPTR->_ElementsArray[RINGQUEUE_THISPTR->_QueueRear++] = data;
    (RINGQUEUE_THISPTR->_QueueRear) %= RINGQUEUE_THISPTR->_ElementsArrayLength;
}
