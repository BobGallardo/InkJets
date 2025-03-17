#include "adsb_parser.h"
#include "utils.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

/**
 * Fetches live ADS-B data, filters aircraft within 25 miles, and prints results.
 */
void adsb_worker(std::vector<Aircraft>& aircrafts) {
    while (true) {
        aircrafts = fetch_adsb_data();  // Get live aircraft data
        aircrafts = filter_aircrafts(aircrafts, HOME_LAT, HOME_LON);  // Filter by location
        store_data(aircrafts);  // Cache filtered aircraft data

        std::this_thread::sleep_for(std::chrono::seconds(10));  // Fetch new data every 10 sec
    }
}

/**
 * Displays aircraft data to the console.
 */
void display_worker(const std::vector<Aircraft>& aircrafts) {
    std::cout << "\n===== Flight Information =====\n";
    for (const auto& ac : aircrafts) {
        std::cout << "Flight: " << ac.flight 
                  << " | Alt: " << ac.altitude << " ft"
                  << " | Speed: " << ac.speed << " knots"
                  << " | Location: " << ac.latitude << "," << ac.longitude << "\n";
    }
    std::cout << "==============================\n";
}

int main() {
    std::vector<Aircraft> aircrafts;

    std::thread adsbThread(adsb_worker, std::ref(aircrafts));

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        display_worker(aircrafts);  // Show aircraft data in console
    }

    adsbThread.join();
    return 0;
}
