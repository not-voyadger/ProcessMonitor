#ifndef PROCESS_MONITOR_HPP
#define PROCESS_MONITOR_HPP

#include <vector>

class ProcessMonitor {
protected:
    double usage = 0.0;
    std::vector<double> usageHistory;
    double lastAverage = 0.0;  

    virtual void calculateUsage() = 0;

public:
    ProcessMonitor();
    virtual ~ProcessMonitor();

    void update();
    double getUsage() const;
    double getAverageUsage(size_t lastN = 10);
};

#endif