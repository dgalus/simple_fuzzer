#include "Fuzzer.h"

Fuzzer::Fuzzer(int threadId, QObject* parent) : QThread(parent), threadId(threadId)
{ }

void Fuzzer::run()
{
    QString filename = "fuzz" + QString::number(threadId) + ".gdb";
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << "set disassembly-flavor intel" << endl;
        stream << "echo ------------------------------" << endl;
        stream << "r sample" << threadId << ".bin" << endl;
        stream << "where" << endl;
        stream << "i r" << endl;
        stream << "x/10i $eip" << endl;
        stream << "echo ------------------------------" << endl;
    }
    file.close();

    ByteArray ba = select_file(std::string(BINARY_PATH));

    while(true)
    {
        if(!this->Stop)
        {
            ByteArray ba2 = ba;
            char *data = (char*) malloc(ba.length+1);
            memcpy(data, ba.data, ba.length);
            ba2.data = data;
            mutate(ba2);
            CrashedReport cr = execute(ba2);
            if(cr.crashed)
                write_sample(ba2, cr.report);
            free(ba2.data);
        }
    }
}

void Fuzzer::mutate(ByteArray ba)
{
    if(ba.length == 0)
        return;
    int max_n = (int) ba.length * MAX_MUTATED_BYTES;
    if(max_n == 0)
        max_n = 1;
    int n = (qrand() % max_n) + 1;
    for(int i=0; i < n; i++)
    {
        int idx = qrand() % ba.length;
        ba.data[idx] = (qrand() % 255) + 1;
    }
}

ByteArray Fuzzer::select_file(std::string path)
{
    char* buffer;
    FILE *p = fopen(path.c_str(), "rb");
    unsigned long filelen;
    fseek(p, 0, SEEK_END);
    filelen = ftell(p);
    rewind(p);
    buffer = (char*) malloc((filelen+1)*sizeof(char));
    fread(buffer, filelen, 1, p);
    fclose(p);
    ByteArray ba(filelen, buffer);
    return ba;
}

CrashedReport Fuzzer::execute(ByteArray ba)
{
    std::string filename = "sample" + to_string(threadId) + ".bin";
    FILE *w = fopen(filename.c_str(), "wb");
    fwrite(ba.data, ba.length, 1, w);
    fclose(w);
    char buf[2000];
    std::string report = "";

    std::string cmd = "gdb --batch --return-child-result -x fuzz" + to_string(threadId) + ".gdb " + std::string(BINARY_PATH) + " 2>&1";
    FILE* p = popen(cmd.c_str(), "r");
    if(p == NULL)
    {
        perror("ERROR!");
    }
    while(fgets(buf, sizeof(buf), p))
    {
        report.append(buf);
    }
    int ret_code = pclose(p);
    bool crashed = (ret_code > 3);
    QString msg = "Thread #" + QString::number(this->threadId) + ": OK";
    emit printInfo(msg, false);
    return CrashedReport(crashed, report);
}

void Fuzzer::write_sample(ByteArray ba, std::string report)
{
    time_t t = time(NULL);
    struct tm ts = *localtime(&t);
    unsigned int rnd = rand() % INT_MAX;
    std::string name = "" + to_string(ts.tm_year+1900) + to_string(ts.tm_mon+1) + to_string(ts.tm_mday) + to_string(ts.tm_hour) + to_string(ts.tm_min) + to_string(ts.tm_sec) + "_" + to_string(rnd);
    FILE* crash_out = fopen(std::string("crashes/" + name + ".bin").c_str(), "wb");
    fwrite(ba.data, ba.length, 1, crash_out);
    fclose(crash_out);
    FILE* report_out = fopen(std::string("crashes/" + name + ".txt").c_str(), "wb");
    fwrite(report.c_str(), report.length(), 1, report_out);
    fclose(report_out);
    QString msg = "Thread #" + QString::number(this->threadId) + ": Crash written as " + QString::fromStdString(name);
    emit printInfo(msg, true);
    this->msleep(100);
}
