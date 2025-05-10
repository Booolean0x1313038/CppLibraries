#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
bool _Boolean::Collections::RingQueue::IsFull()
#else
bool RingQueue_IsFull(RingQueue *RINGQUEUE_THISPTR)
#endif
{
    return (RINGQUEUE_THISPTR->_QueueRear + 1) % RINGQUEUE_THISPTR->_ElementsArrayLength == RINGQUEUE_THISPTR->_QueueFront;
}
