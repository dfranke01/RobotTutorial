// flashes a LED in a 3dots-3dashes-3dots oattern
const int led_pin = 13;

void setup() {
  // set the digital pin as output:
  pinMode(led_pin, OUTPUT);  
  Serial.begin(9600);  
}

void loop()
{
  // write the 'S'.
  digitalWrite(led_pin, LOW);
  delay(250);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(250);
  Serial.println("writing high");
  digitalWrite(led_pin, LOW);
  delay(250);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(250);
  Serial.println("writing high");
  digitalWrite(led_pin, LOW);
  delay(250);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(250);
  Serial.println("writing high");
  // wite the 'O'
  digitalWrite(led_pin, LOW);
  delay(1000);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(1000);
  Serial.println("writing high");
  digitalWrite(led_pin, LOW);
  delay(1000);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(1000);
  Serial.println("writing high");
  digitalWrite(led_pin, LOW);
  delay(1000);
  Serial.println("writing low");
  digitalWrite(led_pin, HIGH);
  delay(1000);
  Serial.println("writing high");
}
