#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cpu = new CpuUsage(this);
    connect(cpu, SIGNAL(sendCpuUsage(int,int,int,int)), this, SLOT(onCpuValuesIn(int,int,int,int)));
}

MainWindow::~MainWindow()
{
    /*for(std::vector<Fuzzer*>::iterator it = fuzzerThreads.begin(); it != fuzzerThreads.end(); it++)
    {
        (*it)->Stop = true;
        (*it)->terminate();
    }*/
    delete ui;
}

void MainWindow::onMessageIn(QString msg)
{
    ui->log->append(msg + "\n");
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
    cpu->start();
    /*for(int i = 0; i < ui->threadCountSpin->value(); i++)
    {
        Fuzzer* f = new Fuzzer(i, this);
        f->Stop = false;
        this->fuzzerThreads.push_back(f);
    }
    for(int i = 0; i < ui->threadCountSpin->value(); i++)
    {
        connect(fuzzerThreads.at(i), SIGNAL(printInfo(QString)), this, SLOT(onMessageIn(QString)));
        fuzzerThreads.at(i)->run();
    }*/
}
