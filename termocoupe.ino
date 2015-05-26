#include <SPI.h>
#include "Adafruit_MAX31855.h"

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

void SetupTemperatureSystem()
{
	// Print header for csv log file.
	Serial.print("Temperature,");
	
	// wait for MAX chip to stabilize
  	delay(500);
}

void GetTemperature()
{
	double c = thermocouple.readCelsius();
	if (isnan(c)) {
		Serial.println("Something wrong with thermocouple!");
	}
	else 
	{
		Serial.print(c);
		Serial.print(",");
	}
}
