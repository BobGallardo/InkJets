# InkJets

InkJets is a lightweight ADS-B receiver application designed to display real-time aircraft information within a set radius of a given location. It is built for Raspberry Pi but can be compiled on other Linux systems as well.

## Features
- Fetches real-time ADS-B aircraft data from an RTL-SDR dongle.
- Filters aircraft within a specified distance from a home location.
- Displays aircraft data dynamically using `ncurses`.
- Optionally caches aircraft data for offline review.

## Prerequisites
To compile and run `InkJets`, ensure your system meets the following requirements:

### Hardware
- Raspberry Pi (or any Linux system with an RTL-SDR dongle)
- RTL2832U-based SDR USB receiver

### Software
Install the required dependencies:
```sh
sudo apt update && sudo apt install -y git build-essential cmake libncurses5-dev rtl-sdr
```

## Installation
Clone the repository and build the application:
```sh
git clone https://github.com/BobGallardo/InkJets.git
cd InkJets
mkdir build && cd build
cmake ..
make
```

## Running the Application
Run `InkJets` after ensuring the SDR device is properly connected:
```sh
./InkJets
```

## Configuration
Modify the `HOME_LAT` and `HOME_LON` values in `utils.h` to match your desired location:
```cpp
constexpr double HOME_LAT = 37.3243;  // Example: Cupertino, CA
constexpr double HOME_LON = -122.0561;
```

## Troubleshooting
### RTL-SDR Not Detected
If the device is not detected, try:
```sh
sudo systemctl stop dump1090-fa
rtl_test -t
```

### Missing ADS-B Data
Ensure `dump1090-fa` is running and configured correctly:
```sh
sudo systemctl start dump1090-fa
```

## License
InkJets is released under the MIT License.

## Author
Developed by Bob Gallardo.
