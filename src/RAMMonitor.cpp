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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (usage >= 80.0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }

    std::cout << "Current usage of RAM is: " << usage << "%." << std::endl;
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void RAMMonitor::displayAverageRAM(size_t lastN) {
    std::cout << "Average RAM usage for last " << lastN << " measures is " << getAverageUsage(lastN) << "%." << std::endl; 
}
