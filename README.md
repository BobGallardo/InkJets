# **ADS-B E-Ink Flight Display**  

## **Project Overview**  
This project is a **C++ application** designed to run on a **Raspberry Pi** with an **ADS-B USB adapter** and an **e-ink display**. It captures live flight data from aircraft within a **25-mile radius** of a fixed location and displays relevant flight information on an e-ink screen.  

This project is a **gift** for my wife, who enjoys looking up information about planes that fly overhead.

---

## **Hardware Requirements**  
- **Raspberry Pi** (Pi 4, Pi 5, or Raspberry Pi 500)  
- **ADS-B USB Adapter** (e.g., RTL-SDR dongle with an appropriate antenna)  
- **E-Ink Display** (e.g., Waveshare 7.5" e-paper display)  
- **MicroSD Card** (for Raspberry Pi OS)  
- **Power Supply** (suitable for Raspberry Pi model)  

---

## **Software Components**  

### **1. ADS-B Data Source**  
- **`dump1090` or `readsb`** will process raw ADS-B signals from the USB adapter.  
- A **C++ parser** will extract relevant flight data from the output.  

### **2. Flight Data Processing**  
- The application will **filter aircraft within a 25-mile radius** of a defined home GPS coordinate.  
- Extract key details such as:  
  - Flight Number  
  - Aircraft Type  
  - Altitude  
  - Speed  
  - Heading  
- A lightweight **SQLite database** may be used for caching or storing flight history.  

### **3. E-Ink Display Integration**  
- The display will be **updated periodically** (e.g., every minute).  
- It will communicate over **SPI/I2C**, using a **C++ driver** to manage rendering.  
- The interface will be optimized to minimize **ghosting and refresh delays**.  

### **4. C++ Development**  
- **Multithreading** will be used to separate ADS-B data processing and e-ink updates.  
- **Memory and CPU efficiency** will be prioritized to ensure smooth operation on a Raspberry Pi.  
- **Logging & Debugging** will be implemented for easy monitoring and troubleshooting.  

---

## **Setup Instructions**  

### **1. Install Dependencies**  
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install git build-essential cmake sqlite3 libsqlite3-dev
```

### **2. Clone Repository**  
```bash
git clone https://github.com/YOUR_GITHUB_USERNAME/ads-b-eink-display.git
cd ads-b-eink-display
```

### **3. Install `dump1090` or `readsb`**  
```bash
sudo apt install dump1090-fa
```
or  
```bash
git clone https://github.com/wiedehopf/readsb.git
cd readsb
make -j4
sudo make install
```

### **4. Configure SPI/I2C for E-Ink Display**  
```bash
sudo raspi-config  # Enable SPI and I2C
```

### **5. Compile and Run the Application**  
```bash
mkdir build && cd build
cmake ..
make
./adsb_display
```

---

## **Future Enhancements**  
- **Live Flight Info:** Integrate with an online API (e.g., ADS-B Exchange or FlightAware).  
- **Weather Integration:** Display local weather alongside flight data.  
- **Historical Data:** Store flight logs to analyze past flights.  

---

## **License**  
This project is released under the MIT License.  
