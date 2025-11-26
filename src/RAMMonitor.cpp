#include "RAMMonitor.hpp"
#include "ProcessMonitor.hpp"
#include <iostream>
#include <windows.h>

RAMMonitor::RAMMonitor() {}
RAMMonitor::~RAMMonitor() {}

unsigned long long RAMMonitor::getTotalRAM() const{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
}

unsigned long long RAMMonitor::getUsedRAM() const{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys - status.ullAvailPhys;
}

void RAMMonitor::calculateUsage() {
    usage = (static_cast<double>(getUsedRAM()) / static_cast<double>(getTotalRAM())) * 100;
}

void RAMMonitor::displayRAM() const{
    std::cout << "Current usage of RAM is: " << usage << "%." << std::endl;
}

void RAMMonitor::displayAverageRAM(size_t lastN) const {
    std::cout << "Average RAM usage for last " << lastN << " measures is " << getAverageUsage(lastN) << "%." << std::endl; 
}
