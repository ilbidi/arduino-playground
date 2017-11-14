/**
* The program shows the seconds passed from startup
*/

// Pin used managed as the part of the led numbers( a,b, ..)
int a = 7;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 2;
int g = 8;
int p = A2;
int d4 = A3;
int d3 = A4;
int d2 = A5;
int d1 = A6;

// Delay of loop in milliseconds
int loopDelay = 5;

// Startup milliseconds
long startupTime=0;

void setup() {
  
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

  startupTime=millis();
}

void loop() {
  delay(loopDelay);
  long currentTime = millis();
  if(currentTime-startupTime>10000)
    startupTime=currentTime;
    
  // Display passed milliseconds as cents of seconds with 2 digits
  displayTime((long)(currentTime-startupTime));
  
}

void displayTime(long passedTime) {
  int n1 = (passedTime%10000)/1000;
  int n2 = (passedTime%1000)/100;
  int n3 = (passedTime%100)/10;
  int n4 = passedTime%10;
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
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  if( digits )
    digitalWrite(p, HIGH);
  else
    digitalWrite(p, LOW);
} 

void five(boolean digits) {
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

void six(boolean digits) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
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

void seven(boolean digits) {
  digitalWrite(a, HIGH);
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
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
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
    default:
    zero(digits);    
  }
}
