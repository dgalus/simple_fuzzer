#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cpu = new CpuUsage(this);
    connect(cpu, SIGNAL(sendCpuUsage(int,int,int,int)), this, SLOT(onCpuValuesIn(int,int,int,int)));
    cpu->start();
    this->running = false;
    this->counterAll = 0;
    this->counterPositive = 0;
    mkdir("tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("crashes", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

MainWindow::~MainWindow()
{
    cpu->terminate();
    for(std::vector<Fuzzer*>::iterator it = fuzzerThreads.begin(); it != fuzzerThreads.end(); it++)
    {
        (*it)->Stop = true;
        (*it)->terminate();
    }
    fuzzerThreads.erase(fuzzerThreads.begin(), fuzzerThreads.end());
    delete ui;
}

void MainWindow::onMessageIn(QString msg, bool positive)
{
    this->counterAll++;
    ui->testCountEdit->setText(QString::number(this->counterAll));
    if(positive)
    {
        counterPositive++;
    }
    ui->crashCountEdit->setText(QString::number(this->counterPositive));
    ui->log->append(msg);
}

void MainWindow::onCpuValuesIn(int cpu1, int cpu2, int cpu3, int cpu4)
{
    ui->cpu1ProgressBar->setValue(cpu1);
    ui->cpu2ProgressBar->setValue(cpu2);
    ui->cpu3ProgressBar->setValue(cpu3);
    ui->cpu4ProgressBar->setValue(cpu4);
}

void MainWindow::on_startButton_clicked()
{
    if(!running)
    {
        for(int i = 0; i < ui->threadCountSpin->value(); i++)
        {
            Fuzzer* f = new Fuzzer(i, this);
            f->Stop = false;
            this->fuzzerThreads.push_back(f);
        }
        for(int i = 0; i < ui->threadCountSpin->value(); i++)
        {
            connect(fuzzerThreads.at(i), SIGNAL(printInfo(QString, bool)), this, SLOT(onMessageIn(QString, bool)));
            fuzzerThreads.at(i)->start();
        }
        running = true;
        ui->startButton->setText("Stop");
    }
    else
    {
        QFile f("stats.txt");
        if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream ts(&f);
            ts << "Threads = " << fuzzerThreads.size() << endl;
            ts << "Tests done = " << ui->testCountEdit->text() << endl;
            ts << "Crashes = " << ui->crashCountEdit->text() << endl;
            ts << "CPU1 = " << ui->cpu1ProgressBar->value() << endl;
            ts << "CPU2 = " << ui->cpu2ProgressBar->value() << endl;
            ts << "CPU3 = " << ui->cpu3ProgressBar->value() << endl;
            ts << "CPU4 = " << ui->cpu4ProgressBar->value() << endl << endl << endl;
        }
        f.close();
        for(std::vector<Fuzzer*>::iterator it = fuzzerThreads.begin(); it != fuzzerThreads.end(); it++)
        {
            (*it)->Stop = true;
            (*it)->terminate();
            (*it)->wait();
        }
        fuzzerThreads.erase(fuzzerThreads.begin(), fuzzerThreads.end());
        // TODO: delete all temporary files
        ui->startButton->setText("Start");
        running = false;
    }
}
