#ifndef ADSB_PARSER_H
#define ADSB_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // Requires json.hpp library

using json = nlohmann::json;

struct Aircraft {
    std::string hex;
    std::string flight;
    int altitude;
    double speed;
    double lat;
    double lon;
    double heading;
};

// Function prototypes
std::vector<Aircraft> fetch_adsb_data();
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts);
void store_data(const std::vector<Aircraft>& aircrafts);

#endif
