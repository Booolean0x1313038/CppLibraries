#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
void _Boolean::Collections::RingQueue::Clear()
#else
void RingQueue_Clear(RingQueue *RINGQUEUE_THISPTR)
#endif
{
    RINGQUEUE_THISPTR->_QueueFront = 0;
    RINGQUEUE_THISPTR->_QueueRear = 0;
}
