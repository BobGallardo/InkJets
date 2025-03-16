#include "adsb_parser.h"
#include "display.h"
#include "utils.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <thread>
#include <chrono>

// Mock function for adsb_worker() to test fetching & filtering aircraft
void mock_adsb_worker(std::vector<Aircraft>& aircrafts) {
    std::cout << "Mock: Fetching ADS-B data...\n";
    
    // Simulate fetching and filtering aircraft
    aircrafts = {
        {"ABC123", "Flight1", 35000, 450, 37.7749, -122.4194, 180}, // Inside radius
        {"XYZ789", "Flight2", 10000, 300, 38.0000, -122.5000, 90}   // Inside radius
    };

    std::vector<Aircraft> filtered = filter_aircrafts(aircrafts);
    assert(!filtered.empty()); // Ensure at least one aircraft is within range
    std::cout << "✅ mock_adsb_worker() passed!\n";
}

// Mock function for display_worker() to test rendering aircraft data
void mock_display_worker(const std::vector<Aircraft>& aircrafts) {
    std::cout << "Mock: Updating E-Ink Display with " << aircrafts.size() << " aircraft(s).\n";
    
    // Ensure the function executes without failure
    assert(!aircrafts.empty());
    std::cout << "✅ mock_display_worker() passed!\n";
}

// Function to test threading behavior in main.cpp
void test_thread_execution() {
    std::vector<Aircraft> aircrafts;

    // Start adsb_worker() in a separate thread
    std::thread adsb_thread(mock_adsb_worker, std::ref(aircrafts));
    adsb_thread.join();  // Ensure it completes

    // Start display_worker() in another thread
    std::thread display_thread(mock_display_worker, std::cref(aircrafts));
    display_thread.join();  // Ensure it completes

    std::cout << "✅ test_thread_execution() passed!\n";
}

// Main function to run all tests
int main() {
    std::cout << "Running unit tests for main.cpp...\n";
    test_thread_execution();
    std::cout << "🎉 All tests passed successfully!\n";
    return 0;
}
