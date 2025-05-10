#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
uint16_t _Boolean::Collections::RingQueue::GetMultipleBytes(uint16_t offset, RingQueueElement* dataPtr, uint16_t length)
{
    uint16_t totalLength = Length();
    if (offset > totalLength)
    {
        return 0;
    }
    totalLength -= offset;
    if (length > totalLength)
    {
        length = totalLength;
    }
    totalLength = length;
    while(length--)
    {
        *(dataPtr + length) = Get(offset + length);
    }
#else
uint16_t RingQueue_GetMultipleBytes(RingQueue* RINGQUEUE_THISPTR, uint16_t offset, RingQueueElement* dataPtr, uint16_t length)
{
    uint16_t totalLength = RingQueue_Length(RINGQUEUE_THISPTR);
    if (offset > totalLength)
    {
        return 0;
    }
    totalLength -= offset;
    if (length > totalLength)
    {
        length = totalLength;
    }
    totalLength = length;
    while(length--)
    {
        *(dataPtr + length) = RingQueue_Get(RINGQUEUE_THISPTR, offset + length);
    }
#endif
    return totalLength;
}
