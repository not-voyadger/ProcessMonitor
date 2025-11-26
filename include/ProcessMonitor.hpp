#ifndef PROCESS_MONITOR_HPP
#define PROCESS_MONITOR_HPP

class ProcessMonitor {
    public:
        ProcessMonitor();
        virtual ~ProcessMonitor();

        virtual void update() = 0;
        virtual void display() const = 0;
};
    
#endif