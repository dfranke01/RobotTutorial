/*************************************************************/

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  Serial.begin(115200); 
  
}

void loop(){
  for(int i=60; i < 150; i++)
    {
     //forward @ full speed
     digitalWrite(12, HIGH); //Establishes forward direction of Channel A
     digitalWrite(9, LOW);   //Disengage the Brake for Channel A
     analogWrite(3, i);   //Spins the motor on Channel A at full speed
     Serial.println(i);
     delay(2000);
    }
}

// hint, you cannot program the board if it has external power and is running a motor




