#ifndef UTILS_H
#define UTILS_H

#include <string>

// Function prototypes
double knots_to_mph(double knots);
std::string format_altitude(int altitude);
std::string get_current_time();
void log_message(const std::string& message);

#endif
