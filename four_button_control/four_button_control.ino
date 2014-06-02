// adds second motor and 2 button control
#include <IRremote.h>

// variables for IR remote
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// hex code assigned to a button
const long forward_button = 0xFF629D;  // uses 'CH+' button 
const long stop_button = 0xFF02FD;     // uses 'Next' button
const long reverse_button = 0xFFA857;  // uses '+' button
const long left_button = 0xFF22DD;     // uses 'prev' button
const long right_button = 0xFFC23D;    // uses 'play' button

const long repeat = 0xFFFFFFFF;
long current_command = 0;
long previous_command = 0;

// speed is used globally for motion and steering
const int ASPEED = 255; // use speeds 60, 84, 108, 132,156,180, 304, 228, 255
const int BSPEED = 255;  
const int TURNSPEED = 5; // amount to adjust the speed when turning

// constant to indicate the forward direction for the motors
const int AFORWARD = HIGH;
const int BFORWARD = LOW;

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
     {
       current_command = previous_command;
     }
    else
     {
       current_command = results.value;
       previous_command = current_command;
     }
     
    // channel A is the left motor as viewed from a "driver" viewpoint"
    // channel B is the right motor as viewed from a "driver" viewpoint"  
    switch (current_command) 
      {
       //Serial.println("in switch");
       case forward_button:
            DriveForward();
            break;
       case stop_button: 
            Stop();
            break;
       case reverse_button:
            DriveBackward();
            break;
       case left_button:
            TurnLeft();
            break;
       case right_button:
            TurnRight(); 
            break;
      }   
     irrecv.resume(); // Receive the next value
  }
}

void DriveForward()
{
  Serial.println("Forward");
  digitalWrite(12, LOW); // Establishes forward direction of Channel A
  digitalWrite(9, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, ASPEED);    // Spins the motor on Channel A
  
  digitalWrite(13, HIGH); // Establishes forward direction of Channel B
  digitalWrite(8, LOW);   // Disengage the Brake for Channel B
  analogWrite(11, BSPEED);   // Spins the motor on Channel B at full speed 
}

void DriveBackward()
{
  Serial.println("Backwards");
  digitalWrite(12, HIGH); // Establishes forward direction of Channel A
  digitalWrite(9, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, ASPEED);    // Spins the motor on Channel A
  
  digitalWrite(13, LOW); // Establishes forward direction of Channel B
  digitalWrite(8, LOW);   // Disengage the Brake for Channel B
  analogWrite(11, BSPEED);   // Spins the motor on Channel B at full speed 
}

void Stop()
{
  Serial.println("Stop");
  digitalWrite(9, HIGH);   // engage the Brake for channel A
  digitalWrite(8, HIGH);   // engage the brake for channel B
}

void TurnLeft()
{
  Serial.println("Turn Left");
  digitalWrite(12, HIGH); // Establishes forward direction of Channel A
  digitalWrite(13, HIGH); // Establishes forward direction of Channel B
  delay(250);
  
  digitalWrite(12, LOW); // Establishes forward direction of Channel A
  digitalWrite(9, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, ASPEED);    // Spins the motor on Channel A
  
  digitalWrite(13, HIGH); // Establishes forward direction of Channel B
  digitalWrite(8, LOW);   // Disengage the Brake for Channel B
  analogWrite(11, BSPEED);   // Spins the motor on Channel B at full speed 
}

void TurnRight()
{
  Serial.println("Turn Right");
  digitalWrite(12, LOW); // Establishes forward direction of Channel A
  digitalWrite(13, LOW); // Establishes forward direction of Channel B
  delay(250);
  //DriveForward();
}

int BrakesEngaged()
{
  if( digitalRead(9) == HIGH && digitalRead(8) == HIGH)
    return 1;
  else 
    return 0;
}



