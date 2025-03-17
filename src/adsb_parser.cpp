#include "adsb_parser.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#define ADSB_DATA_FILE "/run/dump1090-fa/aircraft.json"  // Live ADS-B JSON file from dump1090-fa

/**
 * Fetches live ADS-B data from dump1090-fa JSON output.
 * Parses aircraft data and returns a vector of Aircraft objects.
 */
std::vector<Aircraft> fetch_adsb_data() {
    std::vector<Aircraft> aircraft_list;
    std::ifstream file(ADSB_DATA_FILE);

    if (!file) {
        log_message("[ERROR] Could not open live ADS-B data file: " + std::string(ADSB_DATA_FILE));
        return aircraft_list;
    }

    try {
        nlohmann::json jsonData;
        file >> jsonData;

        for (const auto& ac : jsonData["aircraft"]) {
            if (ac.contains("hex") && ac.contains("alt_baro") && ac.contains("gs")) {
                Aircraft aircraft;
                aircraft.hex = ac.value("hex", "UNKNOWN");
                aircraft.altitude = ac.value("alt_baro", 0);
                aircraft.speed = ac.value("gs", 0);
                aircraft.heading = ac.value("track", 0);
                aircraft.flight = ac.value("flight", "N/A");
                aircraft.latitude = ac.value("lat", 0.0);
                aircraft.longitude = ac.value("lon", 0.0);

                aircraft_list.push_back(aircraft);
            }
        }
        log_message("[INFO] Successfully loaded live ADS-B aircraft data.");
    } catch (const std::exception& e) {
        log_message("[ERROR] Failed to parse ADS-B JSON: " + std::string(e.what()));
    }
    return aircraft_list;
}

/**
 * Filters aircraft within a 25-mile radius of a given home location.
 */
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts, double home_lat, double home_lon) {
    std::vector<Aircraft> filtered_list;

    for (const auto& ac : aircrafts) {
        if (ac.latitude != 0.0 && ac.longitude != 0.0) {
            double distance = calculate_distance(home_lat, home_lon, ac.latitude, ac.longitude);
            if (distance <= 25.0) {
                filtered_list.push_back(ac);
            }
        }
    }

    log_message("[INFO] Filtered " + std::to_string(filtered_list.size()) + " aircraft within 25 miles.");
    return filtered_list;
}

/**
 * Stores the most recent aircraft data in a local cache file.
 */
void store_data(const std::vector<Aircraft>& aircrafts) {
    std::ofstream file("aircraft_cache.txt");

    if (!file) {
        log_message("[ERROR] Could not write to aircraft_cache.txt.");
        return;
    }

    for (const auto& ac : aircrafts) {
        file << ac.flight << " | " << ac.altitude << " ft | " << ac.speed << " knots | " << ac.latitude << "," << ac.longitude << "\n";
    }
    log_message("[INFO] Successfully wrote aircraft data to cache.");
}

/**
 * Loads cached aircraft data from the last successful fetch.
 */
std::vector<Aircraft> load_cached_data() {
    std::vector<Aircraft> cached_aircrafts;
    std::ifstream file("aircraft_cache.txt");

    if (!file) {
        log_message("[WARNING] Could not open aircraft_cache.txt.");
        return cached_aircrafts;
    }

    std::string line;
    while (std::getline(file, line)) {
        Aircraft ac;
        sscanf(line.c_str(), "%s | %d ft | %d knots | %lf,%lf", ac.flight, &ac.altitude, &ac.speed, &ac.latitude, &ac.longitude);
        cached_aircrafts.push_back(ac);
    }

    log_message("[INFO] Loaded cached aircraft data.");
    return cached_aircrafts;
}
