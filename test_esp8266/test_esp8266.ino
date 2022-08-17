/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot
int seuilCapteur = 100;
unsigned long TimerAntiReentrant;
unsigned long ValeurAntiReentrant = 1000;

void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
 if ((sensorValue>=seuilCapteur)&&(TimerAntiReentrant+ValeurAntiReentrant<=millis())){

  TimerAntiReentrant=millis();
  // print the readings in the Serial Monitor
  Serial.println("TOUCHÉ");
 }
  delay(2);
}
