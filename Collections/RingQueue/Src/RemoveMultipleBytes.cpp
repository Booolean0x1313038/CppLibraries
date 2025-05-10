#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
uint16_t _Boolean::Collections::RingQueue::RemoveMultipleBytes(uint16_t length)
{
    uint16_t totalLength = Length();
    if (length >= totalLength)
    {
        Clear();
        return totalLength;
    }
    totalLength = length;
    while (length--)
    {
        Remove();
    }
#else
uint16_t RingQueue_RemoveMultipleBytes(RingQueue* RINGQUEUE_THISPTR, uint16_t length)
{
    uint16_t totalLength = RingQueue_Length(RINGQUEUE_THISPTR);
    if (length >= totalLength)
    {
        RingQueue_Clear(RINGQUEUE_THISPTR);
        return totalLength;
    }
    totalLength = length;
    while (length--)
    {
        RingQueue_Remove(RINGQUEUE_THISPTR);
    }
#endif
    return totalLength;
}
