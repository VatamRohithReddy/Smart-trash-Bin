#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// WiFi and Firebase configuration
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "88888888"
#define API_KEY "AIzaSyBjtSX01P4dC0XiSkshnfqPXWmsgjdIrQs"
#define DATABASE_URL "https://smart-trashbin-50572-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variables
unsigned long sendDataPrevMillis = 0;
int rawFillLevelBin1 = 0;
int fillLevelPercentageBin1 = 0;
const int maxHeight = 27; 
const int thresholdDistance = 5; // Distance in cm below which bin is considered full (100%)

void setup() {
    Serial.begin(115200);
    Wire.begin(D2, D1);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nConnected to WiFi");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase anonymous authentication successful.");
    } else {
        Serial.print("Firebase anonymous authentication failed, ");
        Serial.print("Error code: ");
        Serial.println(config.signer.signupError.code);
        Serial.print("Error message: ");
        Serial.println(config.signer.signupError.message.c_str());
    }
}

void loop() {
    unsigned long currentMillis = millis();
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();
        // Request fill level for Bin1 (I2C address 8)
        Wire.requestFrom(8, 1);
        if (Wire.available()) {
            rawFillLevelBin1 = Wire.read(); // Read raw fill level data for Bin1
        }
        // Calculate fill level percentage
        if (rawFillLevelBin1 < thresholdDistance) {
            fillLevelPercentageBin1 = 100; // Full bin
        } else {
            fillLevelPercentageBin1 = (int)(((float)(maxHeight - rawFillLevelBin1) / maxHeight) * 100.0);
            fillLevelPercentageBin1 = constrain(fillLevelPercentageBin1, 0, 100); // Constrain between 0% and 100%
        }
        Serial.println("Bin1 Fill Level: " + String(fillLevelPercentageBin1) + "%");
        // Push Bin1 data to Firebase
        if (Firebase.RTDB.setInt(&fbdo, "/SmartTrashBin/Bin2/fillLevel", fillLevelPercentageBin1)) {
            Serial.println("Bin1 fill level data sent to Firebase.");
        } else {
            Serial.println("Failed to send Bin1 fill level data: " + fbdo.errorReason());
        }
    }
}
