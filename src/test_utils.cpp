#include "utils.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Function to test knots_to_mph()
void test_knots_to_mph() {
    assert(knots_to_mph(0) == 0);
    assert(knots_to_mph(10) > 11.5 && knots_to_mph(10) < 11.6); // 11.5078 mph
    assert(knots_to_mph(100) > 115.0 && knots_to_mph(100) < 116.0); // ~115.078 mph
    std::cout << "✅ test_knots_to_mph() passed!\n";
}

// Function to test format_altitude()
void test_format_altitude() {
    assert(format_altitude(0) == "Ground");
    assert(format_altitude(30000) == "30000 ft");
    assert(format_altitude(100) == "100 ft");
    std::cout << "✅ test_format_altitude() passed!\n";
}

// Function to test get_current_time()
void test_get_current_time() {
    std::string timestamp = get_current_time();
    assert(timestamp.length() == 19);  // Format: YYYY-MM-DD HH:MM:SS
    std::cout << "✅ test_get_current_time() passed!\n";
}

// Function to test log_message()
void test_log_message() {
    log_message("Test log entry");

    // Verify the log file exists and contains the message
    std::ifstream log_file("inkjets.log");
    assert(log_file.is_open());

    std::string line;
    bool found = false;
    while (std::getline(log_file, line)) {
        if (line.find("Test log entry") != std::string::npos) {
            found = true;
            break;
        }
    }
    log_file.close();

    assert(found);
    std::cout << "✅ test_log_message() passed!\n";
}

// Main function to run all tests
int main() {
    std::cout << "Running unit tests for utils.cpp...\n";
    test_knots_to_mph();
    test_format_altitude();
    test_get_current_time();
    test_log_message();
    std::cout << "🎉 All tests passed successfully!\n";
    return 0;
}
