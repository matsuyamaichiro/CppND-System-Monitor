#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// DONE
int Process::Pid() const {
    return pid_;
}

// TODO: Return this process's CPU utilization
// DONE
float Process::CpuUtilization() const {
    return LinuxParser::CpuUtilization(pid_);
}

// TODO: Return the command that generated this process
// DONE
string Process::Command() const {
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
// DONE: Return MB
string Process::Ram() const {
    return std::to_string((LinuxParser::RamKb(pid_) / 1024));
}

// TODO: Return the user (name) that generated this process
// DONE
string Process::User() const {
    return LinuxParser::User(LinuxParser::Uid(pid_));
}

// TODO: Return the age of this process (in seconds)
// DONE
long int Process::UpTime() const {
    return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// DONE
bool Process::operator<(Process const& a) const {
    return this->CpuUtilization() > a.CpuUtilization();
}