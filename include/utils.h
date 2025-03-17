#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cmath>

// Declare `HOME_LAT` and `HOME_LON` as extern so they can be modified at runtime
extern double HOME_LAT;
extern double HOME_LON;

void log_message(const std::string& message);
double calculate_distance(double lat1, double lon1, double lat2, double lon2);

#endif
