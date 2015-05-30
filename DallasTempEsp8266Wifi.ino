#include <OneWire.h>
#include <DallasTemperature.h>

#include "ESP8266WiFi.h"

float oldTemp;

// Data wire is plugged into port 0 on the Arduino
#define ONE_WIRE_BUS 0

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(115200);
  
  Serial.println("\nBooting firmware");
  
  // Start up the library
  sensors.begin();
  
  while(true) {
    sensors.requestTemperatures(); // Send the command to get temperatures
    oldTemp = sensors.getTempCByIndex(0);
    if (oldTemp == -127.00) {
      delay(1000);
    } else {
      break;
    }
  }
      
  Serial.print("Initial temp is ");
  Serial.println(oldTemp);
}

void loop(void) {
      sensors.requestTemperatures(); // Send the command to get temperatures
      float newTemp = sensors.getTempCByIndex(0);

      if (newTemp != oldTemp) {
        char str[40];
        char newTemp_str[6];
      
        dtostrf(newTemp, 4, 2, newTemp_str);
        sprintf(str, "Temperature is %s C", newTemp_str); 
      
        WiFi.softAP(str);
        oldTemp = newTemp; 
      }  
}
