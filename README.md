# 🗑️ Smart Dustbin with Mobile App Integration

An IoT-based **Smart Dustbin** system that monitors the waste level inside dustbins and sends the data to **Firebase Realtime Database**. The collected data can be accessed through a mobile application to monitor the dustbin status remotely.

This project combines **ESP8266, I2C communication, Firebase, sensors, Wi-Fi, and mobile app integration** to create a smart waste-management solution.

## 📁 Project Resources

🔗 **Project Files / Demo:**
https://drive.google.com/file/d/1fpYc4QTZKnYe-ZgCVtt_8WrRwrdI76mU/view?usp=sharing

---

## 🚀 Features

* 📊 Real-time dustbin fill-level monitoring
* 📱 Mobile application integration
* ☁️ Firebase Realtime Database
* 📡 ESP8266 Wi-Fi connectivity
* 🔄 I2C communication between controllers
* 📈 Fill-level calculation from 0% to 100%
* 🚨 Full-bin detection
* ⏱️ Automatic Firebase data updates
* 🗑️ Supports multiple dustbins
* 🌐 Remote monitoring through the mobile application

---

## 🛠️ Technologies Used

* **ESP8266 NodeMCU**
* **Arduino IDE**
* **C**
* **I2C Communication**
* **Wi-Fi**
* **Firebase Realtime Database**
* **Firebase Authentication**
* **Mobile Application**

---

## 🔧 Hardware Components

* ESP8266 NodeMCU
* Ultrasonic/Distance Sensor
* Microcontroller for sensor processing
* Smart Dustbin
* Jumper Wires
* Power Supply
* Smartphone
* Optional LCD/OLED Display

---

## ⚙️ Working Principle

The distance sensor measures the distance between the top of the dustbin and the waste.

The sensor controller sends the measured value to the ESP8266 using **I2C communication**.

The ESP8266 then:

1. Connects to Wi-Fi.
2. Receives the distance value through I2C.
3. Calculates the dustbin fill percentage.
4. Connects to Firebase.
5. Uploads the fill level to Firebase Realtime Database.
6. The mobile application reads the Firebase data.
7. The user can monitor the dustbin level remotely.

### System Flow

```text
Distance Sensor
       │
       ▼
Sensor Controller
       │
       │ I2C
       ▼
    ESP8266
       │
       │ Wi-Fi
       ▼
Firebase Realtime Database
       │
       │ Internet
       ▼
   Mobile App
       │
       ▼
Dustbin Fill Level
```

---

## 📱 Application

The mobile application retrieves the dustbin fill-level data from Firebase and displays the current status to the user.

This allows users to remotely monitor multiple smart dustbins and identify bins that require emptying.



---

## 👨‍💻 Conclusion

This project demonstrates the integration of **IoT, embedded systems, cloud databases, sensors, and mobile applications** for smart waste-management.
