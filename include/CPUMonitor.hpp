#ifndef CPU_MONITOR_HPP
#define CPU_MONITOR_HPP

#include "ProcessMonitor.hpp" 
#include <iostream>
#include <vector>

class CPUMonitor : public ProcessMonitor {
    private:
        double usage;
        std::vector<double> usageHistory;

        double getUsage() const;
        void calculateUsage();
        double getAverageUsage(size_t lastN = 10) const;

        unsigned long long prevIdle = 0;
        unsigned long long prevKernel = 0;
        unsigned long long prevUser = 0;
    public:
        CPUMonitor();
        ~CPUMonitor();

        void update() override;
        void display() const override;
        void displayAverage(size_t lastN = 10) const;
};

#endif