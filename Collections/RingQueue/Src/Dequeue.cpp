#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
RingQueueElement _Boolean::Collections::RingQueue::Dequeue()
{
    RingQueueElement data = Get(0);
    Remove();
#else
RingQueueElement RingQueue_Dequeue(RingQueue *RINGQUEUE_THISPTR)
{
    RingQueueElement data = RingQueue_Get(RINGQUEUE_THISPTR, 0);
    RingQueue_Remove(RINGQUEUE_THISPTR);
#endif
    return data;
}
