#include "../include/CPUMonitor.hpp"
#include <iostream>
#include <thread>         
#include <chrono>

int main() {
    CPUMonitor cpu;

    while (true) {
        cpu.update();
        cpu.display();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
