/*
  Blink
  Turns on an Fan on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an Fan connected on most Arduino boards.
// give it a name:
int Fan = 0;
int Fan2 = 1;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(Fan, OUTPUT); 
  pinMode(Fan2, OUTPUT);     
  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(Fan, HIGH);   // turn the Fan on (HIGH is the voltage level)
    digitalWrite(Fan2, LOW);   // turn the Fan on (HIGH is the voltage level)

  delay(2000);               // wait for a second
  digitalWrite(Fan, LOW);    // turn the Fan off by making the voltage LOW
    digitalWrite(Fan2, HIGH);   // turn the Fan on (HIGH is the voltage level)

  delay(2000);               // wait for a second
}
