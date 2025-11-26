#include "ProcessMonitor.hpp"


ProcessMonitor::ProcessMonitor() 
    : usage(0.0) {}
ProcessMonitor::~ProcessMonitor() {}

double ProcessMonitor::getUsage() const {
    return usage;
}

void ProcessMonitor::update() {
    calculateUsage();
    usageHistory.push_back(usage);
    if (usageHistory.size() > 100)
        usageHistory.erase(usageHistory.begin());
}

double ProcessMonitor::getAverageUsage(size_t lastN) const{
    if (usageHistory.empty()) return 0.0; 
    
    size_t start = (usageHistory.size() > lastN) ? usageHistory.size() - lastN : 0;

    double sum = 0.0;

    for (size_t i = start; i < usageHistory.size(); ++i) {
        sum += usageHistory[i];
    } 

    return sum / (usageHistory.size() - start);
}