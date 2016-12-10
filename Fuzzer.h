#ifndef FUZZER_H
#define FUZZER_H

#include <QThread>
#include <QMutex>
#include <QString>

class Fuzzer : public QThread
{
    Q_OBJECT
public:
    explicit Fuzzer(int threadId, QObject *parent = 0);
    void run();
    bool Stop;

signals:
    void printInfo(QString, bool);
private:
    int threadId;
};

#endif // FUZZER_H
