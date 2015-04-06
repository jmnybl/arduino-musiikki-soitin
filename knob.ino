

#define A 32
#define B 33

int count = 0;

// Interrupt Service Routine
void isr() {
  
  int pinA = digitalRead(A);
  int pinB = digitalRead(B);
  
  // HH or LL --> clockwise
  // HL or LH --> counter clockwise
  
  if (pinA == pinB) {
    count++;
  }
  else {
    count--;
  }
  
}


void setup () {
  
  digitalWrite(A, HIGH);   // pull-up resistors
  digitalWrite(B, HIGH); 
  
  attachInterrupt(A, isr, CHANGE);

  Serial.begin (9600);
}

void loop () {
  Serial.println(count);
}
