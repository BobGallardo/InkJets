#include "adsb_parser.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp> // Ensure this library is installed and included

using json = nlohmann::json;

void initialize_adsb() {
    std::cout << "Initializing ADS-B data processing..." << std::endl;
}

// Function to fetch ADS-B data (mock implementation)
std::vector<Aircraft> fetch_adsb_data() {
    std::vector<Aircraft> aircrafts;

    // Read ADS-B JSON data from file (mockup)
    std::ifstream file("mock_adsb_data.json");
    if (!file.is_open()) {
        log_message("Error: Could not open ADS-B data file.");
        return aircrafts;
    }

    json adsb_json;
    file >> adsb_json;
    file.close();

    try {
        for (const auto& aircraft : adsb_json["aircraft"]) {
            Aircraft a;
            a.hex = aircraft["hex"];
            a.flight = aircraft["flight"];
            a.altitude = aircraft["alt_baro"];
            a.speed = aircraft["gs"];
            a.lat = aircraft["lat"];
            a.lon = aircraft["lon"];
            a.heading = aircraft["track"];
            aircrafts.push_back(a);
        }
    } catch (const std::exception& e) {
        log_message(std::string("Error parsing ADS-B JSON: ") + e.what());
    }

    return aircrafts;
}

// Function to filter aircraft within a 25-mile radius
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts) {
    std::vector<Aircraft> filtered;
    double home_lat = 37.7749; // Example coordinates (San Francisco)
    double home_lon = -122.4194;
    const double radius_miles = 25.0;

    for (const auto& a : aircrafts) {
        double distance = std::sqrt(std::pow(a.lat - home_lat, 2) + std::pow(a.lon - home_lon, 2));
        if (distance <= radius_miles) {
            filtered.push_back(a);
        }
    }

    return filtered;
}

// Function to store aircraft data in a file for caching
void store_data(const std::vector<Aircraft>& aircrafts) {
    std::ofstream file("aircraft_cache.txt");
    if (!file.is_open()) {
        log_message("Error: Could not write to aircraft_cache.txt.");
        return;
    }

    for (const auto& a : aircrafts) {
        file << a.hex << "," << a.flight << "," << a.altitude << "," << a.speed << ","
             << a.lat << "," << a.lon << "," << a.heading << "\n";
    }

    file.close();
}
