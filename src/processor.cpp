#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
// DONE
float Processor::Utilization() const {
    return LinuxParser::CpuUtilization();
}