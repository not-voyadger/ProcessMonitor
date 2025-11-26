#ifndef CPU_MONITOR_HPP
#define CPU_MONITOR_HPP

#include "ProcessMonitor.hpp" 
#include <iostream>

class CPUMonitor : public ProcessMonitor {
    private:
        double usage;
        double getUsage() const;
        void calculateUsage();

        unsigned long long prevIdle = 0;
        unsigned long long prevKernel = 0;
        unsigned long long prevUser = 0;
    public:
        CPUMonitor();
        ~CPUMonitor();

        void update() override;
        void display() const override;
};

#endif