#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "../RingQueue.h"

#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
using namespace _Boolean::Collections;
#endif

void ShowBuffer(unsigned char* dataPtr, size_t length)
{
    qDebug() << "Length =" << length;
    QString str = "";
    for (int i = 0; i < length; i++)
    {
        str += QString("%1").arg(dataPtr[i], 3) + " ";
        if(i % 10 == 9 )
        {
            qDebug() << str;
            str = "";
        }
    }
    if (str.length() != 0)
    {
        qDebug() << str;
    }
}

RingQueueElement _RingQueueElement[64];
RingQueue* _RingQueuePtr;

int main(int argc, char *argv[])
{
#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
    _RingQueuePtr = new RingQueue(_RingQueueElement, 64);
#else
    _RingQueuePtr = new RingQueue();
    RingQueue_Initialize(_RingQueuePtr, _RingQueueElement, 64);
#endif

    unsigned char str[10] = {0,1,2,3,4,5,6,7,8,9};

    for (int i = 0; i < 50; i++)
    {
#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
        _RingQueuePtr->EnqueueMultipleBytes((unsigned char*)str, sizeof(str));
#else
        RingQueue_EnqueueMultipleBytes(_RingQueuePtr, (unsigned char*)str, sizeof(str));
#endif
        for (int j = 0; j < sizeof(str); j++)
        {
            str[j] += sizeof(str);
        }
#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
        int length = _RingQueuePtr->Length();
#else
        int length = RingQueue_Length(_RingQueuePtr);
#endif
        int offset = 0;
        QString qstring = "";
        while (offset < length)
        {
            unsigned char buf[20];
            memset(buf, 0, sizeof(buf));
#ifdef RINGQUEUE_ENABLE_FEATURE_CPLUSPLUS_CLASS
            unsigned char getLength = _RingQueuePtr->GetMultipleBytes(offset, buf, sizeof(buf));
#else
            unsigned char getLength = RingQueue_GetMultipleBytes(_RingQueuePtr, offset, buf, sizeof(buf));
#endif
            if (getLength == 0)
            {
                break;
            }
            for (int k = 0; k < getLength; k++)
            {
                qstring += QString("%1").arg(buf[k], 4);
            }
            // qstring += buf;
            offset += getLength;
        }
        qDebug() << QString("Length = %1 | Usage = %2 bytes | UnitsCount = %3 |").arg(length, 4).arg(-1).arg(-1) <<  qstring;
    }
}
