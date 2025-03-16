#include "display.h"
#include <iostream>

void initialize_display() {
    std::cout << "Console display initialized.\n";
}

void render_display(const std::vector<Aircraft>& aircrafts) {
    std::cout << "\n===== Flight Information =====\n";
    for (const auto& aircraft : aircrafts) {
        std::cout << "Flight: " << aircraft.flight
                  << " | Altitude: " << aircraft.altitude << " ft"
                  << " | Speed: " << aircraft.speed << " knots\n";
    }
    std::cout << "==============================\n";
}
