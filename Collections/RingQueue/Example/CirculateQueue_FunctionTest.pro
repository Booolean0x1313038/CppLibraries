QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../Src/Clear.cpp \
        ../Src/Dequeue.cpp \
        ../Src/DequeueMultipleBytes.cpp \
        ../Src/Enqueue.cpp \
        ../Src/EnqueueMultipleBytes.cpp \
        ../Src/Get.cpp \
        ../Src/GetMultipleBytes.cpp \
        ../Src/Initialize.cpp \
        ../Src/IsFull.cpp \
        ../Src/Length.cpp \
        ../Src/Remove.cpp \
        ../Src/RemoveMultipleBytes.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Buffer.h \
    ../RingQueue.h \
    ../RingQueue_Configuration.h
