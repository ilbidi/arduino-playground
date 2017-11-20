/*
* Laser timer on a 7 segments display
* 
*/

/* 
* Seven segments diplay settings 
*/
// Pin used managed as the part of the led numbers( a,b, ..)
int a = 5;
int b = 4;
int c = 3;
int d = 2;
int e = 7;
int f = 6;
int g = 8;
int p = A2;
int d4 = A3;
int d3 = A4;
int d2 = A5;
int d1 =  A1; // A7;

/*
* Laser beam and sensor
*/
int lightSensorPin=A0;
int laserOnPin=A7;
int laserOn = 0;

/*
* Program settings
*/
int cycleDelay = 5; // Millisecondi di delay
long cycleCounter = 0; // Contatore cicli
long startTimeMillis = 0;
long timeMillis = 0;

int lightSensorValue = 0;

int lightSensorSwitchLevel = 300;

int numberCyclesToShowTime = 300;

int waitLigthSensorOn = 0;

long lastLapTimeMillis = 0;
 
void setup() {
  Serial.begin(9600);
  // Setup 7 segs display
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(p, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(laserOnPin, OUTPUT);

  // Setto il tempo a 0
  cycleCounter=0;
  lightSensorValue=0;
  
  // Calcolo soglia
  int maxValue=0;
  int minValue=0;
  int curMediumValue=0;
  boolean firstCycle=true;
  
  // Try to guess if sensor is high or low
  Serial.println("Wait sensor change over 20%");
  while( true ) {
    displayCal();
    delay(cycleDelay*50);
    lightSensorValue = analogRead(lightSensorPin);
    if( firstCycle ) {
      curMediumValue=lightSensorValue;
      firstCycle=false;
    } else {
      curMediumValue = (curMediumValue+lightSensorValue)/2;
    }   
    Serial.print(lightSensorValue);
    Serial.print("Current Medium Value : ");
    Serial.println(curMediumValue);
    if( lightSensorValue>curMediumValue*1.2 ) {
      // Actual value is higher so 
      minValue=curMediumValue;
      maxValue=lightSensorValue;
      Serial.print("1 Min Value : ");
      Serial.print(minValue);
      Serial.print("1 Max Value : ");
      Serial.println(maxValue);
      break;
    } else if(  lightSensorValue<=curMediumValue*0.8 ) {
      // Actual values is lower so:
      minValue=lightSensorValue;
      maxValue=curMediumValue;      
      Serial.print("2 Min Value : ");
      Serial.print(minValue);
      Serial.print("2 Max Value : ");
      Serial.println(maxValue);
      break;
    }
  }
  lightSensorSwitchLevel=(minValue+maxValue)/2;
  Serial.print("Switch Value : ");
  Serial.println(lightSensorSwitchLevel);
  
    
  // Attesa primo inizio ciclo
  // Step 1 : Il sensore va a off e significa che si è partiti, prima attendiamo che il sensore sia acceso
  Serial.println("Wait sens ON");
  while( true ) {
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    Serial.println(lightSensorValue);
    if( lightSensorValue>lightSensorSwitchLevel )
      break;
    Serial.println("Attesa che il sensore si accenda");
  }
  Serial.println("Wait sens OFF");
  int c=0;
  while( true ) {
    c++;
    displayWait((c/100)%4);
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    Serial.println(lightSensorValue);
    if( lightSensorValue<=lightSensorSwitchLevel ) {
      cycleCounter=0;
      break;
    Serial.println("Attesa che il sensore si spenga");
    }
  }
  
  /*
  Serial.println("Wait Start");
  c=0;
  while( true ) {
    c++;
    delay(cycleDelay);
    lightSensorValue = analogRead(lightSensorPin);
    Serial.println(lightSensorValue);
    if( lightSensorValue<=lightSensorSwitchLevel ) {
      cycleCounter=0;
      break;
    Serial.println("Attesa che il sensore si spenga");
    if(c%100==0) {
      displayTime(8888);
    }
    if(c%200==0) {
      displayTime(1111);
    }
    
    }
  }
  */

  // Reset timer
  startTimeMillis = millis();
  timeMillis = startTimeMillis;
  lastLapTimeMillis = 0;  
}

void loop() {
  // TODO Leggo i centesimi di secondo trascorsi e li stampo a console
  delay(cycleDelay);
  cycleCounter++;
  //Serial.print("Count : ");
  //Serial.print(cycleCounter);
  //Serial.println(".");
  timeMillis = millis();
 
  // Read light sensor
  lightSensorValue = analogRead(lightSensorPin);
  //Serial.print("Ligth sensor : ");
  //Serial.print(lightSensorValue);
  //Serial.println(".");
  // Check if sensor is on or off
  int lightSensorStatus = 1;
   
  if( lightSensorValue<lightSensorSwitchLevel )
    lightSensorStatus =0;
  if( lightSensorValue>=lightSensorSwitchLevel )
    waitLigthSensorOn = 0;
  
  // Calcolo dei millisecondi
  if(timeMillis-startTimeMillis>1000000)
    startTimeMillis=timeMillis;
  long cycleMilliSeconds = (timeMillis-startTimeMillis);
  
  //Serial.print("MilliSeconds : ");
  //Serial.print(cycleMilliSeconds);
  //Serial.print( " - laser switch value");
  //Serial.print(lightSensorValue);
  //if( lightSensorStatus == 1 ) {
  //  Serial.print(" - Sensor ON");
  //} else {     
  //  Serial.print(" - Sensor OFF");
  //}  
  //Serial.println(".");
  
  if( lightSensorStatus==0 && waitLigthSensorOn==0 ) {
    cycleCounter=0;
    startTimeMillis = millis();
    timeMillis = startTimeMillis;
    waitLigthSensorOn = 1;
    lastLapTimeMillis = cycleMilliSeconds;
  }
  
  if( cycleCounter<numberCyclesToShowTime && lastLapTimeMillis > 10 ) {
    displayTime(lastLapTimeMillis);
  } else {
    displayTime(cycleMilliSeconds);
  }
  
  // Test 
  if( (cycleCounter%1000)==0 ) {
    if( laserOn=0 ) {
      digitalWrite(laserOnPin, HIGH);
      laserOn=1;
    } else {
      digitalWrite(laserOnPin, LOW);
      laserOn=0;      
    }
  } 
}

/*====================================================
* Seven segs utils 
*/
void displayTime(long passedTime) {
  int n0 = ((passedTime/10)%100000)/10000;
  int n1 = ((passedTime/10)%10000)/1000;
  int n2 = ((passedTime/10)%1000)/100;
  int n3 = ((passedTime/10)%100)/10;
  int n4 = (passedTime/10)%10;
  
  int dly = 3;

/*  
  Serial.print("Passed time : ");
  Serial.println(passedTime);
  Serial.print("n0 : ");
  Serial.println(n0);
  Serial.print("n1 : ");
  Serial.println(n1);
  Serial.print("n2 : ");
  Serial.println(n2);
  Serial.print("n3 : ");
  Serial.println(n3);
  Serial.print("n4 : ");
  Serial.println(n4);
*/

  clearDisplay();
  pickDigit(0);
  pickNumber(n0, false);
  delay(dly);
  clearDisplay();
  pickDigit(1);
  pickNumber(n1, false);
  delay(dly);
  clearDisplay();
  pickDigit(2);
  pickNumber(n2, true);
  delay(dly);
  clearDisplay();
  pickDigit(3);
  pickNumber(n3, false);
  delay(dly);
  
}

void displayCal() {
  int dly = 3;
  clearDisplay();
  pickDigit(0);
  pickNumber(10, false);
  delay(dly);
  clearDisplay();
  pickDigit(1);
  pickNumber(11, false);
  delay(dly);
  clearDisplay();
  pickDigit(2);
  pickNumber(12, true);
  delay(dly);
  clearDisplay();
  pickDigit(3);
  pickNumber(99, false);
  delay(dly);
}

void displayWait(int i) {
  int dly = 3;
  clearDisplay();
  if( i<1 )
    return;
  pickDigit(0);
  pickNumber(99, true);
  delay(dly);
  clearDisplay();
  if( i<2 )
    return;
  pickDigit(1);
  pickNumber(99, true);
  delay(dly);
  clearDisplay();
  if( i<3 )
    return;
  pickDigit(2);
  pickNumber(99, true);
  delay(dly);
  clearDisplay();
  if( i<4 )
    return;
  pickDigit(3);
  pickNumber(99, true);
  delay(dly);
}

void clearDisplay() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(p, LOW);
}

