#include "display.h"
#include <ncurses.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "utils.h"

// Initialize ncurses display
void initialize_display() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
}

// Format numbers with commas (e.g., 12,500 ft)
std::string format_number(int num) {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << num;
    return ss.str();
}

// Render ncurses table for flight data
void render_display(const std::vector<Aircraft>& aircrafts) {
    clear();
    mvprintw(1, 2, "===== Flight Information =====");
    mvprintw(2, 2, "=================================");
    mvprintw(3, 2, "%-10s | %-12s | %-10s | %-20s", "Flight", "Altitude", "Speed", "Location");
    mvprintw(4, 2, "--------------------------------------------------------------");

    int row = 5;
    for (const auto& ac : aircrafts) {
        mvprintw(row++, 2, "%-10s | %-12s | %-10s | %-20s",
                 ac.flight.empty() ? "Unknown" : ac.flight.c_str(),
                 (format_number(ac.altitude) + " ft").c_str(),
                 (format_number(ac.speed) + " knots").c_str(),
                 (std::to_string(ac.latitude) + "," + std::to_string(ac.longitude)).c_str());
    }

    mvprintw(row + 2, 2, "Press 'q' to quit.");
    refresh();
}

// Cleanup ncurses
void close_display() {
    endwin();
}
