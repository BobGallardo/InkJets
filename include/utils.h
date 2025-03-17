#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Define home GPS coordinates (Set to your location)
constexpr double HOME_LAT = 37.3243;  // Cupertino, CA
constexpr double HOME_LON = -122.0561; // Corrected to match `display.cpp`

// Function prototypes
void log_message(const std::string& message);

#endif // UTILS_H
