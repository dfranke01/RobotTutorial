// adds second motor and 2 button control
#include <IRremote.h>

// variables for IR remote
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// hex code assigned to a button
const long prev_button = 0xFF22DD; 
const long play_button = 0xFFC23D;
const long next_button = 0xFF02FD;
const long repeat = 0xFFFFFFFF;
long current_command = 0;
long previous_command = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  //motor setup
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  
  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin
  
  digitalWrite(9, HIGH);   // engage the Brake for channel A
  digitalWrite(8, HIGH);   // engage the brake for channel B
}

void loop() 
{
  if (irrecv.decode(&results)) {   // results is an instance of a decode_results class, decode() returns an int
    Serial.println(results.value, HEX);
    
    if( results.value == repeat )
       current_command = previous_command;
    else
       current_command = results.value;
       
    switch (current_command) 
      {
       Serial.println("in switch");
             
       // run both motors at the same time
       case next_button:
            previous_command = next_button;
            // drive left motor
            digitalWrite(12, LOW);   // Establishes forward direction of Channel A
            digitalWrite(13, HIGH);  // Establishes forward direction of Channel B
            digitalWrite(9, LOW);    // Disengage the Brake for Channel A
            digitalWrite(8, LOW);    // Disengage the Brake for Channel B
            analogWrite(3, 255);     // Spins the motor on Channel A
            analogWrite(11, 255);   // Spins the motor on Channel B at full speed
            delay(250);
            digitalWrite(9, HIGH);   // engage the Brake for Channel A
            digitalWrite(8, HIGH);   // engage the Brake for Channel B           
            break;
       
       // channel A is the left motor as viewed from a "driver" viewpoint"
       case prev_button: 
            previous_command = prev_button;
            // drive left motor
            digitalWrite(12, LOW); // Establishes forward direction of Channel A
            digitalWrite(9, LOW);   // Disengage the Brake for Channel A
            analogWrite(3, 255);    // Spins the motor on Channel A
            delay(250);
            digitalWrite(9, HIGH);   // engage the Brake for Channel A
            break;
            
       // channel B is the right motor as viewed from a "driver" viewpoint"
       case play_button:
            previous_command = play_button;
            // drive right motor
            digitalWrite(13, HIGH); // Establishes forward direction of Channel B
            digitalWrite(8, LOW);   // Disengage the Brake for Channel B
            analogWrite(11, 255);   // Spins the motor on Channel B at full speed
            delay(250);
            digitalWrite(8, HIGH);   // engage the Brake for Channel B
            break;
      
   
      } 
     irrecv.resume(); // Receive the next value
  }
}


//digitalWrite(9, HIGH);  //Engage the Brake for Channel A
//digitalWrite(9, HIGH);  //Engage the Brake for Channel B
