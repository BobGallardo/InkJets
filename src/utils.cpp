#include "utils.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

// Define `HOME_LAT` and `HOME_LON` here so they can be modified at runtime
double HOME_LAT = 37.3243;  // Cupertino, CA
double HOME_LON = -122.0561;

void log_message(const std::string& message) {
    std::ofstream log_file("log.txt", std::ios::app);
    if (log_file.is_open()) {
        std::time_t now = std::time(nullptr);
        log_file << "[" << std::ctime(&now) << "] " << message << "\n";
    }
}

// Haversine formula to calculate distance between two lat/lon points
double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    constexpr double R = 3958.8;  // Radius of Earth in miles
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c;
}
