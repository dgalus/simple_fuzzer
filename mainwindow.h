#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>
#include <vector>
#include "Fuzzer.h"
#include "CpuUsage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onMessageIn(QString, bool);
    void onCpuValuesIn(int, int, int, int);

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    CpuUsage *cpu;
    std::vector<Fuzzer*> fuzzerThreads;
    bool running;
    int counterAll;
    int counterPositive;
};

#endif // MAINWINDOW_H
