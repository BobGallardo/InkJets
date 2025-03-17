#ifndef ADSB_PARSER_H
#define ADSB_PARSER_H

#include <vector>
#include <string>

// Aircraft structure to hold ADS-B data
struct Aircraft {
    std::string hex;      // Unique aircraft ID
    std::string flight;   // Flight number
    int altitude;         // Altitude in feet
    int speed;            // Speed in knots
    int heading;          // Aircraft heading
    double latitude;      // Aircraft latitude
    double longitude;     // Aircraft longitude
};

// Function declarations
std::vector<Aircraft> fetch_adsb_data();
std::vector<Aircraft> filter_aircrafts(const std::vector<Aircraft>& aircrafts, double home_lat, double home_lon);
void store_data(const std::vector<Aircraft>& aircrafts);
std::vector<Aircraft> load_cached_data();
double calculate_distance(double lat1, double lon1, double lat2, double lon2); // Function prototype added

#endif // ADSB_PARSER_H
