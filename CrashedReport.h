#ifndef CRASHEDREPORT_H
#define CRASHEDREPORT_H

#include <string>

class CrashedReport
{
public:
    bool crashed;
    std::string report;
    CrashedReport(bool crashed, std::string report)
        : crashed(crashed), report(report) { }
};

#endif // CRASHEDREPORT_H
