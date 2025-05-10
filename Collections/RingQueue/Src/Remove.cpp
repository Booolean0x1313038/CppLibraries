#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
void _Boolean::Collections::RingQueue::Remove()
{
    if (Length() < 2)
    {
        Clear();
        return;
    }
#else
void RingQueue_Remove(RingQueue *RINGQUEUE_THISPTR)
{
    if (RingQueue_Length(RINGQUEUE_THISPTR) < 2)
    {
        RingQueue_Clear(RINGQUEUE_THISPTR);
        return;
    }
#endif
    ++RINGQUEUE_THISPTR->_QueueFront;
    RINGQUEUE_THISPTR->_QueueFront %= RINGQUEUE_THISPTR->_ElementsArrayLength;
}
