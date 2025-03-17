#include "adsb_parser.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Get the directory of the running executable
std::string get_executable_path() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    std::string exePath = (count != -1) ? std::string(result, count) : "";
    size_t lastSlash = exePath.find_last_of("/");
    return (lastSlash == std::string::npos) ? "./" : exePath.substr(0, lastSlash + 1);
}

// Initialize ADS-B processing
void initialize_adsb() {
    log_message("ADS-B system initialized.");
}

// Fetch aircraft data from ADS-B JSON file
std::vector<Aircraft> fetch_adsb_data() {
    std::vector<Aircraft> aircraftList;
    std::string adsbFilePath = get_executable_path() + "adsb_data.json";

    std::ifstream file(adsbFilePath);
    if (!file) {
        log_message("Error: Could not open ADS-B data file at " + adsbFilePath);
        return aircraftList;
    }

    try {
        json adsbData;
        file >> adsbData;

        if (!adsbData.contains("aircraft")) {
            log_message("Warning: No 'aircraft' key found in ADS-B data.");
            return aircraftList;
        }

        for (const auto& ac : adsbData["aircraft"]) {
            Aircraft a;
            a.flight = ac.value("flight", "UNKNOWN");
            a.altitude = ac.value("alt_baro", 0);
            a.speed = ac.value("gs", 0);
            a.heading = ac.value("track", 0);
            aircraftList.push_back(a);
        }
    } catch (const std::exception& e) {
        log_message("Error parsing ADS-B JSON: " + std::string(e.what()));
    }

    return aircraftList;
}

// Filter out invalid or unwanted aircraft
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts) {
    std::vector<Aircraft> filtered;
    for (const auto& ac : aircrafts) {
        if (ac.altitude > 0) { // Only show aircraft above ground
            filtered.push_back(ac);
        }
    }
    return filtered;
}

// Store aircraft data in a cache file
void store_data(const std::vector<Aircraft>& aircraftList) {
    std::string cacheFilePath = get_executable_path() + "aircraft_cache.txt";
    std::ofstream cache(cacheFilePath);
    if (!cache) {
        log_message("Error: Could not write to " + cacheFilePath);
        return;
    }

    for (const auto& ac : aircraftList) {
        cache << ac.flight << ", " << ac.altitude << ", " << ac.speed << ", " << ac.heading << "\n";
    }

    log_message("Successfully wrote aircraft data to cache.");
}
