float loadA = 1.36; //kg
int analogvalA = 200;

float loadB = 15.44; //kg
int analogvalB = 600;

float analogValueAverage = 0;

long time = 0;
int timeBetweenReadings = 200; //ms

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("analog, load");
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogValue = analogRead(0);


  Serial.println(analogValue);

  return;

  analogValueAverage = 0.99*analogValueAverage + 0.01*analogValue;

  if (millis() > time + timeBetweenReadings) {
    float load = analogToLoad(analogValueAverage);

    Serial.print(analogValueAverage);
    Serial.print(",");
    Serial.print(load,5);
    Serial.println("");
    time = millis();
  }
  //delay(1000);
}

float analogToLoad(float analogval) {
  float load = mapfloat(analogval, analogvalA, analogvalB, loadA, loadB);
  return load;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min)/(in_max - in_min) + out_min;
}


