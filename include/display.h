#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include "adsb_parser.h"

// Initialize ncurses display
void initialize_display();

// Render a formatted table of flight data
void render_display(const std::vector<Aircraft>& aircrafts);

// Render an ASCII radar for aircraft positions
void render_ascii_radar(const std::vector<Aircraft>& aircrafts);

// Close ncurses display
void close_display();

#endif // DISPLAY_H
