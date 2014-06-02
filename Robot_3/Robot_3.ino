// adds second motor and 2 button control
#include <IRremote.h>

// variables for IR remote
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// hex code assigned to a button
const long prev_button = 0xFF22DD; 
const long play_button = 0xFF22DD;
const long repeat = FFFFFFFF;
int current_command = 0;
int previous_command = 0;

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
}

void loop() {
  if (irrecv.decode(&results)) {   // results is an instance of a decode_results class, decode() returns an int
    //Serial.println(results.value, HEX);
    
    current_command = results.value;
    switch (current_command) 
      {
       //Serial.println("in switch");
       // channel A is the left motor as viewed from a "driver" viewpoint"
       case prev_button: 
            previous_command = results.value;
            // drive left motor
            digitalWrite(12, HIGH); // Establishes forward direction of Channel A
            digitalWrite(9, LOW);   // Disengage the Brake for Channel A
            analogWrite(3, 255);    // Spins the motor on Channel 
            delay(250);
            break;
       // channel B is the right motor as viewed from a "driver" viewpoint"     
       case play_button:
            previous_command = results.value;
            // drive right motor
            digitalWrite(13, HIGH); //Establishes forward direction of Channel B
            digitalWrite(8, LOW);   //Disengage the Brake for Channel B
            analogWrite(11, 255);   //Spins the motor on Channel B at full speed
            delay(250);
            break;
            
       case repeat:
            if( previous_command == prev_button )
              {
                // drive left motor
                digitalWrite(12, HIGH); // Establishes forward direction of Channel A
                digitalWrite(9, LOW);   // Disengage the Brake for Channel A
                analogWrite(3, 255);    // Spins the motor on Channel 
                delay(250);
                break;
              }
             else if( previous_command == play_button )
              {
                // drive right motor
                digitalWrite(13, HIGH); //Establishes forward direction of Channel B
                digitalWrite(8, LOW);   //Disengage the Brake for Channel B
                analogWrite(11, 255);   //Spins the motor on Channel B at full speed
                delay(250);
                break;
              } 
            
       default: 
      }   
    irrecv.resume(); // Receive the next value
  }
}

/*************************************************************
Motor Shield 2-Channel DC Motor Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
}

void loop(){

  
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B backward @ half speed
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 123);    //Spins the motor on Channel B at half speed

  
  delay(3000);

  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(9, HIGH);  //Engage the Brake for Channel B


  delay(1000);
  
  
  //Motor A forward @ full speed
  digitalWrite(12, LOW);  //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);    //Spins the motor on Channel A at half speed
  
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
  
  delay(3000);
  
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(9, HIGH);  //Engage the Brake for Channel B
  
  
  delay(1000);
  
}
*/
