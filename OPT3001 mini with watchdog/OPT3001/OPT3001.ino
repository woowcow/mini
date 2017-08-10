/*
  OPT3001_Demo Example
  VCC接3.3V,GND接地,SDA接A4,SCL接A5
  喇叭+ PIN8，喇叭- GND

  --- OPT3001 ---
  GY-30 -> Arduino
  VCC -> 3.3V
  GND -> GND
  SDA -> A4
  SCL -> A5

  --- buzzer ---
  buzzer+ -> D8
  buzzer- -> GND

  Design by 牛圈
  http://www.woowcow.com

*/

#include <Wire.h>      // Needed by Energia for Tiva C LaunchPad 
#include "Opt3001.h"
#include "pitches.h"
#define USE_USCI_B1
#include "wdt.h"  //Watchdog

#define SCL_PIN      5
#define SDA_PIN      4

Opt3001 opt3001;
int maxvalue = 0;
int temp = 0;
int ledPin = 13;

//-----------Buzzer sound
int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds
int count0, count1, count2, count3, count4;
//-----------Buzzer sound END

void setup()
{
  wdt_enable (WDTO_8S);   //Watchdog set 8 second


  pinMode(ledPin, OUTPUT);

  unsigned int readings = 0;

  Serial.begin(9600);

  opt3001.begin();

  Serial.println("Earthquake program - http://www.woowcow.com");


  int opt300read = 0;
  double opt300rawread = 0;
}

void loop()
{
  wdt_reset ();   //Watchdog
  // Variables
  uint32_t readings;

  // Read OPT3001
  readings = opt3001.readResult() * 100;       //*100 取得最低0.01 LUX

  Serial.print("OPT3001 LUX Readings = ");
  Serial.println((double)readings / 100, 2);  //輸出LUX值

  Serial.print("OPT3001 Readings = ");
  Serial.println(readings, DEC);              //輸出原始資料

  //  delay(200);

  digitalWrite(ledPin, HIGH);
  delay(1);
  digitalWrite(ledPin, LOW);

  temp = readings;
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

    if (maxvalue > 0) {
      if (count4 > 0) {
        for (int count = 0; count < count4; count++)    //喇叭輸出千位數 Output Thousands number
        {
          sound();
        }
        delay(300);
      }

      if (count3 > 0 || count4 > 0)   //喇叭輸出百位數 Output Hundred number
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

      if (count2 > 0 || count3 > 0 || count4 > 0)   //喇叭輸出十位數 Output Ten number
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

      for (int count = 0; count < count1; count++)    //喇叭輸出個位數 Output number
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
