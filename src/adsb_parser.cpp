#include "adsb_parser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

// Constants for filtering
const double HOME_LAT = 37.7749;  // Example: San Francisco (Change to your location)
const double HOME_LON = -122.4194;
const double RADIUS_MILES = 25.0;

// Function to execute shell commands and capture output
std::string execute_command(const std::string& command) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    pclose(pipe);
    return result;
}

// Function to fetch raw ADS-B data using dump1090 or readsb
std::vector<Aircraft> fetch_adsb_data() {
    std::vector<Aircraft> aircrafts;

    // Fetch data (Assumes dump1090 is running and provides JSON output)
    std::string adsb_output = execute_command("curl -s http://localhost:8080/data.json");

    if (adsb_output.empty()) {
        std::cerr << "Error: No ADS-B data received.\n";
        return aircrafts;
    }

    // Parse JSON response
    try {
        json adsb_json = json::parse(adsb_output);

        for (const auto& plane : adsb_json) {
            Aircraft a;
            a.hex = plane.value("hex", "");
            a.flight = plane.value("flight", "UNKNOWN");
            a.altitude = plane.value("alt_baro", 0);
            a.speed = plane.value("gs", 0);
            a.lat = plane.value("lat", 0.0);
            a.lon = plane.value("lon", 0.0);
            a.heading = plane.value("track", 0.0);

            if (a.hex.empty()) continue;  // Skip invalid entries

            aircrafts.push_back(a);
        }
    } catch (...) {
        std::cerr << "Error parsing ADS-B JSON data.\n";
    }

    return aircrafts;
}

// Haversine formula for distance calculation
double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    constexpr double R = 3958.8; // Earth radius in miles
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

// Filter aircraft within the 25-mile radius
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts) {
    std::vector<Aircraft> filtered;
    
    for (const auto& a : aircrafts) {
        double distance = haversine_distance(HOME_LAT, HOME_LON, a.lat, a.lon);
        if (distance <= RADIUS_MILES) {
            filtered.push_back(a);
        }
    }
    
    return filtered;
}

// Store filtered data (for display use)
void store_data(const std::vector<Aircraft>& aircrafts) {
    std::ofstream file("aircraft_cache.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open cache file for writing.\n";
        return;
    }

    for (const auto& a : aircrafts) {
        file << a.hex << "," << a.flight << "," << a.altitude << "," 
             << a.speed << "," << a.lat << "," << a.lon << "," << a.heading << "\n";
    }

    file.close();
}
