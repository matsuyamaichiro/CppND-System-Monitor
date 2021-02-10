#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

#include <unistd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem(){
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// WON'T DO
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
// DONE
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  int memtotal{0};
  int memfree{0};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        if (std::all_of(value.begin(), value.end(), isdigit)) {
          memtotal = stoi(value);
          if (memfree != 0) break;
        }
      } else if (key == "MemFree:") {
        if (std::all_of(value.begin(), value.end(), isdigit)) {
          memfree = stoi(value);
          if (memtotal != 0) break;
        }
      }
    }
  }
  if (memtotal <= 0 || memfree < 0 || memfree > memtotal) {
    return 0.0;
  }
  return (float)(memtotal - memfree) / (float)memtotal;
}

// TODO: Read and return the system uptime
// DONE
long LinuxParser::UpTime() {
  string line;
  string uptime;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), '.', ' '); // ignore decimal part
    std::istringstream linestream(line);
    linestream >> uptime;
    if (std::all_of(uptime.begin(), uptime.end(), isdigit)) {
      return stol(uptime);
    }
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
// SKIPED
//  long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// SKIPED
//  long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
// SKIPED
//  long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
// SKIPED
//  long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// CHANGED from
//  vector<string> LinuxParser::CpuUtilization() { return {}; }
// DONE
float LinuxParser::CpuUtilization() {
  string line;
  string s_user, s_nice, s_system, s_idle, s_iowait, s_irq, s_softirq, s_steal;
  long non_idle{0}, idle{0};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore #1
    linestream >> s_user >> s_nice >> s_system >> s_idle >> s_iowait >> s_irq >> s_softirq >> s_steal;
    if (std::all_of(s_user.begin(), s_user.end(), isdigit) &&
        std::all_of(s_nice.begin(), s_nice.end(), isdigit) &&
        std::all_of(s_system.begin(), s_system.end(), isdigit) &&
        std::all_of(s_idle.begin(), s_idle.end(), isdigit) &&
        std::all_of(s_iowait.begin(), s_iowait.end(), isdigit) &&
        std::all_of(s_irq.begin(), s_irq.end(), isdigit) &&
        std::all_of(s_softirq.begin(), s_softirq.end(), isdigit) &&
        std::all_of(s_steal.begin(), s_steal.end(), isdigit)) {
      non_idle = stol(s_user) + stol(s_nice) + stol(s_system) + stol(s_irq) + stol(s_softirq) + stol(s_steal);
      idle = stol(s_idle) + stol(s_iowait);
      if (non_idle + idle > 0) {
        return (float)non_idle / (float)(non_idle + idle);
      }
    }
  }
  return 0.0;
}

// ADDED as a common function called by some public functions.
// DONE
static int GetKeyValue(const std::string &file_name, const std::string &given_key) {
  string line;
  string s_key;
  string s_value;
  int value{0};
  std::ifstream filestream(file_name);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> s_key >> s_value;
      if (s_key == given_key) {
        if (std::all_of(s_value.begin(), s_value.end(), isdigit)) {
          value = stoi(s_value);
          return value;
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the total number of processes
// DONE
int LinuxParser::TotalProcesses() {
  return GetKeyValue(kProcDirectory + kStatFilename, "processes");
}

// TODO: Read and return the number of running processes
// DONE
int LinuxParser::RunningProcesses() {
  return GetKeyValue(kProcDirectory + kStatFilename, "procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// DONE
string LinuxParser::Command(int pid) {
  string line;
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
    return command;
  }
  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// CHANGED from
//  string LinuxParser::Ram(int pid) { return string(); }
// DONE
int LinuxParser::RamKb(int pid) {
  return GetKeyValue(kProcDirectory + std::to_string(pid) + kStatusFilename, "VmSize:");
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// CHANGED from
//  string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }
// DONE
int LinuxParser::Uid(int pid) {
  return GetKeyValue(kProcDirectory + std::to_string(pid) + kStatusFilename, "Uid:");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// DONE
string LinuxParser::User(int uid) {
  string line;
  string user, passwd, s_uid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> passwd >> s_uid;
      if (std::all_of(s_uid.begin(), s_uid.end(), isdigit)) {
        if (stoi(s_uid) == uid) {
          return user;
        }
      }
    }
  }
  return "";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// DONE
long LinuxParser::UpTime(int pid) {
  string line;
  string s_starttime;
  long start_tick{0};
  long uptime_seconds{0};
  long hertz{100};
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 21; i++) { // ignore #1-#21 words
      linestream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    linestream >> s_starttime; // #22
    if (std::all_of(s_starttime.begin(), s_starttime.end(), isdigit)) {
      start_tick = stol(s_starttime);
    }
    uptime_seconds = UpTime();
    hertz = sysconf(_SC_CLK_TCK);
    if (hertz > 0) {
      return uptime_seconds - start_tick / hertz;
    }
  }
  return 0;
}

// ADDED instead of ActiveJiffies(int pid)
// DONE: Return process CPU utilization
float LinuxParser::CpuUtilization(int pid) {
  string line;
  string s_utime, s_stime, s_cutime, s_cstime;
  string s_starttime;
  long total_tick_spent{0};
  float total_seconds_spent{0};
  float total_seconds_past{0};
  long hertz{100};
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 13; i++) { // ignore #1-#13 words
      linestream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    linestream >> s_utime >> s_stime >> s_cutime >> s_cstime; // #14, #15, #16, #17
    if (std::all_of(s_utime.begin(), s_utime.end(), isdigit) &&
        std::all_of(s_stime.begin(), s_stime.end(), isdigit) &&
        std::all_of(s_cutime.begin(), s_cutime.end(), isdigit) &&
        std::all_of(s_cstime.begin(), s_cstime.end(), isdigit)) {
      total_tick_spent = stol(s_utime) + stol(s_stime) + stol(s_cutime) + stol(s_cstime);
    }
    hertz = sysconf(_SC_CLK_TCK);
    if (hertz > 0) {
      total_seconds_past = (float)UpTime(pid);
      total_seconds_spent = (float)total_tick_spent / (float)hertz;
      if (total_seconds_past > 0 + std::numeric_limits<float>::epsilon()) {
        return total_seconds_spent / total_seconds_past;
      }
    }
  }
  return 0.0;
}