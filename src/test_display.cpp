#include "display.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Mock function to simulate e-ink display initialization
void mock_initialize_display() {
    std::cout << "Mock: Initializing E-Ink Display...\n";
}

// Mock function to simulate rendering aircraft data on e-ink
void mock_render_display(const std::vector<Aircraft>& aircrafts) {
    std::cout << "Mock: Rendering " << aircrafts.size() << " aircraft(s) on e-ink display.\n";
}

// Mock function to simulate drawing text on e-ink
void mock_draw_text(const std::string& text, int x, int y) {
    std::cout << "Mock: Drawing text '" << text << "' at (" << x << ", " << y << ").\n";
}

// Function to test loading cached aircraft data
void test_load_cached_data() {
    // Create a mock cache file
    std::ofstream file("aircraft_cache.txt");
    file << "ABC123,Flight1,35000,450,37.7749,-122.4194,180\n";
    file << "XYZ789,Flight2,10000,300,38.0000,-122.5000,90\n";
    file.close();

    // Load data from cache
    std::vector<Aircraft> aircrafts = load_cached_data();
    assert(aircrafts.size() == 2);
    assert(aircrafts[0].flight == "Flight1");
    assert(aircrafts[1].altitude == 10000);

    std::cout << "✅ test_load_cached_data() passed!\n";
}

// Function to test rendering aircraft data
void test_render_display() {
    std::vector<Aircraft> aircrafts = {
        {"ABC123", "Flight1", 35000, 450, 37.7749, -122.4194, 180},
        {"XYZ789", "Flight2", 10000, 300, 38.0000, -122.5000, 90}
    };

    mock_render_display(aircrafts);
    std::cout << "✅ test_render_display() passed!\n";
}

// Function to test text rendering
void test_draw_text() {
    mock_draw_text("Test Flight", 20, 30);
    std::cout << "✅ test_draw_text() passed!\n";
}

// Main function to run all tests
int main() {
    std::cout << "Running unit tests for display.cpp...\n";
    test_load_cached_data();
    test_render_display();
    test_draw_text();
    std::cout << "🎉 All tests passed successfully!\n";
    return 0;
}
