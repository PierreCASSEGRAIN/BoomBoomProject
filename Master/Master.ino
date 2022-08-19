#include <SPI.h>              // include libraries
#include <LoRa.h>

const int csPin = 15;          // LoRa radio chip select
const int resetPin = 16;       // LoRa radio reset
const int irqPin = 2;         // change for your board; must be a hardware interrupt pin

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // adresse du maître
byte destination1 = 0x11;      // adresse cible 1
byte destination2 = 0x22;      // adresse cible 2
byte destination3 = 0x33;      // adresse cible 3
byte destination4 = 0x44;      // adresse cible 4
byte destination5 = 0x55;      // adresse cible 5
byte destination6 = 0x66;      // adresse cible 6
byte destination7 = 0x77;      // adresse cible 7
byte destination8 = 0x88;      // adresse cible 8
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

void setup() {
  Serial.begin(115200);                   // initialize serial
  while (!Serial);

  Serial.println("LoRa Duplex");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
  
  if (Mode==0) {
    selectionMode();
  }
  Serial.println(Mode);
  switch (Mode){
    case 1:
      PreparationModeDeJeu1();
      Jeu1();
  }

  Mode=0;
  
  if (millis() - lastSendTime > interval) {
    String message = "HeLoRa World!";   // send a message
    sendMessage(message,1);
    Serial.println("Sending " + message + " to cible 1");
    sendMessage(message,2);
    Serial.println("Sending " + message + " to cible 2");
    lastSendTime = millis();            // timestamp the message
    interval = 1000;    // 2-3 seconds
  }

  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendMessage(String message,int numCible) {

  switch (numCible){
    case 1:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination1);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 2:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination2);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 3:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination3);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 4:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination4);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 5:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination5);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 6:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination6);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 7:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination7);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    case 8:
      LoRa.beginPacket();                   // start packet
      LoRa.write(destination8);             // add destination address
      LoRa.write(localAddress);             // add sender address
      LoRa.write(msgCount);                 // add message ID
      LoRa.write(outgoing.length());        // add payload length
      LoRa.print(outgoing);                 // add payload
      LoRa.endPacket();                     // finish packet and send it
      msgCount++;                           // increment message ID
      break;
    default:
      break;      
  }
  
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}

void PreparationModeDeJeu1(){
  RefreshSeed();
  for (int i = 0; i < nbDeRound; i++){
    TableauCibleJeu1[i]=random(1,pow(2,nbDeCapteurs));
    Serial.print("TableauCibleJeu = ");
    Serial.println(TableauCibleJeu1[i]);
  }
}

int Jeu1(){
  Serial.println("Le jeu va commencer dans...");
  delay(1000);
  Serial.println("5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("C'est parti !");
  TimerTotalJeu1=millis();
  Points=0;
  while (millis()<=TimerTotalJeu1+TempsMancheModeDeJeu1){
    TimerRoundJeu1=millis();
    EtatCibles = TableauCibleJeu1[NumRound];
    NumRound++;
    Serial.print("Round n°");
    Serial.println(NumRound);
    Serial.println(EtatCibles);
    RoundFini=false;
  }
  Serial.println("Terminé !");
  Serial.print("Vous avez eu ");
  Serial.print(Points);
  Serial.println(" points");
}
