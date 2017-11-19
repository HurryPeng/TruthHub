/*
  TruthHub
  2017.11.18-19
  The 1st place winning project in the 1st Shenzhen Middle School Students' Maker Marathon. 
  Shenzhen Experimental School
  Version: Beta1.0
*/

#include <Arduino.h>
#include "HurryPeng.h"
#include <SPI.h>
#include "MFRC522.h"
#include <SoftwareSerial.h>

const pin_t RfidRst = 9, RfidSda = 10, RfidMosi = 11, RfidMiso = 12, RfidSck = 13;
SoftwareSerial BlueTooth(3, 2);
MFRC522 RfidReader(RfidSda, RfidRst);
MFRC522::MIFARE_Key Key;

void setup()
{
	BlueTooth.begin(9600);
	BlueTooth.listen();
	SPI.begin();
	RfidReader.PCD_Init();
	for (uint8_t i = 0; i < 6; i++) Key.keyByte[i] = 0xff;
}

//int j = 0;

void loop()
{
	if (!RfidReader.PICC_IsNewCardPresent()) return;
	if (!RfidReader.PICC_ReadCardSerial()) return;
	uint32_t uid = *((uint32_t *)RfidReader.uid.uidByte);
	Serial.println(uid, HEX);
	int id = 0;
	switch (uid)
	{
		case 0x1bf39fd0: id = 1; break;
		case 0x0d8efc42: id = 2; break;
		case 0xdbc299dc: id = 3; break;
		case 0x80582d50: id = 4; break;
	}
	BlueTooth.write(id);
	//Serial.println(id);
	//Serial.println(j++);
	BlueTooth.flush();
}
