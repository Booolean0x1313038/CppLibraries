#include "../RingQueue.h"
#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
uint16_t _Boolean::Collections::RingQueue::DequeueMultipleBytes(RingQueueElement* dataPtr, uint16_t length)
{
    length = GetMultipleBytes(0, dataPtr, length);
    RemoveMultipleBytes(length);
#else
uint16_t RingQueue_DequeueMultipleBytes(RingQueue* RINGQUEUE_THISPTR, RingQueueElement* dataPtr, uint16_t length)
{
    length = RingQueue_GetMultipleBytes(RINGQUEUE_THISPTR, 0, dataPtr, length);
    RingQueue_RemoveMultipleBytes(RINGQUEUE_THISPTR, length);
#endif
    return length;
}