void zero(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void one(boolean digits) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void two(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void three(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void four(boolean digits) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void five(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void six(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void seven(boolean digits) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void eight(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 


void nine(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 


void l_c(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 
void l_a(boolean digits) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 
void l_l(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 
void l_digits(boolean digits) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void pickDigit(int x) {
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  
  switch(x) {
    case 0:
    digitalWrite(d1, LOW);
    break;
    case 1:
    digitalWrite(d2, LOW);
    break;
    case 2:
    digitalWrite(d3, LOW);
    break;
    case 3:
    digitalWrite(d4, LOW);
    break;
  }
}

void pickNumber(int x, boolean digits) {
  switch(x) {
    case 0:
    zero(digits);
    break;
    case 1:
    one(digits);
    break;
    case 2:
    two(digits);
    break;
    case 3:
    three(digits);
    break;
    case 4:
    four(digits);
    break;
    case 5:
    five(digits);
    break;
    case 6:
    six(digits);
    break;
    case 7:
    seven(digits);
    break;
    case 8:
    eight(digits);
    break;
    case 9:
    nine(digits);
    break;
    case 10:
    l_c(digits);
    break;
    case 11:
    l_a(digits);
    break;
    case 12:
    l_l(digits);
    break;
    case 99:
    l_digits(digits);
    break;
    default:
    zero(digits);    
  }
}
