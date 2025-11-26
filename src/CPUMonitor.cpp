#include "CPUMonitor.hpp"
#include <iostream>
#include <windows.h>
#include <vector>

CPUMonitor::CPUMonitor() : usage(0.0), prevIdle(0), prevKernel(0), prevUser(0) {}
CPUMonitor::~CPUMonitor() {}

void CPUMonitor::calculateUsage() {
    FILETIME idleTime, kernelTime, userTime;
    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) return;

    ULARGE_INTEGER idle, kernel, user;

    idle.LowPart = idleTime.dwLowDateTime;
    idle.HighPart = idleTime.dwHighDateTime;

    kernel.LowPart = kernelTime.dwLowDateTime;
    kernel.HighPart = kernelTime.dwHighDateTime;

    user.LowPart = userTime.dwLowDateTime;
    user.HighPart = userTime.dwHighDateTime;

    unsigned long long sysIdle = idle.QuadPart - prevIdle;
    unsigned long long sysKernel = kernel.QuadPart - prevKernel;
    unsigned long long sysUser = user.QuadPart - prevUser;

    if (prevIdle == 0 && prevKernel == 0 && prevUser == 0) {
        prevIdle = idle.QuadPart;
        prevKernel = kernel.QuadPart;
        prevUser = user.QuadPart;
        usage = 0.0;
        return;
    }

    usage = 100.0 * (double)(sysKernel + sysUser - sysIdle) / (sysKernel + sysUser);

    prevIdle = idle.QuadPart;
    prevKernel = kernel.QuadPart;
    prevUser = user.QuadPart;
}

double CPUMonitor::getUsage() const{
    return usage;
}


void CPUMonitor::update() {
    calculateUsage();
    usageHistory.push_back(usage);
    if (usageHistory.size() > 100) {
        usageHistory.erase(usageHistory.begin());
    }
}

double CPUMonitor::getAverageUsage(size_t lastN) const{
    if (usageHistory.empty()) return 0.0; 
    
    size_t start = 0;
    if (usageHistory.size() > lastN) {
        start = usageHistory.size() - lastN;
    } else {
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = start; i < usageHistory.size(); ++i) {
        sum += usageHistory[i];
    } 

    return sum / (usageHistory.size() - start); 
}   

void CPUMonitor::display() const{
    std::cout << "Current usage: " << usage << "%." << std::endl;
}

void CPUMonitor::displayAverage(size_t lastN) const{
    double avg = getAverageUsage(lastN);
    std::cout << "Average usage for last " << lastN << " measures is " << avg << "%." << std::endl; 
}