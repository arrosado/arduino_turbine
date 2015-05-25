#include <SPI.h>
#include <Time.h>
#include "Adafruit_MAX31855.h"

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

int loadCell = 0;                //output from load cell
int analogValue = 0;

const int numReadings = 10;      //determines the number of values in the rolling average
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int rollingAverage = 0;         // the rolling average reading

const int ZERO = 14; // 0 lb
const int ONE_POUND = 224.93438;
const int THREE_POUNDS = 857; // 3.81 lb


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Tiempo, Temperatura, RPM, Fuerza");
  // wait for MAX chip to stabilize
  delay(500);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++)    //This need to be in the set-up section to aviod resetting the array in the loop
    readings[thisReading] = 0;                                            // initialize all the readings in the array to 0

}

void loop() {
  // put your main code here, to run repeatedly:
  //GetTime();
  //GetTemperature();
  //GetRPM();
  GetTourque();
  Serial.println("");

  


  //Serial.print("F = ");
  //Serial.println(thermocouple.readFarenheit());

  //delay(1000);
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
  analogValue = analogRead(loadCell);
   
    rollingReading();
    Serial.print(analogValue);
    Serial.print(" = ");
    Serial.print(rollingAverage/ONE_POUND);
    Serial.print("lbs");

  Serial.print(",");
}

void rollingReading() {
  total = total - readings[index];              // subtract the last reading   
  readings[index] = analogRead(loadCell) - ZERO;      // read from the sensor
  total = total + readings[index];             // add the reading to the total:      
  index = index + 1;                          // advance to the next position in the array:
  if (index >= numReadings)                  // if we're at the end of the array wrap around to the beginning
    index = 0;                           
  rollingAverage = total / numReadings;         
//  Serial.println(rollingAverage);   
  delay(1);                              // delay in between reads for stability            
}

