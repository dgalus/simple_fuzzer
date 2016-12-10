#ifndef FUZZER_H
#define FUZZER_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "ByteArray.h"
#include "CrashedReport.h"
#include "Helpers.h"

#define BINARY_PATH "test"
#define MAX_MUTATED_BYTES 0.01

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
    void write_sample(ByteArray ba, std::string report);
    CrashedReport execute(ByteArray ba);
    ByteArray select_file(std::string path);
    void mutate(ByteArray ba);
    int threadId;
};

#endif // FUZZER_H
