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

## End-User Setup Instructions

### 1. Update the System
Before installing any packages, update the package lists and upgrade existing packages:
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Install Required Libraries
#### Libraries for ADS-B Data Processing
```bash
sudo apt install librtlsdr-dev libusb-1.0-0-dev
```
- **librtlsdr-dev** – Required for handling ADS-B signals from RTL-SDR dongles.
- **libusb-1.0-0-dev** – Required for interfacing with USB devices.

#### SQLite Support (Optional, for Flight Data Storage)
```bash
sudo apt install sqlite3 libsqlite3-dev
```
- **sqlite3** – Command-line tool for SQLite.
- **libsqlite3-dev** – Development headers for SQLite integration.

#### Libraries for E-Ink Display (SPI/I2C Support)
```bash
sudo apt install libspdlog-dev wiringpi libwiringpi-dev libboost-dev
```
- **wiringpi** – Required for GPIO communication (SPI/I2C support).
- **libwiringpi-dev** – Development headers for WiringPi.
- **libspdlog-dev** – Logging library for debugging.
- **libboost-dev** – Provides additional C++ functionality (may be useful for multithreading or networking).

### 3. Enable SPI/I2C on Raspberry Pi (If Using SPI-Based E-Ink)
```bash
sudo raspi-config
```
Then:
1. Go to **Interfacing Options**
2. Enable **SPI** and **I2C**
3. Reboot the system:
   ```bash
   sudo reboot
   ```

### 4. Clone the Project Repository
Once dependencies are installed, clone the repository:
```bash
git clone https://github.com/YOUR_GITHUB_USERNAME/InkJets.git
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
