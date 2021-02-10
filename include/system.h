#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // DONE: TODO: See src/system.cpp
  std::vector<Process>& Processes();  // DONE: TODO: See src/system.cpp
  float MemoryUtilization() const;    // DONE: TODO: See src/system.cpp
  long UpTime() const;                // DONE: TODO: See src/system.cpp
  int TotalProcesses() const;         // DONE: TODO: See src/system.cpp
  int RunningProcesses() const;       // DONE: TODO: See src/system.cpp
  std::string Kernel() const;         // DONE: TODO: See src/system.cpp
  std::string OperatingSystem() const;// DONE: TODO: See src/system.cpp

  // TODO: Define any necessary private members
  // DONE
 private:
  Processor cpu_;
  std::vector<Process> processes_ = {};
};

#endif