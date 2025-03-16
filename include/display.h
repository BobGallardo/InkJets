#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "adsb_parser.h"  // Aircraft struct

// Function prototypes
void initialize_display();
void render_display(const std::vector<Aircraft>& aircrafts);
void draw_text(const std::string& text, int x, int y);
std::vector<Aircraft> load_cached_data();

#endif