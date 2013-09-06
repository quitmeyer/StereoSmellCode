/*
  StereoSmelling Input Switch Fans
Switches Input fans based on breathing 
 This example code is in the public domain.
 */

//Serial Stuff
#include <SoftwareSerial.h>
// Definitions
#define rxPin 3
#define txPin 4
SoftwareSerial mySerial(rxPin, txPin);

// We use both outputs on the ATTINY to control the fans

int Fan = 1;
int Fan2 = 0;

//Use one input
int breathPin = 7; //ACTUALLY PIN LABELED AS "2" on the HLT tutorial

//Raw Value from the input
int breathVal = -1;

int threshold = 900;
const int num=6;
int senseVals[num]; //Stores the past [num] amount of microphone values

int senseAverage; //Processed values from the breath sensor
//Will be rounded cuz it's an int

//Toggle to decide which fan is currently going
boolean switchFans = 0;






// the setup routine runs once when you press reset:
void setup() {                
  pinMode(breathPin, INPUT);

  // initialize the digital pin as an output.

  pinMode(Fan, OUTPUT); 
  pinMode(Fan2, OUTPUT);   
  mySerial.begin(9600);


}

// the loop routine runs over and over abreathpingain forever:
void loop() {

  //Read in Input
  breathVal = analogRead(breathPin); 
  
  //Output values to serial (useful for debugging)
  mySerial.print("Mic Val: ");
  mySerial.print(breathVal);
  
  updateArray(); //Push the most recent value into the array
  
 senseAverage= getRecentAverage(); // Prevents a noisy spike from flipping the smell side switch

 mySerial.print("    Average: ");
  mySerial.print(senseAverage);
  mySerial.println();

  if(senseAverage>threshold){ //1023 is m680 is max at 3.3v ffor this electret microphone.   

switchFans=!switchFans;
//Reset the Array
 for(int i = num; i > -1; i--){
   senseVals[i] = 0;
 }
 delay(750);               // wait for a second
  }
  runFans();
}

void updateArray(){
 for(int i = num; i > 0; i--){
   senseVals[i] = senseVals[i-1];
 }
 senseVals[0] = breathVal;
}

int getRecentAverage(){
    int senseAv = 0;
 for(int i = 0; i < num; i++){
   senseAv = senseAv+ senseVals[i];
 }
 senseAv = senseAv/num;
 return senseAv;
}


void runFans(){
   if(switchFans){
    digitalWrite(Fan, HIGH);   // turn the Fan on (HIGH is the voltage level)
    digitalWrite(Fan2, LOW);   // turn the Fan on (HIGH is the voltage level)
  }
  else{
    digitalWrite(Fan, LOW);   // turn the Fan on (HIGH is the voltage level)
    digitalWrite(Fan2, HIGH); 
  } 
}
