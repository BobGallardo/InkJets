#ifndef ADSB_PARSER_H
#define ADSB_PARSER_H

#include <vector>
#include <string>

// Aircraft data structure
struct Aircraft {
    std::string flight;
    int altitude;
    int speed;
    int heading;
};

// Function declarations
void initialize_adsb();
std::vector<Aircraft> fetch_adsb_data();
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts);
void store_data(const std::vector<Aircraft>& aircraftList);

#endif // ADSB_PARSER_H
