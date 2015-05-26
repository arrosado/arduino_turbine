#include <Time.h>

void SetupTimeSystem()
{
	// Print header for csv log file.
	Serial.print("Time,");
}


void GetTime()
{
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(",");
}
