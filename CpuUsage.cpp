#include "CpuUsage.h"

CpuUsage::CpuUsage(QObject* parent) : QThread(parent)
{ }

void CpuUsage::run()
{
    while(true)
    {
        FILE *fp;
        char linec[1000];
        long values_cpu0[7];
        long values_cpu1[7];
        long values_cpu2[7];
        long values_cpu3[7];

        fp = fopen("/proc/stat", "r");

        fgets(linec, sizeof(linec)-1, fp);
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu0 %ld %ld %ld %ld %ld %ld %ld", &values_cpu0[0], &values_cpu0[1], &values_cpu0[2], &values_cpu0[3], &values_cpu0[4], &values_cpu0[5], &values_cpu0[6]);
        long total_jiffies_0 = values_cpu0[0] + values_cpu0[1] + values_cpu0[2] + values_cpu0[3] + values_cpu0[4] + values_cpu0[5] + values_cpu0[6];
        long work_jiffies_0 = values_cpu0[0] + values_cpu0[1] + values_cpu0[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu1 %ld %ld %ld %ld %ld %ld %ld", &values_cpu1[0], &values_cpu1[1], &values_cpu1[2], &values_cpu1[3], &values_cpu1[4], &values_cpu1[5], &values_cpu1[6]);
        long total_jiffies_1 = values_cpu1[0] + values_cpu1[1] + values_cpu1[2] + values_cpu1[3] + values_cpu1[4] + values_cpu1[5] + values_cpu1[6];
        long work_jiffies_1 = values_cpu1[0] + values_cpu1[1] + values_cpu1[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu2 %ld %ld %ld %ld %ld %ld %ld", &values_cpu2[0], &values_cpu2[1], &values_cpu2[2], &values_cpu2[3], &values_cpu2[4], &values_cpu2[5], &values_cpu2[6]);
        long total_jiffies_2 = values_cpu2[0] + values_cpu2[1] + values_cpu2[2] + values_cpu2[3] + values_cpu2[4] + values_cpu2[5] + values_cpu2[6];
        long work_jiffies_2 = values_cpu2[0] + values_cpu2[1] + values_cpu2[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu3 %ld %ld %ld %ld %ld %ld %ld", &values_cpu3[0], &values_cpu3[1], &values_cpu3[2], &values_cpu3[3], &values_cpu3[4], &values_cpu3[5], &values_cpu3[6]);
        long total_jiffies_3 = values_cpu3[0] + values_cpu3[1] + values_cpu3[2] + values_cpu3[3] + values_cpu3[4] + values_cpu3[5] + values_cpu3[6];
        long work_jiffies_3 = values_cpu3[0] + values_cpu3[1] + values_cpu3[2];
        fclose(fp);

        this->msleep(1000);

        fp = fopen("/proc/stat", "r");

        fgets(linec, sizeof(linec)-1, fp);
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu0 %ld %ld %ld %ld %ld %ld %ld", &values_cpu0[0], &values_cpu0[1], &values_cpu0[2], &values_cpu0[3], &values_cpu0[4], &values_cpu0[5], &values_cpu0[6]);
        long total_jiffies_0a = values_cpu0[0] + values_cpu0[1] + values_cpu0[2] + values_cpu0[3] + values_cpu0[4] + values_cpu0[5] + values_cpu0[6];
        long work_jiffies_0a = values_cpu0[0] + values_cpu0[1] + values_cpu0[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu1 %ld %ld %ld %ld %ld %ld %ld", &values_cpu1[0], &values_cpu1[1], &values_cpu1[2], &values_cpu1[3], &values_cpu1[4], &values_cpu1[5], &values_cpu1[6]);
        long total_jiffies_1a = values_cpu1[0] + values_cpu1[1] + values_cpu1[2] + values_cpu1[3] + values_cpu1[4] + values_cpu1[5] + values_cpu1[6];
        long work_jiffies_1a = values_cpu1[0] + values_cpu1[1] + values_cpu1[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu2 %ld %ld %ld %ld %ld %ld %ld", &values_cpu2[0], &values_cpu2[1], &values_cpu2[2], &values_cpu2[3], &values_cpu2[4], &values_cpu2[5], &values_cpu2[6]);
        long total_jiffies_2a = values_cpu2[0] + values_cpu2[1] + values_cpu2[2] + values_cpu2[3] + values_cpu2[4] + values_cpu2[5] + values_cpu2[6];
        long work_jiffies_2a = values_cpu2[0] + values_cpu2[1] + values_cpu2[2];
        fgets(linec, sizeof(linec)-1, fp);
        sscanf(linec, "cpu3 %ld %ld %ld %ld %ld %ld %ld", &values_cpu3[0], &values_cpu3[1], &values_cpu3[2], &values_cpu3[3], &values_cpu3[4], &values_cpu3[5], &values_cpu3[6]);
        long total_jiffies_3a = values_cpu3[0] + values_cpu3[1] + values_cpu3[2] + values_cpu3[3] + values_cpu3[4] + values_cpu3[5] + values_cpu3[6];
        long work_jiffies_3a = values_cpu3[0] + values_cpu3[1] + values_cpu3[2];

        fclose(fp);

        long work_over_period_0 = work_jiffies_0a - work_jiffies_0;
        long total_over_period_0 = total_jiffies_0a - total_jiffies_0;
        int ret0 = work_over_period_0*100./total_over_period_0;
        long work_over_period_1 = work_jiffies_1a - work_jiffies_1;
        long total_over_period_1 = total_jiffies_1a - total_jiffies_1;
        int ret1 = work_over_period_1*100./total_over_period_1;
        long work_over_period_2 = work_jiffies_2a - work_jiffies_2;
        long total_over_period_2 = total_jiffies_2a - total_jiffies_2;
        int ret2 = work_over_period_2*100./total_over_period_2;
        long work_over_period_3 = work_jiffies_3a - work_jiffies_3;
        long total_over_period_3 = total_jiffies_3a - total_jiffies_3;
        int ret3 = work_over_period_3*100./total_over_period_3;

        emit sendCpuUsage(ret0, ret1, ret2, ret3);
    }
}
