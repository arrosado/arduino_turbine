
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SetupTimeSystem();
  SetupTemperatureSystem();
  SetupTorqueSystem();
  SetupRPMSystem();

  Serial.println("");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  GetTime();
  GetTemperature();
  GetTourque();
  GetRPM();
  
  Serial.println("");
}

