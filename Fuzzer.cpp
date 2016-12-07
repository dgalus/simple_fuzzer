#include "Fuzzer.h"

Fuzzer::Fuzzer(int threadId, QObject* parent) : QThread(parent), threadId(threadId)
{ }

void Fuzzer::run()
{
    for(int i = 0; i < 100000; i++)
    {
        QMutex mutex;
        mutex.lock();
        if(this->Stop)
            break;
        mutex.unlock();
        QString msg = "Thread #" + QString::number(this->threadId) + ": Message = " + QString::number(i);
        emit printInfo(msg);
        this->msleep(100);
    }
}
