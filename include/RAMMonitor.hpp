#ifndef RAM_MONITOR_HPP
#define RAM_MONITOR_HPP

#include "ProcessMonitor.hpp"

class RAMMonitor : public ProcessMonitor {
    private:
        unsigned long long getTotalRAM() const;
        unsigned long long getUsedRAM() const;
    protected:
        void calculateUsage() override;
    public:
        RAMMonitor();
        ~RAMMonitor();
};

#endif 