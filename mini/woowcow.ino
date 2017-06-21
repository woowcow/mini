/*
 
  VCC接5V,GND接地,SDA接A4,SCL接A5
  喇叭+ PIN8，喇叭- GND

  --- GY-30 ---
  GY-30 -> Arduino
  VCC -> 5V
  GND -> GND
  SDA -> A4
  SCL -> A5

  --- buzzer ---
  buzzer+ -> D8
  buzzer- -> GND
  
*/

#include <Wire.h>
#include "pitches.h"
#include "wdt.h"  //Watchdog

int BH1750_address = 0x23; // i2c Addresse
byte buff[2];
int maxvalue = 0;
int temp = 0;
int ledPin = 13;
//-----------聲音
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};
int duration = 500;  // 500 miliseconds

int count0, count1, count2, count3, count4;
//----------------

void setup() {
  wdt_enable (WDTO_8S);   //Watchdog 8S

  pinMode(ledPin, OUTPUT);

  Wire.begin();
  BH1750_Init(BH1750_address);

  delay(200);
  Serial.begin(9600);
  Serial.println("Earthquake program - Fluorescent lamp");
}

void loop() {
  wdt_reset ();   //Watchdog

  float valf = 0;

  if (BH1750_Read(BH1750_address) == 2) {

    valf = ((buff[0] << 8) | buff[1]) / 1.2;

    if (valf < 0)Serial.print("> 65535");
    else Serial.print((int)valf, DEC);

    Serial.println(" lx");


  }
  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);

  temp = valf;
  if (temp > maxvalue)
  {
    maxvalue = temp;
  }
  if (maxvalue != 0) {
    Serial.println("Warning MAX:");
    Serial.println(maxvalue);


    for (int thisNote = 0; thisNote < 8; thisNote++) {  //喇叭輸出
      tone(8, melody[thisNote], duration);
      delay(100);
    }
    tone(8, melody[10000], duration);
    delay(100);


    count1 = maxvalue % 10;
    count2 = maxvalue % 100 / 10;
    count3 = maxvalue % 1000 / 100;
    count4 = maxvalue % 10000 / 1000;
    //    Serial.println(count4);
    //    Serial.println(count3);
    //    Serial.println(count2);
    //    Serial.println(count1);
    if (maxvalue > 0) {
      if (count4 > 0) {
        for (int count = 0; count < count4; count++)    //喇叭輸出千位數
        {
          sound();
        }
        delay(300);
      }

      if (count3 > 0 || count4 > 0)   //喇叭輸出百位數
      {
        for (int count = 0; count < count3; count++)
        {
          sound();
        }
        if (count3 == 0 && (count4 > 0))    //如果千位數以上有數值百位數為0響10次
        {
          zero();
        }
        delay(300);
      }

      if (count2 > 0 || count3 > 0 || count4 > 0)   //喇叭輸出十位數
      {
        for (int count = 0; count < count2; count++)
        {
          sound();
        }
        if (count2 == 0 && ( count3 > 0 || count4 > 0))   //如果百位數以上有數值十位數為0響10次
        {
          zero();
        }
        delay(300);
      }

      for (int count = 0; count < count1; count++)    //喇叭輸出個位數
      {
        sound();
      }
      if (count1 == 0 && (count2 > 0 || count3 > 0 || count4 > 0)) {    //如果十位數以上有數值十位數為0響10次
        zero();
      }
    }

  }

  if (maxvalue != 0) {
    delay(0);
  } else {
    delay(500);
  }
}

void BH1750_Init(int address) {

  Wire.beginTransmission(address);
  Wire.write(0x10); // 1 [lux] aufloesung
  Wire.endTransmission();
}

byte BH1750_Read(int address) {

  byte i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  return i;
}

void sound(void)
{
  tone(8, melody[0], duration);
  delay(100);
  tone(8, melody[10000], duration);
  delay(100);
  wdt_reset ();   //Watchdog
}

void zero(void)
{
  for (int count = 0; count < 10; count++)
  {
    tone(8, melody[0], duration);
    delay(100);
    tone(8, melody[10000], duration);
    delay(100);
  }
}
