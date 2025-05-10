#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
_Boolean::Collections::RingQueue::RingQueue(RingQueueElement* elementsArray, uint16_t elementsAttayLength)
{
    Clear();
#else
void RingQueue_Initialize(RingQueue *RINGQUEUE_THISPTR, RingQueueElement* elementsArray, uint16_t elementsAttayLength)
{
    RingQueue_Clear(RINGQUEUE_THISPTR);
#endif
    RINGQUEUE_THISPTR->_ElementsArray = elementsArray;
    RINGQUEUE_THISPTR->_ElementsArrayLength = elementsAttayLength;
}
