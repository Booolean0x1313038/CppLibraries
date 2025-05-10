#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
RingQueueElement _Boolean::Collections::RingQueue::Get(uint16_t offset)
#else
RingQueueElement RingQueue_Get(RingQueue *RINGQUEUE_THISPTR, uint16_t offset)
#endif
{
    return RINGQUEUE_THISPTR->_ElementsArray[(offset + RINGQUEUE_THISPTR->_QueueFront) % RINGQUEUE_THISPTR->_ElementsArrayLength];
}
