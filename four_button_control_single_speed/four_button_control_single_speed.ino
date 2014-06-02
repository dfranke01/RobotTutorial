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
const int SPEED = 255; // use speeds 60, 84, 108, 132,156,180, 304, 228, 255  

// constant to indicate the forward direction of the motors
const int AFORWARD = HIGH; // forward
const int BFORWARD = LOW;  // forward

// constant to indicate the current direction of the motors
int ADIRECTION = HIGH; // forward
int BDIRECTION = LOW;  // forward



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
  ADIRECTION = AFORWARD;
  BDIRECTION = BFORWARD;
  digitalWrite(12, ADIRECTION); // Establishes direction of Channel A
  digitalWrite(9, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, SPEED);    // Spins the motor on Channel A
  
  digitalWrite(13, BDIRECTION); // Establishes direction of Channel B
  digitalWrite(8, LOW);   // Disengage the Brake for Channel B
  analogWrite(11, SPEED);   // Spins the motor on Channel B at full speed 
}

void DriveBackward()
{
  Serial.println("Backwards");
  ADIRECTION = (! AFORWARD);
  BDIRECTION = (! BFORWARD);
  digitalWrite(12, ADIRECTION); // Establishes forward direction of Channel A
  digitalWrite(9, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, SPEED);    // Spins the motor on Channel A
  
  digitalWrite(13, BDIRECTION); // Establishes forward direction of Channel B
  digitalWrite(8, LOW);   // Disengage the Brake for Channel B
  analogWrite(11, SPEED);   // Spins the motor on Channel B at full speed 
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
  digitalWrite(12, (! ADIRECTION)); // drive channel A in the opposite direction
  delay(250);
  digitalWrite(12, ADIRECTION); // restore channel A to the direction we started with
}

void TurnRight()
{
  Serial.println("Turn Right");
  int notMoving = 0;
  if( BrakesEngaged())
    {
     DriveForward();
     notMoving = 1;
    }
     
  digitalWrite(12, (! BDIRECTION)); // drive channel A in the opposite direction
  delay(250);
  digitalWrite(12, BDIRECTION); // restore channel A to the direction we started with
  
  if( notMoving )
    Stop();
    
}

int BrakesEngaged()
{
  if( digitalRead(9) == HIGH && digitalRead(8) == HIGH)
    return 1;
  else 
    return 0;
}



