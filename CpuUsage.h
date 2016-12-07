#ifndef CPUUSAGE_H
#define CPUUSAGE_H

#include <QThread>
#include <QMutex>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

class CpuUsage : public QThread
{
    Q_OBJECT
public:
    explicit CpuUsage(QObject *parent = 0);
    void run();

signals:
    void sendCpuUsage(int, int, int, int);

};

#endif // CPUUSAGE_H
