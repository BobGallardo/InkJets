#include "adsb_parser.h"
#include "display.h"
#include "utils.h"
#include <iostream>
#include <thread>
#include <vector>

// Function that handles ADS-B data retrieval
void adsb_worker(std::vector<Aircraft>& aircrafts) {
    initialize_adsb(); // Initialize ADS-B processing
    while (true) {
        aircrafts = fetch_adsb_data();
        aircrafts = filter_aircrafts(aircrafts);
        store_data(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Refresh every 10 sec
    }
}

// Function that handles e-ink display updates
void display_worker(const std::vector<Aircraft>& aircrafts) {
    initialize_display();
    while (true) {
        std::vector<Aircraft> data = load_cached_data();
        render_display(data);
        std::this_thread::sleep_for(std::chrono::minutes(1)); // Update every minute
    }
}

int main() {
    std::vector<Aircraft> aircrafts;

    // Start ADS-B worker in a separate thread
    std::thread adsb_thread(adsb_worker, std::ref(aircrafts));

    // Start display worker in another thread
    std::thread display_thread(display_worker, std::cref(aircrafts));

    // Keep main thread running
    adsb_thread.join();
    display_thread.join();

    return 0;
}