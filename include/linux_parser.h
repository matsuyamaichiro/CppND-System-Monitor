#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
float CpuUtilization(); // CHANGED from std::vector<std::string> CpuUtilization();
// SKIP below
// long Jiffies();
// long ActiveJiffies();
// long ActiveJiffies(int pid);
// long IdleJiffies();

// Processes
std::string Command(int pid);
int RamKb(int pid); // CHANGED from std::string Ram(int pid);
int Uid(int pid); // CHANGED from std::string Uid(int pid);
std::string User(int uid);
long int UpTime(int pid);
float CpuUtilization(int pid); // ADDED
};  // namespace LinuxParser

#endif