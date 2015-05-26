#include <Time.h>

const int GRN = 12;
const int VCC = 10;
const int SIG = 0;

volatile byte REV; // Volatile data type to store revolutions
unsigned long int rpm, maxRPM; 
unsigned long time; 
int ledPin = 12; 
int led = 0, RPMlen, prevRPM; // Integers to store led value and current rpm and previous rpm
long prevtime = 0; // Store idle time to toggle menu

long fakeRPM = 200;
long MAX_FAKE_RPM = 100000;

void SetupRPMSystem()
{
  // Print header for csv log file.
  Serial.print("RPM,");

	attachInterrupt(SIG, RPMCount, RISING); // Add high priority action (interrupt) when the sensor goes from low to high
	REV = 0;
	rpm = 0;
	time = 0;
	pinMode(ledPin, OUTPUT);
	pinMode(VCC, OUTPUT);
	pinMode(GRN, OUTPUT);
	digitalWrite(VCC, HIGH); // VCC pin for sensor
	digitalWrite(GRN, LOW); // GND pin for sensor
}

void GetRPM()
{
  if (fakeRPM < MAX_FAKE_RPM)
    fakeRPM+=300;
    
  Serial.print(fakeRPM);
  
  long currtime = millis();
  long idletime = currtime - prevtime;

  if (REV >= 5) 
  {
    rpm = 30*1000/(millis() - time)*REV;

    if (rpm > maxRPM)
      maxRPM = rpm;

      time = millis();

      REV = 0;

      int x = rpm;
      while (x!=0)
      {
        x = x/10;
        RPMlen++;
      }

      if (RPMlen!=prevRPM)
      {
        prevRPM = RPMlen;
      }

      //Serial.print(rpm);

      //delay(500);

      prevtime = currtime;
  }
/*
  if (idletime > 5000)
  {
    Serial.println("IDLE STATE");
    Serial.println("READY TO MEASURE");
    delay(2000);
    prevtime = currtime;
  }
*/
  Serial.print(",");
}

void RPMCount() // Everytime when the sensor goes from low to high, this function will be invoked
{
	REV++;

	if (led == LOW)
	{
		led = HIGH; // Toggle status led
	}
	else
	{
		led = LOW;
	}
	digitalWrite(ledPin, led);
}
