/*
This code will detect RFID and trigger nodejs server accordingly. Read comments to understand what to change.
  */

#include <Wire.h>
#include "MFRC522_I2C.h" //rfid library
#include <M5CoreS3.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define RST_PIN 0

MFRC522_I2C mfrc522(0x28,RST_PIN); 

WiFiMulti wifiMulti;
//HTTPClient http;

const char* ssid     = "TheB3st$$1"; // Change this according wifi SSID
const char* password = "l0ck0N3$$1"; // Change this according to wifi PW

const char *server = "192.168.1.169";
const int port = 9000;

void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3.  
    Serial.begin(115200); 
    M5.Lcd.setTextSize(2);        // Set text size. 
      wifiMulti.addAP(ssid, password);
      M5.Lcd.print("\nConnecting Wifi...\n"); 

      if ((wifiMulti.run() ==
         WL_CONNECTED)) {  // wait for WiFi connection.  

          M5.Lcd.print("");
    M5.Lcd.print("\nWiFi connected.\n");
    M5.Lcd.print("\nIP address:\n ");
    M5.Lcd.print( WiFi.localIP());
    M5.Lcd.print("\nCode written by: \nthesupersystem\n");
     
      M5.Lcd.print("\n\Tap card ");
   } else {
        //http.end();
        M5.Lcd.print("connect failed");
    }
     Wire.begin(2,1);  // Wire init, adding the I2C bus.  
mfrc522.PCD_Init();  // Init MFRC522. 
}

void loop() {
M5.Lcd.setCursor(40, 47);
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {  
        delay(1000);
        return;
    }
     M5.Lcd.fillRect(0, 0, 320, 240, BLACK);
     M5.Lcd.print("\nIP address:");
     M5.Lcd.print("\n\ ");
     M5.Lcd.print( WiFi.localIP());
     
    
    String cardUID = "";
   
    for (byte i = 0; i < mfrc522.uid.size;
         i++) {  // Output the stored UID data.
        //cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        cardUID += String(mfrc522.uid.uidByte[i], HEX);
          
          M5.Lcd.fillRect(0, 0, 320, 240, BLACK);
          M5.Lcd.println("Card UID: " + cardUID);
           Serial.println(cardUID);
          
          delay(200);
    
    }
  sendHttpRequest(cardUID);
}


void sendHttpRequest(String cardUID){

WiFiClient client;

 if (cardUID == "b0b240a7") { // Change this according to RFID UID of product

  HTTPClient http;

  String url = "http://192.168.1.41:9000/test1"; // Change this according to NODEJS server

  http.begin(url);  //Specify the URL
  int httpCode = http.GET(); //Make the request
      
      M5.Lcd.println("Trigger Video1");
http.end(); //Close connection
    } if (cardUID == "1d5524b") { // Change this according to RFID UID of product

      HTTPClient http;

  String url = "http://192.168.1.169:9000/test2"; // Change this according to NODEJS server

  http.begin(url);  //Specify the URL
  int httpCode = http.GET(); //Make the request
      
      Serial.println("Trigger Video2");
      http.end(); //Close connection

    } else {

      Serial.println("Unknown card UID, no action taken.");

    }


}


