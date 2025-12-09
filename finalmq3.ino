#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

String apiUrl = "https://co2-api-render.onrender.com/update";  // your render link

int sensorPin = 34; // analog pin for MQ sensor

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  HTTPClient http;
  http.begin(apiUrl);
  http.addHeader("Content-Type", "application/json");

  String json = "{\"value\": " + String(sensorValue) + "}";

  int response = http.POST(json);
  Serial.println("Sent value: " + String(sensorValue) + " | Response: " + String(response));

  http.end();
  delay(1000);
}
