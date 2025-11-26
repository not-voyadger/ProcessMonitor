#include "../include/CPUMonitor.hpp"
#include "../include/RAMMonitor.hpp"
#include "../include/ProcessMonitor.hpp"
#include <iostream>
#include <thread>         
#include <chrono>

int main() {
    CPUMonitor cpu;
    RAMMonitor ram;
    int displayCount = 0;

    while (true) {
        cpu.update();
        ram.update();
        cpu.displayCPU();
        ram.displayRAM();
        displayCount += 1;
        if (displayCount >= 10) {
            cpu.displayAverageCPU(10);
            ram.displayAverageRAM(10);
            displayCount = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
