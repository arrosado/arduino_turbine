#include <SPI.h>
#include <Time.h>
#include "Adafruit_MAX31855.h"

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Tiempo, Temperatura, RPM, Fuerza");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  GetTime();
  GetTemperature();
  GetRPM();
  GetTourque();
  Serial.println("");

  //Serial.print("F = ");
  //Serial.println(thermocouple.readFarenheit());

  delay(1000);
}

void GetTime()
{
  // ToDo:
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(",");
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

void GetRPM()
{
  //ToDo:
  Serial.print(",");
}

void GetTourque()
{ 
  //ToDo:
  Serial.print(",");
}
