# IoT-Based Smart Irrigation System 🌱💧

<p align="center">
  <img src="https://github.com/user-attachments/assets/b72c420d-f046-4ce2-ac90-a65d5dc42242" width="300";">
</p>

## 📌 Project Overview  
This project is an **IoT-Based Smart Irrigation System** using an **ESP8266**, a **DHT sensor** for temperature and humidity monitoring, and a **soil moisture sensor** to detect soil conditions. The system features:  
✅ Real-time **temperature, humidity, and soil moisture** monitoring  
✅ **Relay-controlled pump** that activates when soil moisture is low  
✅ A **web interface** for live data visualization  
✅ Adjustable **moisture threshold** via the web interface  
✅ Runs as a **Wi-Fi Access Point (AP)**, eliminating internet dependency  

## 🚀 Features  
- **ESP8266 Web Server**: Displays sensor data in a structured UI  
- **Dynamic Moisture Threshold**: Users can modify soil moisture levels for pump activation  
- **Mobile-Friendly UI**: Optimized for mobile and desktop views  
- **Real-Time Sensor Updates**: Data refreshes every 5 seconds  

## 🛠️ Hardware Requirements  
- **ESP8266 (NodeMCU or similar)**  
- **DHT11/DHT22 Sensor**  
- **Soil Moisture Sensor**  
- **Relay Module**  
- **Water Pump (optional)**  
- **Power Supply (e.g., 5V or 12V depending on pump requirements)**  

## 📌 Circuit Connections  
| Component           | ESP8266 Pin  |
|--------------------|-------------|
| DHT Sensor (Data)  | D5 (GPIO14)  |
| Soil Moisture Sensor | A0 (Analog)  |
| Relay (Pump Control) | D2 (GPIO4)   |

## 🌐 Web Interface  
The ESP8266 serves a **webpage UI** where users can:  
✔️ **View sensor readings** (Temperature, Humidity, Soil Moisture)  
✔️ **Adjust the soil moisture threshold** for pump activation  
✔️ **See pump status** in real-time  

## 📦 Installation & Setup  
1. **Clone the repository**  
   ```sh
   git clone https://github.com/P-Shreyas543/Iot-Based-Irrigation-System
   cd Iot-Based-Irrigation-System

2. **Upload the Code using Arduino IDE**
- **Install ESP8266 Board Manager**
- **Install required libraries**:
-- **ESPAsyncWebServer, DHT sensor library, Adafruit Unified Sensor**
- **Set Board to NodeMCU 1.0 (ESP-12E Module)**
- **Select the correct COM Port and Upload**

3.**Connect to ESP8266 Access Point**
- **Default WiFi: ESP8266_AP**
- **Password: 12345678**
- **Open Browser and go to:**
-- **http://192.168.4.1**
- **Adjust moisture threshold and monitor real-time data**



