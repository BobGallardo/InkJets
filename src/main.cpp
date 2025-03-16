#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "adsb_parser.h"
#include "display.h"
#include "utils.h"

#define REFRESH_INTERVAL 60  // Update display every 60 seconds

// Function to continuously fetch and process ADS-B data
void adsb_worker() {
    while (true) {
        std::vector<Aircraft> aircrafts = fetch_adsb_data();
        filter_aircrafts(aircrafts);
        store_data(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(10));  // Fetch every 10 seconds
    }
}

// Function to periodically update the e-ink display
void display_worker() {
    while (true) {
        std::vector<Aircraft> aircrafts = load_cached_data();
        render_display(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(REFRESH_INTERVAL));
    }
}

int main() {
    std::cout << "InkJets - ADS-B E-Ink Flight Display\n";
    
    // Initialize system components
    initialize_adsb();
    initialize_display();
    
    // Start ADS-B data collection in a separate thread
    std::thread adsb_thread(adsb_worker);
    
    // Start e-ink display update loop in another thread
    std::thread display_thread(display_worker);
    
    // Join threads (keeps program running)
    adsb_thread.join();
    display_thread.join();

    return 0;
}
