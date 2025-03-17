#include "utils.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

#define EARTH_RADIUS_MILES 3958.8  // Earth's radius in miles

// Convert degrees to radians
double to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

// Haversine formula to calculate great-circle distance between two points
double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = to_radians(lat2 - lat1);
    double dlon = to_radians(lon2 - lon1);

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(to_radians(lat1)) * cos(to_radians(lat2)) *
               sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS_MILES * c; // Distance in miles
}

// Log messages with timestamps
void log_message(const std::string& message) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    std::time_t now = std::time(nullptr);
    std::string timeStr = std::ctime(&now);
    timeStr.pop_back(); // Remove newline
    std::cout << "[" << timeStr << "] " << message << std::endl;
    logFile << "[" << timeStr << "] " << message << std::endl;
}
