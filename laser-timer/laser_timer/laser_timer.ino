/*
* Laser timer
* 
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd( 7, 6, 5, 4, 3, 2 );

int cycleDelay = 5; // Millisecondi di delay
int cycleCounter = 0; // Contatore cicli

int lightSensorPin=A0;
int lightSensorValue = 0;

int lightSensorSwitchLevel = 500;

int numberCyclesToShowTime = 50;

int waitLigthSensorOn = 0;

float lastLapTime =0.0;
 
void setup() {
  Serial.begin(9600);
  // Setto il tempo a 0
  cycleCounter=0;
  lightSensorValue=0;
  
  // Setup lcd
  lcd.begin(16,2);
  lcd.print("Timer startup.");
  
  // Attesa primo inizio ciclo
  // Step 1 : Il sensore deve andare a on
  // Step 2 : Il sensore va a off e si parte
  int count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wait sens ON");
  while( true ) {
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    if( lightSensorValue>lightSensorSwitchLevel )
      break;
    Serial.println("Attesa che il sensore si accenda");
    lcd.setCursor(count/10,1);
    lcd.print(".");
    count++;
    if( count> 150 ) {
      count=0;
      for( int i=0; i<16; i++) {
        lcd.setCursor(i,1);
        lcd.print(" ");
      }
    }
  }
  count=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wait sens OFF");
  while( true ) {
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    if( lightSensorValue<=lightSensorSwitchLevel ) {
      cycleCounter=0;
      break;
    }
    Serial.println("Attesa che il sensore si spenga");
    lcd.setCursor(count/10,1);
    lcd.print(".");
    count++;
    if( count> 150 ) {
      count=0;
      for( int i=0; i<16; i++) {
        lcd.setCursor(i,1);
        lcd.print(" ");
      }
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Last Lap :");
  lcd.setCursor(0,1);
  lcd.print("Curr time:");

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
  if( lightSensorValue>=lightSensorSwitchLevel )
    waitLigthSensorOn = 0;
  
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
  
  if( lightSensorStatus==0 && waitLigthSensorOn==0 ) {
    cycleCounter=0;
    waitLigthSensorOn = 1;
    lastLapTime = cycleSeconds;
  }
  displayTimer(cycleSeconds, lastLapTime);
}

void displayTimer(float cycleSeconds, float lastLapTime ) {
   // Data connection
   // Display D4 -> D5
   // Display D5 -> D4
   // Display D6 -> D3
   // Display D7 -> D2
   // Diplay E -> D6 
   // Display RS -> D7
   lcd.setCursor(11,0);
   lcd.print(lastLapTime);
   lcd.setCursor(11,1);
   lcd.print(cycleSeconds);
}

