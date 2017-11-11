/*
* Laser timer
* 
*/
int cycleDelay = 5; // Millisecondi di delay
int cycleCounter = 0; // Contatore cicli

int lightSensorPin=A0;
int lightSensorValue = 0;

int lightSensorSwitchLevel = 500;

int numberCyclesToShowTime = 50;

void setup() {
  Serial.begin(9600);
  // Setto il tempo a 0
  cycleCounter=0;
  lightSensorValue=0;
  
  // Attesa primo inizio ciclo
  // Step 1 : Il sensore deve andare a on
  // Step 2 : Il sensore va a off e si parte
  while( true ) {
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    if( lightSensorValue>lightSensorSwitchLevel )
      break;
    Serial.println("Attesa che il sensore si accenda");
  }
  while( true ) {
   delay(cycleDelay);
   lightSensorValue = analogRead(lightSensorPin);
   if( lightSensorValue<=lightSensorSwitchLevel ) {
     cycleCounter=0;
     break;
   }
   Serial.println("Attesa che il sensore si spenga");
  }
}

void loop() {
  // TODO Leggo i centesimi di secondo trascorsi e li stampo a console
  delay(cycleDelay);
  cycleCounter++;
  //Serial.print("Count : ");
  //Serial.print(cycleCounter);
  //Serial.println(".");
  
  // Read light sensor
  lightSensorValue = analogRead(lightSensorPin);
  // Serial.print("Ligth sensor : ");
  // Serial.print(lightSensorValue);
  // Serial.println(".");
  // Check if sensor is on or off
  int lightSensorStatus = 1;
  if( lightSensorValue<lightSensorSwitchLevel )
    lightSensorStatus =0;
  
  // Calcolo dei secondi
  float cycleSeconds = ((float)cycleCounter)/(2*100);
  Serial.print("Seconds : ");
  Serial.print(cycleSeconds);
  Serial.print( " - laser switch value");
  //Serial.print(lightSensorValue);
  if( lightSensorStatus == 1 ) {
    Serial.print(" - Sensor ON");
  } else {
    Serial.print(" - Sensor OFF");
  }
  Serial.println(".");
  
  // Quando il sensore si spegne ricomincio il conteggio e faccio vedere
  // Il tempo per un certo numero di cicli
  if( lightSensorStatus == 0) {
    cycleCounter=0;
  } 
}


