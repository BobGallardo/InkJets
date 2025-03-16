#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

// Function to convert knots to mph
double knots_to_mph(double knots) {
    return knots * 1.15078;  // 1 knot = 1.15078 mph
}

// Function to format altitude nicely
std::string format_altitude(int altitude) {
    if (altitude == 0) return "Ground";
    return std::to_string(altitude) + " ft";
}

// Function to get the current timestamp
std::string get_current_time() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Function to log messages to a file
void log_message(const std::string& message) {
    std::ofstream log_file("inkjets.log", std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error: Cannot open log file.\n";
        return;
    }
    log_file << "[" << get_current_time() << "] " << message << "\n";
    log_file.close();
}
