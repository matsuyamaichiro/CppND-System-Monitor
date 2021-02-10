#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int &pid) : pid_(pid) {}
  int Pid() const;                         // DONE: TODO: See src/process.cpp
  std::string User() const;                // DONE: TODO: See src/process.cpp
  std::string Command() const;             // DONE: TODO: See src/process.cpp
  float CpuUtilization() const;            // DONE: TODO: See src/process.cpp
  std::string Ram() const;                 // DONE: TODO: See src/process.cpp
  long int UpTime() const;                 // DONE: TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: TODO: See src/process.cpp

  // TODO: Declare any necessary private members
  // DONE
 private:
  int pid_;
};

#endif