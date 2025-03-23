#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(5,4);

const char *ssid = "sureshkumar";
const char *password = "sreshta123";

void setup() {

  delay(1000);
  Serial.begin(115200);
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
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void  loop() {

Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(),  HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float  energy = pzem.energy();
    float frequency = pzem.frequency();
    float  pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } 
    if (isnan(current))  {
        Serial.println("Error reading current");
    } 
    if (isnan(power))  {
        Serial.println("Error reading power");
    } 
    if (isnan(energy))  { 
        Serial.println("Error reading energy");
    } 
    if (isnan(frequency))  {
        Serial.println("Error reading frequency");
    } 
    if (isnan(pf))  {
        Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage:  ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current:  ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power:  ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy:  ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency:  ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF:  ");           Serial.println(pf);

    }
  
  delay(5000);  //Post  Data at every 5 seconds
}
