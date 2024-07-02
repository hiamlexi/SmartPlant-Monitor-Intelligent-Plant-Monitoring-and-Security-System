#ifndef RFID_H
#define RFID_H

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setupRFID() {
  pinMode(16, OUTPUT); // Red LED
  pinMode(15, OUTPUT); // Green LED
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 // Serial.println("Approximate your card to the reader...");
  //Serial.println();
}

bool checkRFID() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
 //Uncommented this line for debugging purpose if you need to
  //Show UID on serial monitor
  //Serial.print("UID tag: ");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  
  //Serial.print("Message: ");
  content.toUpperCase();
  
  // Change here the UID of the card/cards that you want to give access
  if (content.substring(1) == "53 8A 97 16") {
    //Uncommented this line for debugging purpose if you need to
    //Serial.println("Authorized access");
    //Serial.println();
    digitalWrite(15, HIGH);
    delay(200);
    digitalWrite(15, LOW);
    delay(200);
    digitalWrite(15, HIGH);
    delay(200);
    digitalWrite(15, LOW);
    return true;
  } else {
   //Uncommented this line for debugging purpose if you need to
    //Serial.println("Access denied");
    //Serial.println();
    digitalWrite(16, HIGH);
    delay(200);
    digitalWrite(16, LOW);
    delay(200);
    digitalWrite(16, HIGH);
    delay(200);
    digitalWrite(16, LOW);
    return false;
  }
}

#endif
