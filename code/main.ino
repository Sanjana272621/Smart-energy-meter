#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(5, 4);
ESP8266WebServer server(80); // Create a web server on port 80

// WiFi credentials
const char *ssid = "abc"; //enter your ssid
const char *password = "123"; //enter your password

// Variables to store the latest readings
float voltage = 0;
float current = 0;
float power = 0;
float energy = 0;
float frequency = 0;
float pf = 0;

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);       
  WiFi.begin(ssid, password);     
  Serial.println("");
  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // IP address assigned to your ESP
  
  // Set up web server routes
  server.on("/", handleRoot);      // Main page
  server.on("/data", handleData);  // JSON endpoint for data updates
  server.on("/reset", handleReset); // Reset energy counter
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
  
  // Read the data from the sensor
  updateReadings();
  
  // Small delay
  delay(2000);
}

void updateReadings() {
  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();
  frequency = pzem.frequency();
  pf = pzem.pf();
  
  // Print to serial for debugging
  if (!isnan(voltage) && !isnan(current) && !isnan(power) && 
      !isnan(energy) && !isnan(frequency) && !isnan(pf)) {
    
    Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
    Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
    Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
    Serial.print("Energy: ");       Serial.print(energy, 3);    Serial.println("kWh");
    Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
    Serial.print("PF: ");           Serial.println(pf);
  }
}

void handleRoot() {
  String html = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                  "<title>Smart Energy Meter</title>"
                  "<style>"
                    "body { font-family: Arial, sans-serif; text-align: center; margin: 0; padding: 20px; background-color: #f4f4f4; }"
                    ".container { max-width: 800px; margin: 0 auto; background-color: white; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }"
                    "h1 { color: #2c3e50; }"
                    ".gauge-container { display: flex; flex-wrap: wrap; justify-content: center; gap: 20px; margin-top: 20px; }"
                    ".gauge { background-color: #ecf0f1; padding: 15px; border-radius: 8px; width: 200px; margin-bottom: 15px; }"
                    ".value { font-size: 24px; font-weight: bold; color: #3498db; margin: 10px 0; }"
                    ".unit { font-size: 14px; color: #7f8c8d; }"
                    "button { background-color: #3498db; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; margin-top: 20px; }"
                    "button:hover { background-color: #2980b9; }"
                  "</style>"
                "</head>"
                "<body>"
                  "<div class='container'>"
                    "<h1>Smart Energy Meter Dashboard</h1>"
                    "<div class='gauge-container'>"
                      "<div class='gauge'>"
                        "<h3>Voltage</h3>"
                        "<div id='voltage' class='value'>0</div>"
                        "<div class='unit'>Volts</div>"
                      "</div>"
                      "<div class='gauge'>"
                        "<h3>Current</h3>"
                        "<div id='current' class='value'>0</div>"
                        "<div class='unit'>Amps</div>"
                      "</div>"
                      "<div class='gauge'>"
                        "<h3>Power</h3>"
                        "<div id='power' class='value'>0</div>"
                        "<div class='unit'>Watts</div>"
                      "</div>"
                      "<div class='gauge'>"
                        "<h3>Energy</h3>"
                        "<div id='energy' class='value'>0</div>"
                        "<div class='unit'>kWh</div>"
                      "</div>"
                      "<div class='gauge'>"
                        "<h3>Frequency</h3>"
                        "<div id='frequency' class='value'>0</div>"
                        "<div class='unit'>Hz</div>"
                      "</div>"
                      "<div class='gauge'>"
                        "<h3>Power Factor</h3>"
                        "<div id='pf' class='value'>0</div>"
                        "<div class='unit'>PF</div>"
                      "</div>"
                    "</div>"
                    "<button onclick='resetEnergy()'>Reset Energy Counter</button>"
                  "</div>"
                  "<script>"
                    "function updateValues() {"
                      "fetch('/data')"
                        ".then(response => response.json())"
                        ".then(data => {"
                          "document.getElementById('voltage').textContent = data.voltage.toFixed(1);"
                          "document.getElementById('current').textContent = data.current.toFixed(3);"
                          "document.getElementById('power').textContent = data.power.toFixed(1);"
                          "document.getElementById('energy').textContent = data.energy.toFixed(3);"
                          "document.getElementById('frequency').textContent = data.frequency.toFixed(1);"
                          "document.getElementById('pf').textContent = data.pf.toFixed(2);"
                        "});"
                    "}"
                    "function resetEnergy() {"
                      "fetch('/reset')"
                        ".then(response => response.text())"
                        ".then(data => {"
                          "alert(data);"
                          "updateValues();"
                        "});"
                    "}"
                    "// Update values every 3 seconds"
                    "setInterval(updateValues, 3000);"
                    "// Initial update"
                    "updateValues();"
                  "</script>"
                "</body>"
                "</html>";
  
  server.send(200, "text/html", html);
}

void handleData() {
  // Create a JSON string with the latest readings
  String json = "{";
  json += "\"voltage\":" + String(isnan(voltage) ? 0 : voltage) + ",";
  json += "\"current\":" + String(isnan(current) ? 0 : current) + ",";
  json += "\"power\":" + String(isnan(power) ? 0 : power) + ",";
  json += "\"energy\":" + String(isnan(energy) ? 0 : energy) + ",";
  json += "\"frequency\":" + String(isnan(frequency) ? 0 : frequency) + ",";
  json += "\"pf\":" + String(isnan(pf) ? 0 : pf);
  json += "}";
  
  server.send(200, "application/json", json);
}

void handleReset() {
  pzem.resetEnergy();
  server.send(200, "text/plain", "Energy counter reset successfully");
}
