#include "../include/CPUMonitor.hpp"
#include "../include/RAMMonitor.hpp"
#include "../include/ProcessMonitor.hpp"
#include <iostream>
#include <iomanip>
#include <thread>         
#include <chrono>
#include <windows.h>

void moveCursorTo(int row, int col) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)col, (SHORT)row};
    SetConsoleCursorPosition(hConsole, pos);
}

void printColoredValue(double value, double threshold, int width = 8) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (value >= threshold)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    else
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout << std::right << std::setw(width-1) << std::fixed << std::setprecision(1) << value << "% ";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {
    CPUMonitor cpu;
    RAMMonitor ram;

    system("cls");

    const double THRESHOLD = 80.0;

    std::cout << "+----------------+----------------+----------------+\n";
    std::cout << "|     Metric     |   Current %    |    Average %   |\n";
    std::cout << "+----------------+----------------+----------------+\n";

    std::cout << "| CPU Usage      |      " 
        << std::setw(3) << cpu.getUsage() << "       |      " 
        << std::setw(3) << cpu.getAverageUsage(10) << "       |\n";

    std::cout << "| RAM Usage      |      " 
        << std::setw(3) << ram.getUsage() << "       |      " 
        << std::setw(3) << ram.getAverageUsage(10) << "       |\n";

    std::cout << "+----------------+----------------+----------------+\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));


    while (true) {
        cpu.update();
        ram.update();
        
        moveCursorTo(3, 20);
        printColoredValue(cpu.getUsage(), THRESHOLD);

        moveCursorTo(3, 36);
        printColoredValue(cpu.getAverageUsage(10), THRESHOLD);

        moveCursorTo(4, 20);
        printColoredValue(ram.getUsage(), THRESHOLD);

        moveCursorTo(4, 36);
        printColoredValue(ram.getAverageUsage(10), THRESHOLD);

        if (cpu.getUsage() >= THRESHOLD || ram.getUsage() >= THRESHOLD) {
            moveCursorTo(6, 0);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::cout << "Dangerous level of usage! Close some processes!";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

        moveCursorTo(10, 0);

        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
