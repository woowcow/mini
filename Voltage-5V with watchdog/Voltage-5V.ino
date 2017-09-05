/*

  Voltage 5V

  --- Voltage ---
  A0 -> Fluorescent lamp
  GND -> Fluorescent lamp


  --- buzzer ---
  buzzer+ -> D8
  buzzer- -> GND

  Design by 牛圈
  http://www.woowcow.com

*/

#include <Wire.h>
#include "pitches.h"
#include "wdt.h"  //Watchdog


int maxvalue = 0;
int temp = 0;
int ledPin = 13;

float temp_voltage;
int voltage;
float rectifier_voltage = 1; //整流器壓降(V)


//-----------Buzzer sound
int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds
int count0, count1, count2, count3, count4;
//-----------Buzzer sound END

void setup() {
  wdt_enable (WDTO_8S);   //Watchdog set 8 second

  pinMode(ledPin, OUTPUT);

  delay(200);
  Serial.begin(9600);
  Serial.println("Earthquake program - http://www.woowcow.com");
}

void loop() {
  wdt_reset ();   //Watchdog

  float valf = 0;

  int V1 = analogRead(A0);          //讀取A0範圍0～5v 值0-1024
  float vol = V1 * (5.0 / 1023.0);  //轉換成電壓
  int voltage = vol * 100 * rectifier_voltage;        //*100倍加上整流器壓降
  if (vol == temp_voltage)          //不同上次值才輸出
  {
    temp_voltage = vol;
  }
  else
  {
    Serial.println("Voltage:");
    Serial.print(vol * rectifier_voltage);        //輸出電壓值加上整流器壓降
    Serial.println("\tV");


    Serial.println("Source:");
    Serial.print(voltage);      //輸出電壓*100倍值
    Serial.println("\n");

    temp_voltage = vol;
    valf = voltage;
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
