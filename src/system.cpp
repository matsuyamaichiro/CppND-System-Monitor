#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
// DONE
Processor& System::Cpu() {
    return cpu_;
}

// TODO: Return a container composed of the system's processes
// DONE
vector<Process>& System::Processes() {
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();
    for (int pid : pids) {
        Process process(pid);
        processes_.push_back(process);
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
// DONE
std::string System::Kernel() const {
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
// DONE
float System::MemoryUtilization() const {
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
// DONE
std::string System::OperatingSystem() const {
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
// DONE
int System::RunningProcesses() const {
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
// DONE
int System::TotalProcesses() const {
    return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
// DONE
long int System::UpTime() const {
    return LinuxParser::UpTime();
}