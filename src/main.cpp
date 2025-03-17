#include "adsb_parser.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Function to handle ADS-B data retrieval
void adsb_worker(std::vector<Aircraft>& aircrafts) {
    initialize_adsb();
    
    while (true) {
        aircrafts = fetch_adsb_data();
        aircrafts = filter_aircrafts(aircrafts);
        store_data(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Update every 10s
    }
}

// Function to handle displaying aircraft information
void display_worker(const std::vector<Aircraft>& aircrafts) {
    std::cout << "\n===== Flight Information =====\n";
    for (const auto& ac : aircrafts) {
        std::cout << "Flight: " << ac.flight << " | Alt: " << ac.altitude 
                  << " ft | Speed: " << ac.speed << " knots\n";
    }
    std::cout << "==============================\n";
}

int main() {
    log_message("Initializing ADS-B data processing...");
    std::vector<Aircraft> aircrafts;

    // Launch data processing thread
    std::thread adsb_thread(adsb_worker, std::ref(aircrafts));

    while (true) {
        display_worker(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Refresh display every 5s
    }

    adsb_thread.join();
    return 0;
}
