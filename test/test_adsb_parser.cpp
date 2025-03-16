#include "adsb_parser.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Mock function to simulate fetching ADS-B data
std::vector<Aircraft> mock_fetch_adsb_data() {
    return {
        {"ABC123", "Flight1", 35000, 450, 37.7749, -122.4194, 180.0},  // Inside radius
        {"XYZ789", "Flight2", 10000, 300, 38.0000, -122.5000, 90.0},  // Inside radius
        {"OUT123", "Flight3", 5000, 250, 39.5000, -120.0000, 45.0}    // Outside radius
    };
}

// Function to test filtering aircraft within the 25-mile radius
void test_filter_aircrafts() {
    std::vector<Aircraft> aircrafts = mock_fetch_adsb_data();
    std::vector<Aircraft> filtered = filter_aircrafts(aircrafts);

    assert(filtered.size() == 2);  // Only two flights are within 25 miles

    std::cout << "✅ test_filter_aircrafts() passed!\n";
}

// Function to test storing aircraft data in a file
void test_store_data() {
    std::vector<Aircraft> aircrafts = mock_fetch_adsb_data();
    store_data(aircrafts);

    std::ifstream file("aircraft_cache.txt");
    assert(file.is_open());

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        count++;
    }
    file.close();

    assert(count == 3);  // Ensure all aircraft entries were written
    std::cout << "✅ test_store_data() passed!\n";
}

// Function to test JSON parsing (Simulating invalid JSON handling)
void test_fetch_adsb_data_invalid_json() {
    std::string invalid_json = "{invalid data}";
    
    try {
        std::ofstream file("mock_data.json");
        file << invalid_json;
        file.close();

        std::vector<Aircraft> aircrafts = fetch_adsb_data();  // Should handle error gracefully

        assert(aircrafts.empty());  // Should return an empty vector on failure
        std::cout << "✅ test_fetch_adsb_data_invalid_json() passed!\n";
    } catch (...) {
        std::cerr << "❌ test_fetch_adsb_data_invalid_json() failed: Exception thrown\n";
    }
}

// Main function to run all tests
int main() {
    std::cout << "Running unit tests for adsb_parser.cpp...\n";
    test_filter_aircrafts();
    test_store_data();
    test_fetch_adsb_data_invalid_json();
    std::cout << "🎉 All tests passed successfully!\n";
    return 0;
}
