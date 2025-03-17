#include "utils.h"
#include <iostream>
#include <fstream>
#include <ctime>

// Log messages with timestamps
void log_message(const std::string& message) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    std::time_t now = std::time(nullptr);
    std::string timeStr = std::ctime(&now);
    timeStr.pop_back(); // Remove newline
    std::cout << "[" << timeStr << "] " << message << std::endl;
    logFile << "[" << timeStr << "] " << message << std::endl;
}
