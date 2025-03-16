#include "utils.h"
#include <iostream>
#include <fstream>

void log_message(const std::string& message) {
    std::cerr << "[LOG] " << message << std::endl;
}

std::vector<Aircraft> load_cached_data() {
    std::vector<Aircraft> cached_data;
    std::ifstream file("aircraft_cache.txt");

    if (!file.is_open()) {
        log_message("Warning: Could not open aircraft_cache.txt");
        return cached_data;
    }

    Aircraft aircraft;
    while (file >> aircraft.flight >> aircraft.altitude >> aircraft.speed) {
        cached_data.push_back(aircraft);
    }

    file.close();
    return cached_data;
}
