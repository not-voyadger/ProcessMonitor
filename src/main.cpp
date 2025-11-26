#include "../include/CPUMonitor.hpp"
#include <iostream>
#include <thread>         
#include <chrono>

int main() {
    CPUMonitor cpu;
    int displayCount = 0;

    while (true) {
        cpu.update();
        cpu.display();
        displayCount += 1;
        if (displayCount >= 10) {
            cpu.displayAverage(10);
            displayCount = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
