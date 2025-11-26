#include "CPUMonitor.hpp"
#include "ProcessMonitor.hpp"
#include <iostream>
#include <windows.h>
#include <vector>

CPUMonitor::CPUMonitor() 
    : prevIdle(0), prevKernel(0), prevUser(0) {}
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

void CPUMonitor::displayCPU() const{
    std::cout << "Current usage of CPU is: " << usage << "%." << std::endl;
}

void CPUMonitor::displayAverageCPU(size_t lastN) const{
    std::cout << "Average CPU usage for last " << lastN << " measures is " << getAverageUsage(lastN) << "%." << std::endl; 
}