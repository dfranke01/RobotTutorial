// adds second motor and 2 button control
#include <IRremote.h>

// pin assignments
const int pingPin = 6; // need to set these
const int RECV_PIN = 4;
const int directionPinA = 12;
const int directionPinB = 13;
const int motorPinA = 3;
const int motorPinB = 11;
const int brakePinA = 9;
const int brakePinB = 8;

// hex code assigned to a button press
const long forward_button = 0xFD807F;  // uses 'VOL+' button 
const long stop_button = 0xFDA05F;     // uses 'Play' button
const long reverse_button = 0xFD906F;  // uses 'VOL-' button
const long left_button = 0xFD20DF;     // uses 'prev' button
const long right_button = 0xFD609F;    // uses 'next' button
const long repeat = 0xFFFFFFFF;

// global vars
const int AFORWARD = LOW;
const int BFORWARD = HIGH;
IRrecv irrecv(RECV_PIN);
decode_results results;
long current_command = 0;
long previous_command = 0;

// speed is used globally for motion and steering
const int MAX_SPEED = 255; // use speed 255  

// main class to represent our robot
class Robot
{
  private:
    int _lts; // left track speed
    int _rts; // right track speed 
    int _ltd; // left track direction
    int _rtd; // right track direction
    void drive(int lts, int rts, int ltd, int rtd);
    
  public:
    Robot(int lts, int rts, int ltd, int rtd);
    void Stop(); // engage both brakes    
    void DriveForward(); // both forward 
    void DriveBackward(); // both backward 
    void TurnLeft(); // opposite directions 
    void TurnRight(); // opposite directions
};
 
// create a new robot
Robot tracky(0, 0, AFORWARD, BFORWARD); // our robot is named tracky
   
void setup()
{
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  // setup channels A
  pinMode(motorPinA, OUTPUT); //Initiates Motor Channel A pin
  pinMode(brakePinA, OUTPUT); //Initiates Brake Channel A pin
  
  // setup Channel B
  pinMode(motorPinB, OUTPUT); //Initiates Motor Channel B pin
  pinMode(brakePinB, OUTPUT);  //Initiates Brake Channel B pin
  
  digitalWrite(brakePinA, LOW);   // disengage the Brake for channel A
  digitalWrite(brakePinB, LOW);   // disengage the brake for channel B
  
  // setup ports for ultrasonic sensor
  pinMode(pingPin, OUTPUT);
}

void loop() 
{
   // test for obstacle
   int duration, inches=3;
   pinMode(pingPin, OUTPUT);          // Set pin to OUTPUT
   digitalWrite(pingPin, LOW);        // Ensure pin is low
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);       // Start ranging
   delayMicroseconds(5);              //   with 5 microsecond burst
   digitalWrite(pingPin, LOW);        // End ranging
   pinMode(pingPin, INPUT);           // Set pin to INPUT
   duration = pulseIn(pingPin, HIGH); // Read echo pulse
   inches = duration / 74 / 2;        // Convert to inches
   Serial.println(inches);            // Display result
   delay(200);		             // Short delay
  
   if( inches < 3 && inches > 0)
     {
       Serial.println("obstacle detected");
       tracky.Stop();
       tracky.DriveBackward();
       delay(1000); // go backwards briefly
       tracky.TurnLeft();
       tracky.Stop();
       tracky.DriveForward();
     } 
    delay(200);
 
 
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
       //Serial.println("in switch statement");
       case forward_button:
            tracky.DriveForward();
            break;
       case stop_button: 
            tracky.Stop();
            break;
       case reverse_button:
            tracky.DriveBackward();
            break;
       case left_button:
            tracky.TurnLeft();
            break;
       case right_button:
            tracky.TurnRight(); 
            break;
      }   
     irrecv.resume(); // Receive the next value
  }
}

Robot::Robot(int lts, int rts, int ltd, int rtd)
{
  _lts = lts;
  _rts = rts;
  _ltd = ltd;
  _rtd = rtd;
}

void Robot::drive(int lts, int rts, int ltd, int rtd)
{
  //Serial.println(lts);
  digitalWrite(directionPinA, ltd); // Establishes direction of Channel A
  //digitalWrite(brakePinA, LOW);   // Disengage the Brake for Channel A
  analogWrite(motorPinA, lts);    // Spins the motor on Channel A
  
  //Serial.println(rts);
  digitalWrite(directionPinB, rtd); // Establishes direction of Channel B
  //digitalWrite(brakePinB, LOW);   // Disengage the Brake for Channel B
  analogWrite(motorPinB, rts);   // Spins the motor on Channel B at full speed 
}

void Robot::Stop()
{
  //Serial.println("Stop");
  //digitalWrite(brakePinA, HIGH);   // engage the Brake for channel A
  //digitalWrite(brakePinB, HIGH);   // engage the brake for channel B
  _lts = 0;
  _rts = 0;
  drive(_lts, _rts, _ltd, _rtd);

}    
       
void Robot::DriveForward()
{
  //Serial.println("Forward");
  _lts = MAX_SPEED;
  _rts = MAX_SPEED;
  _ltd = AFORWARD;
  _rtd = BFORWARD;
  drive(_lts, _rts, _ltd, _rtd);
}
  
void Robot::DriveBackward()
{
  //Serial.println("Backwards");
  _lts = MAX_SPEED;
  _rts = MAX_SPEED;
  _ltd = !AFORWARD;
  _rtd = !BFORWARD;
  drive(_lts, _rts, _ltd, _rtd);
}

void Robot::TurnLeft()
{
  //Serial.println("Turn Left");
  Serial.println(_lts);
  Serial.println(_rts);
  // the robot does not have to be moving to turn, we will spin in place
  drive(MAX_SPEED, MAX_SPEED, !AFORWARD, BFORWARD); // drive the left track in the opposite direction  
  delay(750);
  drive(_lts, _rts, _ltd, _rtd); // resume whatever we were doing when this function was called
 }

void Robot::TurnRight()
{
  //Serial.println("Turn Right");
  // the robot does not have to be moving to turn, we will spin in place
  drive(MAX_SPEED, MAX_SPEED, AFORWARD, !BFORWARD); // drive the left track in the opposite direction  
  delay(500);
  drive(_lts, _rts, _ltd, _rtd); // resume whatever we were doing when this function was called
}


