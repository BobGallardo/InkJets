#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "adsb_parser.h"

// Function prototypes for console output
void initialize_display();
void render_display(const std::vector<Aircraft>& aircrafts);

#endif // DISPLAY_H
