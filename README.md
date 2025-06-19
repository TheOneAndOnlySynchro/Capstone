# IoT Hydroponics Monitoring System

This project is a simulated IoT system designed to monitor environmental parameters in a garden-like hydroponics setup. The system reads from virtual sensors using an ESP32 microcontroller on Wokwi, sends data to the cloud via Adafruit IO, and visualizes it on a live dashboard.

---

## 💡 Project Features

* Temperature and humidity monitoring using DHT22 sensor
* CO₂ concentration simulation using analog sensor
* Water level detection with float switch
* Visual LED alert for threshold breaches
* Cloud integration using MQTT and Adafruit IO
* Real-time dashboard with charts, gauges, and status indicators

---

## 🔧 Installation and Setup Guide

### 1. Clone the repository

```bash
[https://github.com/TheOneAndOnlySynchro/Capstone.git]
```

### 2. Open Wokwi Simulation

* Go to [Wokwi](https://wokwi.com)
* Click **Import Project**
* Upload the `project.json` and `main.ino` files from the repository

### 3. Configure Adafruit IO

* Create an account at [https://io.adafruit.com](https://io.adafruit.com)
* Create the following **feeds**:

  * `temp`
  * `humidity`
  * `co2`
  * `lowlevel`
  * `alarm`
  * `lights`
* Go to **My Key** and copy your Adafruit IO key

### 4. Update the Code

In `main.ino`, replace the placeholder:

```cpp
const char* aioKey = "YOUR_AIO_KEY";  // Replace with your Adafruit IO key
```

### 5. Run the Simulation

* Press the green play button in Wokwi
* Open Serial Monitor to confirm data is being sent
* View your Adafruit IO dashboard live at [https://io.adafruit.com/YOUR\_USERNAME/dashboards/capstone-project](https://io.adafruit.com/YOUR_USERNAME/dashboards/capstone-project)

---

## 📦 File Structure

```
├── main.ino                # Main ESP32 Program
├── project.json            # Wokwi simulation configuration
├── README.md               # Setup and documentation (this file)
├── Capstone Presentation.pptx       # Project presentation 
```

---

## ✅ Testing Performed

* Normal sensor readings
* Simulated low water and high CO₂ triggers
* Dashboard updates every 10 seconds
* Visual alerts (LED and Adafruit indicator blocks)

---

## 📄 License

This project is provided for educational use under the MIT License.

---
