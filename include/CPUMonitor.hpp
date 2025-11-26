#ifndef CPU_MONITOR_HPP
#define CPU_MONITOR_HPP

#include "ProcessMonitor.hpp"

class CPUMonitor : public ProcessMonitor {
    private:
        unsigned long long prevIdle = 0;
        unsigned long long prevKernel = 0;
        unsigned long long prevUser = 0;

    protected:
        void calculateUsage() override;

    public:
        CPUMonitor();
        ~CPUMonitor();

        void displayCPU() const;
        void displayAverageCPU(size_t lastN = 10) const;
};

#endif