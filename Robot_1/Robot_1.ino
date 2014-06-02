#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// hex code assigned to each button
const long ch_minus_button = 0xFFA25D;
const long ch_button = 0xFF629D;
const long ch_plus_button = 0xFFE21D;
const long prev_button = 0xFF22DD; // turn left
const long next_button = 0xFF02FD; // move forward
const long play_button = 0xFFC23D; // turn right
const long minus_button = 0xFFE01F;
const long plus_button = 0xFFA857;   // move in reverse
const long EQ_button = 0xFF906F;
const long zero_button = 0xFF6897;
const long hund_plus_button = 0xFF9867;
const long twohund_plus_button = 0xFFB04F;
const long one_button = 0xFF30CF;  
const long two_button = 0xFF18E7; 
const long three_button = 0xFF78A85; 
const long four_button = 0xFF10EF; 
const long five_button = 0xFF38C7; 
const long six_button = 0xFF5AA5; 
const long seven_button = 0xFF42BD; 
const long eight_button = 0xFF4AB5; 
const long nine_button = 0xFF52AD;
const long repeat = 0xFFFFFFFF;


  
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
    if(results.value == prev_button)
      {
        Serial.println("in loop");
        // move motor forward
        digitalWrite(12, HIGH); // Establishes forward direction of Channel A
        digitalWrite(9, LOW);   // Disengage the Brake for Channel A
        analogWrite(3, 255);    // Spins the motor on Channel 
        delay(2000);
      }
    Serial.println(results.value, HEX);
    Serial.println(prev_button, HEX);
    irrecv.resume(); // Receive the next value
  }
}

/*************************************************************
Motor Shield 1-Channel DC Motor Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  
}

void loop(){
  
  //forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
  
  delay(3000);
  
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A

  delay(1000);
  
  //backward @ half speed
  digitalWrite(12, LOW); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);   //Spins the motor on Channel A at half speed
  
  delay(3000);
  
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  
  delay(1000);
  
}
*/
