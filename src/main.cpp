#include "adsb_parser.h"
#include "display.h"  // Ensure this is included
#include "utils.h"    // Ensure this is included
#include <iostream>
#include <thread>
#include <vector>

// Function handling ADS-B data retrieval
void adsb_worker(std::vector<Aircraft>& aircrafts) {
    initialize_adsb();
    while (true) {
        aircrafts = fetch_adsb_data();
        aircrafts = filter_aircrafts(aircrafts);
        store_data(aircrafts);
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Refresh every 10 sec
    }
}

// Function handling display updates
void display_worker(const std::vector<Aircraft>& aircrafts) {
    initialize_display();  // Now declared correctly
    while (true) {
        std::vector<Aircraft> data = load_cached_data();  // Now declared correctly
        render_display(data);  // Now declared correctly
        std::this_thread::sleep_for(std::chrono::minutes(1)); // Update every minute
    }
}

int main() {
    std::vector<Aircraft> aircrafts;

    // Start ADS-B worker thread
    std::thread adsb_thread(adsb_worker, std::ref(aircrafts));

    // Start display worker thread
    std::thread display_thread(display_worker, std::cref(aircrafts));

    adsb_thread.join();
    display_thread.join();

    return 0;
}
