#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
// DONE
string Format::ElapsedTime(long seconds) {
    string s_seconds = std::to_string(seconds % 60);
    string s_minutes = std::to_string((seconds / 60) % 60);
    string s_hours = std::to_string(seconds / 3600);
    s_seconds.insert(0, 2 - s_seconds.length(), '0');
    s_minutes.insert(0, 2 - s_minutes.length(), '0');
    if (s_hours.length() < 2) {
        s_hours.insert(0, 2 - s_hours.length(), '0');
    } else if (s_hours.length() > 2) { // for overflow
        s_hours = ">99";
        s_minutes = "99";
        s_seconds = "99";
    }
    return s_hours + ":" + s_minutes + ":" + s_seconds;
}