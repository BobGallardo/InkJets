#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "adsb_parser.h"

// Logging function
void log_message(const std::string& message);

// Function to retrieve stored aircraft data
std::vector<Aircraft> load_cached_data();

#endif // UTILS_H
