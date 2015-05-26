int loadCell = 0;                //output from load cell
int analogValue = 0;

const int numReadings = 10;      //determines the number of values in the rolling average
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int rollingAverage = 0;         // the rolling average reading

const int ZERO = 10; // 0 lb
const int ONE_POUND = 3;//93438;
const int THREE_POUNDS = 857; // 3.81 lb

void SetupTorqueSystem()
{
	// Print header for csv log file.
	Serial.print("Torque,");
	
	for (int thisReading = 0; thisReading < numReadings; thisReading++)    //This need to be in the set-up section to aviod resetting the array in the loop
		readings[thisReading] = 0;                                            // initialize all the readings in the array to 0
}

void GetTourque()
{ 
	analogValue = analogRead(loadCell);

	rollingReading();
	Serial.print(rollingAverage/ONE_POUND);
	Serial.print("lbs");
	Serial.print(",");
}

void rollingReading() 
{
	total = total - readings[index];              // subtract the last reading   
	readings[index] = analogRead(loadCell) - ZERO;      // read from the sensor
	total = total + readings[index];             // add the reading to the total:      
	index = index + 1;                          // advance to the next position in the array:
	if (index >= numReadings)                  // if we're at the end of the array wrap around to the beginning
		index = 0;                           
	rollingAverage = total / numReadings;         
	   
	delay(1);                              // delay in between reads for stability            
}
