#include "display.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include "epd_driver.h"  // Waveshare EPD driver (ensure you have this library)
#include "utils.h"        // Helper functions (e.g., text formatting)

// Function to read aircraft data from cache
std::vector<Aircraft> load_cached_data() {
    std::vector<Aircraft> aircrafts;
    std::ifstream file("aircraft_cache.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open aircraft cache file.\n";
        return aircrafts;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Aircraft a;
        std::getline(ss, a.hex, ',');
        std::getline(ss, a.flight, ',');
        ss >> a.altitude;
        ss.ignore();
        ss >> a.speed;
        ss.ignore();
        ss >> a.lat;
        ss.ignore();
        ss >> a.lon;
        ss.ignore();
        ss >> a.heading;
        aircrafts.push_back(a);
    }

    file.close();
    return aircrafts;
}

// Function to initialize the e-ink display
void initialize_display() {
    std::cout << "Initializing E-Ink Display...\n";
    if (EPD_Init() != 0) {
        std::cerr << "Error: Failed to initialize e-ink display!\n";
    }
    EPD_Clear();  // Clear the screen before rendering
}

// Function to render aircraft data on the e-ink display
void render_display(const std::vector<Aircraft>& aircrafts) {
    std::cout << "Updating E-Ink Display...\n";
    
    EPD_ClearBuffer();  // Clear screen buffer to prevent ghosting

    if (aircrafts.empty()) {
        draw_text("No aircraft detected", 20, 30);
    } else {
        int y_offset = 20;
        for (const auto& a : aircrafts) {
            std::string info = a.flight + " " + std::to_string(a.altitude) + "ft " + 
                               std::to_string(a.speed) + "kt";
            draw_text(info, 20, y_offset);
            y_offset += 20;
            if (y_offset > 200) break;  // Prevent overflow
        }
    }

    EPD_DisplayBuffer();  // Push buffer to the e-ink screen
}

// Function to draw text on the display
void draw_text(const std::string& text, int x, int y) {
    Paint_DrawStringAt(x, y, text.c_str(), &Font16, BLACK);
}
