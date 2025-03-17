#include "adsb_parser.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp>  // JSON parsing library

using json = nlohmann::json;

/**
 * Fetches ADS-B data from the aircraft.json file and parses it into a vector of Aircraft.
 */
std::vector<Aircraft> fetch_adsb_data() {
    std::vector<Aircraft> aircrafts;
    std::ifstream file("/run/dump1090-fa/aircraft.json");
    if (!file.is_open()) {
        log_message("[ERROR] Could not open live ADS-B data file: /run/dump1090-fa/aircraft.json");
        return aircrafts;
    }
    
    json data;
    file >> data;
    file.close();
    
    if (data.contains("aircraft")) {
        for (const auto& ac : data["aircraft"]) {
            Aircraft aircraft;
            aircraft.flight = ac.value("flight", "Unknown");
            aircraft.altitude = ac.value("alt_baro", 0);
            aircraft.speed = ac.value("gs", 0);
            aircraft.latitude = ac.value("lat", 0.0);
            aircraft.longitude = ac.value("lon", 0.0);
            
            if (aircraft.latitude != 0.0 && aircraft.longitude != 0.0) {
                aircrafts.push_back(aircraft);
            }
        }
    }
    
    log_message("[INFO] Successfully loaded live ADS-B aircraft data.");
    return aircrafts;
}

/**
 * Filters aircraft that are within a given radius of the home location.
 */
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts, double home_lat, double home_lon) {
    std::vector<Aircraft> filtered;
    
    for (const auto& ac : aircrafts) {
        if (ac.latitude != 0.0 && ac.longitude != 0.0) {
            double distance = calculate_distance(home_lat, home_lon, ac.latitude, ac.longitude);
            if (distance <= 25.0) {  // Filter aircraft within 25 miles
                filtered.push_back(ac);
            }
        }
    }
    
    log_message("[INFO] Filtered " + std::to_string(filtered.size()) + " aircraft within 25 miles.");
    return filtered;
}

/**
 * Saves the aircraft data to a local cache file.
 */
void store_data(const std::vector<Aircraft>& aircrafts) {
    std::ofstream file("aircraft_cache.txt");
    if (!file.is_open()) {
        log_message("[ERROR] Could not write to aircraft_cache.txt.");
        return;
    }
    
    for (const auto& ac : aircrafts) {
        file << ac.flight << " | " << ac.altitude << " ft | " << ac.speed << " knots | "
             << ac.latitude << "," << ac.longitude << "\n";
    }
    
    file.close();
    log_message("[INFO] Successfully wrote aircraft data to cache.");
}

/**
 * Loads aircraft data from the cache file.
 */
std::vector<Aircraft> load_cached_data() {
    std::vector<Aircraft> aircrafts;
    std::ifstream file("aircraft_cache.txt");
    if (!file.is_open()) {
        log_message("[WARNING] Could not open aircraft_cache.txt.");
        return aircrafts;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        Aircraft ac;
        sscanf(line.c_str(), "%s | %d ft | %d knots | %lf,%lf", ac.flight, &ac.altitude, &ac.speed, &ac.latitude, &ac.longitude);
        aircrafts.push_back(ac);
    }
    
    file.close();
    return aircrafts;
}