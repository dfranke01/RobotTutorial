#include <IRremote.h>

// variables for IR remote
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// hex code assigned to a button
const long prev_button = 0xFF22DD; 
  
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  //motor setup
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
}

void loop() {
  if (irrecv.decode(&results)) {   // results is an instance of a decode_results class, decode() returns an int
    //Serial.println(results.value, HEX);
    //Serial.println(prev_button, HEX);
    if(results.value == prev_button)
      {
        //Serial.println("in loop");
        // move motor forward
        digitalWrite(12, HIGH); // Establishes forward direction of Channel A
        digitalWrite(9, LOW);   // Disengage the Brake for Channel A
        analogWrite(3, 255);    // Spins the motor on Channel 
        delay(2000);
      }
    
    irrecv.resume(); // Receive the next value
  }
}

