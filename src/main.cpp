#include "adsb_parser.h"
#include "utils.h"
#include "display.h"
#include "crow.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

// Global flags and location variables
bool WEB_MODE = false;  // Enable web mode when `--web` is passed

/**
 * Fetches live ADS-B data, filters aircraft within a set distance, and stores results.
 */
void adsb_worker(std::vector<Aircraft>& aircrafts) {
    while (true) {
        aircrafts = fetch_adsb_data();  // Get live aircraft data
        aircrafts = filter_aircrafts(aircrafts, HOME_LAT, HOME_LON);  // Filter by location
        store_data(aircrafts);  // Cache filtered aircraft data

        std::this_thread::sleep_for(std::chrono::seconds(10));  // Fetch new data every 10 sec
    }
}

/**
 * Displays aircraft data either on console or web, depending on mode.
 */
void display_worker(const std::vector<Aircraft>& aircrafts) {
    if (!WEB_MODE) {
        render_display(aircrafts);  // Show aircraft data in console using ncurses
    }
}

/**
 * Starts the web server using Crow to serve ADS-B data in JSON format.
 */
void start_web_server(std::vector<Aircraft>& aircrafts) {
    crow::SimpleApp app;

    // API Route for fetching flight data
    CROW_ROUTE(app, "/api/flights").methods(crow::HTTPMethod::GET)([&aircrafts]() {
        crow::json::wvalue json_response;
        std::vector<crow::json::wvalue> flight_list;

        for (const auto& ac : aircrafts) {
            crow::json::wvalue flight;
            flight["flight"] = ac.flight.empty() ? "Unknown" : ac.flight;
            flight["altitude"] = ac.altitude;
            flight["speed"] = ac.speed;
            flight["latitude"] = ac.latitude;
            flight["longitude"] = ac.longitude;
            flight_list.push_back(std::move(flight));
        }
        json_response["flights"] = std::move(flight_list);
        return crow::response{crow::status::OK, json_response};
    });

    // Route to serve the map
    CROW_ROUTE(app, "/map")
    .methods(crow::HTTPMethod::GET)
    ([]() {
        return crow::response{crow::status::OK, R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>InkJets Flight Tracker</title>
                <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.3/dist/leaflet.css" />
                <script src="https://unpkg.com/leaflet@1.9.3/dist/leaflet.js"></script>
                <style>
                    #map { height: 100vh; width: 100%; }
                </style>
            </head>
            <body>
                <h1>InkJets ADS-B Flight Tracker</h1>
                <div id="map"></div>
                <script>
                    const map = L.map('map').setView([37.3243, -122.0561], 10);
                    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                        attribution: '&copy; OpenStreetMap contributors'
                    }).addTo(map);

                    async function fetchFlights() {
                        const response = await fetch('/api/flights');
                        const data = await response.json();
                        map.eachLayer(layer => { if (layer instanceof L.Marker) map.removeLayer(layer); });

                        data.flights.forEach(flight => {
                            const marker = L.marker([flight.latitude, flight.longitude]).addTo(map);
                            marker.bindPopup(`<b>${flight.flight}</b><br>Altitude: ${flight.altitude} ft<br>Speed: ${flight.speed} knots`);
                        });
                    }

                    fetchFlights();
                    setInterval(fetchFlights, 5000);
                </script>
            </body>
            </html>
        )"};
    });

    log_message("Starting web server on port 9000...");
    app.port(9000).multithreaded().run();
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments for lat/lon and output mode
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--lat" && i + 1 < argc) {
            HOME_LAT = std::stod(argv[++i]);
        } else if (arg == "--lon" && i + 1 < argc) {
            HOME_LON = std::stod(argv[++i]);
        } else if (arg == "--web") {
            WEB_MODE = true;
        }
    }

    log_message("Using home coordinates: " + std::to_string(HOME_LAT) + ", " + std::to_string(HOME_LON));

    // Start ADS-B worker in a separate thread
    std::vector<Aircraft> aircrafts;
    std::thread adsbThread(adsb_worker, std::ref(aircrafts));

    if (WEB_MODE) {
        start_web_server(aircrafts);
    } else {
        initialize_display();
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            display_worker(aircrafts);
        }
        close_display();
    }

    adsbThread.join();
    return 0;
}
