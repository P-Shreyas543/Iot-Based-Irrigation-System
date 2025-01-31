#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 5               // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11          // Change to DHT11 or DHT21 if needed
#define MOISTUREPIN A0         // Analog pin connected to the moisture sensor
#define RELAYPIN 4             // Digital pin for relay

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

float t = 0.0, h = 0.0, moisture = 0.0;
unsigned long previousMillis = 0;
const long interval = 1000;
int rawMoisture = 0;
int moistureThreshold = 30;

const char *ssid = "Irrigation_System";
const char *password = "12345678";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial, text-align: center; padding: 20px; background-color: #f4f4f4; }
    h2 { font-size: 2rem; color: #333; }
    table { width: 90%; margin: 20px auto; border-collapse: collapse; background: white; }
    th, td { padding: 10px; border: 1px solid #ddd; font-size: 1.2rem; }
    th { background: #4CAF50; color: white; }
    td span { font-weight: bold; }
    @media (max-width: 600px) {
      h2 { font-size: 1.5rem; }
      table { width: 100%; }
      th, td { font-size: 1rem; }
    }
  </style>
</head>
<body>
  <h2>IoT Based Irrigation System</h2>
  <table>
    <tr><th>Parameter</th><th>Value</th></tr>
    <tr><td>Temperature</td><td><span id="temperature">--</span>&deg;C</td></tr>
    <tr><td>Humidity</td><td><span id="humidity">--</span>%</td></tr>
    <tr><td>Soil Moisture</td><td><span id="moisture">--</span>%</td></tr>
    <tr><td>Pump Status</td><td><span id="pump_status">OFF</span></td></tr>
  </table>
  <p>Moisture Threshold: <input type="number" id="threshold" value="30" style="width:50px;"/> % <button onclick="setThreshold()">Set</button></p>
  <script>
    function updateData() {
      fetch('/temperature').then(res => res.text()).then(data => document.getElementById("temperature").innerText = data);
      fetch('/humidity').then(res => res.text()).then(data => document.getElementById("humidity").innerText = data);
      fetch('/moisture').then(res => res.text()).then(data => {
        document.getElementById("moisture").innerText = data;
        document.getElementById("pump_status").innerText = data < document.getElementById("threshold").value ? "ON" : "OFF";
      });
    }
    function setThreshold() {
      let value = document.getElementById("threshold").value;
      fetch('/set_threshold?value=' + value);
    }
    setInterval(updateData, 5000);
    updateData();
  </script>
</body>
</html>)rawliteral";

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW);  // Initially turn off relay

  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(t));
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(h));
  });
  server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(moisture));
  });
  server.on("/set_threshold", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      moistureThreshold = request->getParam("value")->value().toInt();
    }
    request->send(200, "text/plain", "Threshold updated");
  });

  server.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    float newH = dht.readHumidity();

    rawMoisture = analogRead(MOISTUREPIN);
    moisture = map(rawMoisture, 1023, 424, 0, 100);  // Convert to percentage

    if ( moisture < moistureThreshold) {
      if (digitalRead(RELAYPIN) == 0) {
        digitalWrite(RELAYPIN, HIGH);
      }
    } else {
      digitalWrite(RELAYPIN, LOW);
    }


    if (!isnan(newT)) t = newT;
    if (!isnan(newH)) h = newH;

    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Soil Moisture: ");
    Serial.println(moisture);
  }

}