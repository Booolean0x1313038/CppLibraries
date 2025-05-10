#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
uint16_t _Boolean::Collections::RingQueue::Length()
#else
uint16_t RingQueue_Length(RingQueue *RINGQUEUE_THISPTR)
#endif
{
    return (RINGQUEUE_THISPTR->_QueueRear + RINGQUEUE_THISPTR->_ElementsArrayLength - RINGQUEUE_THISPTR->_QueueFront) % RINGQUEUE_THISPTR->_ElementsArrayLength;
}
