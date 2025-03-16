# InkJets - ADS-B E-Ink Flight Display

## Project Overview

InkJets is a **C++ application** designed to run on a **Raspberry Pi** with an **ADS-B USB adapter** and an **e-ink display**. It captures live flight data from aircraft within a **25-mile radius** of a fixed location and displays relevant flight information on an e-ink screen. 

This project is a **gift** for my wife, who enjoys looking up information about planes that fly overhead.

---

## Hardware Requirements

- **Raspberry Pi** (Pi 4, Pi 5, or Raspberry Pi 500)  
- **ADS-B USB Adapter** (e.g., RTL-SDR dongle with an appropriate antenna)  
- **E-Ink Display** (e.g., Waveshare 7.5" e-paper display)  
- **MicroSD Card** (for Raspberry Pi OS)  
- **Power Supply** (suitable for Raspberry Pi model)  

---

## Software Components

### 1. ADS-B Data Source
- **`dump1090` or `readsb`** will process raw ADS-B signals from the USB adapter.
- A **C++ parser** will extract relevant flight data from the output.

### 2. Flight Data Processing
- The application will **filter aircraft within a 25-mile radius** of a defined home GPS coordinate.
- Extract key details such as:
  - Flight Number
  - Aircraft Type
  - Altitude
  - Speed
  - Heading
- A lightweight **SQLite database** may be used for caching or storing flight history.

### 3. E-Ink Display Integration
- The display will be **updated periodically** (e.g., every minute).
- It will communicate over **SPI/I2C**, using a **C++ driver** to manage rendering.
- The interface will be optimized to minimize **ghosting and refresh delays**.

### 4. C++ Development
- **Multithreading** will be used to separate ADS-B data processing and e-ink updates.
- **Memory and CPU efficiency** will be prioritized to ensure smooth operation on a Raspberry Pi.
- **Logging & Debugging** will be implemented for easy monitoring and troubleshooting.

---

## Implementation

### 1. Core Components
- **ADS-B Data Retrieval:** Capture real-time aircraft data using `librtlsdr` and `dump1090`.
- **Data Filtering:** Identify aircraft within the 25-mile radius.
- **Data Processing:** Convert ADS-B signals into a structured format.
- **E-Ink Rendering:** Display filtered aircraft data in a readable format.
- **Multithreading:** Ensure smooth operation by handling data retrieval and display updates concurrently.

### 2. Directory Structure
```
InkJets/
├── src/
│   ├── main.cpp  # Entry point
│   ├── adsb_parser.cpp  # Parses ADS-B data
│   ├── display.cpp  # Handles e-ink rendering
│   ├── utils.cpp  # Helper functions
├── include/
│   ├── adsb_parser.h
│   ├── display.h
│   ├── utils.h
├── assets/
│   ├── fonts/  # Font files for e-ink display
│   ├── icons/  # Optional icons for UI
├── CMakeLists.txt  # Build configuration
├── README.md  # Documentation
```

---

## End-User Setup Instructions

### 1. Update the System
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Install Required Libraries
```bash
sudo apt install librtlsdr-dev libusb-1.0-0-dev sqlite3 libsqlite3-dev libspdlog-dev wiringpi libwiringpi-dev libboost-dev
```

### 3. Enable SPI/I2C on Raspberry Pi
```bash
sudo raspi-config
```
- Go to **Interfacing Options**
- Enable **SPI** and **I2C**
- Reboot the system:
```bash
sudo reboot
```

### 4. Clone the Project Repository
```bash
git clone https://github.com/BobGallardo/InkJets.git
cd InkJets
```

### 5. Compile the Project
```bash
mkdir build && cd build
cmake ..
make
```

### 6. Run the Application
```bash
./adsb_display
```

---

## Future Enhancements
- **Live Flight Info:** Integrate with an online API (e.g., ADS-B Exchange or FlightAware).
- **Weather Integration:** Display local weather alongside flight data.
- **Historical Data:** Store flight logs to analyze past flights.

---

## License
This project is released under the MIT License.
