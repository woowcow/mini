/*
  TSL2561 Example
  VCC接3.3V,GND接地,SDA接A4,SCL接A5
  喇叭+ PIN8，喇叭- GND

  --- TSL2561 ---
  GY-2561 -> Arduino
  VCC -> 3.3V
  GND -> GND
  SDA -> A4
  SCL -> A5

  library
  https://learn.sparkfun.com/tutorials/tsl2561-luminosity-sensor-hookup-guide/all
  https://github.com/adafruit/TSL2561-Arduino-Library

  --- buzzer ---
  buzzer+ -> D8
  buzzer- -> GND

  Design by 牛圈
  http://www.woowcow.com

*/

#include <SparkFunTSL2561.h>
#include <Wire.h>
#include "pitches.h"
#include "wdt.h"  //Watchdog

int maxvalue = 0;
int temp = 0;
int ledPin = 13;
//-----------Buzzer sound
int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds
int count0, count1, count2, count3, count4;
//-----------Buzzer sound END


// Create an SFE_TSL2561 object, here called "light":

SFE_TSL2561 light;

// Global variables:

boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

void setup()
{
  // Initialize the Serial port:

  Serial.begin(9600);
  Serial.println("TSL2561 example sketch");

  light.begin();

  unsigned char ID;

  if (light.getID(ID))
  {
    Serial.print("Got factory ID: 0X");
    Serial.print(ID, HEX);
    Serial.println(", should be 0X5X");
  }

  else
  {
    byte error = light.getError();
    printError(error);
  }

  // If gain = false (0), device is set to low gain (1X)
  // If gain = high (1), device is set to high gain (16X)

  gain = 1;

  // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  // If time = 3, use manual start / stop to perform your own integration

  unsigned char time = 2;

  // setTiming() will set the third parameter (ms) to the
  // requested integration time in ms (this will be useful later):

  Serial.println("Set timing...");
  light.setTiming(gain, time, ms);

  // To start taking measurements, power up the sensor:

  Serial.println("Powerup...");
  light.setPowerUp();

  // The sensor will now gather light during the integration time.
  // After the specified time, you can retrieve the result from the sensor.
  // Once a measurement occurs, another integration period will start.
}

void loop()
{

  ms = 1000;
  light.manualStart();
  delay(ms);
  light.manualStop();

  unsigned int data0, data1;
  int readings;

  if (light.getData(data0, data1))
  {
    // getData() returned true, communication was successful

    Serial.print("data0: ");
    Serial.print(data0);
    Serial.print(" data1: ");
    Serial.print(data1);

    double lux;    // Resulting lux value
    boolean good;  // True if neither sensor is saturated

    // Perform lux calculation:

    good = light.getLux(gain, ms, data0, data1, lux);

    // Print out the results:

    readings = (lux * 100); // X100倍輸出資料
    Serial.print(" lux: ");
    Serial.print(lux);
    Serial.print(" Readings: ");
    Serial.print(readings);

    if (good) Serial.println(" (good)\t"); else Serial.println(" (BAD)\t");


  }
  else
  {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    printError(error);
  }

  //---------- sound
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

void printError(byte error)
// If there's an I2C error, this function will
// print out an explanation.
{
  Serial.print("I2C error: ");
  Serial.print(error, DEC);
  Serial.print(", ");

  switch (error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}

void sound(void)
{
  
  digitalWrite(ledPin, LOW);
  tone(8, melody[0], duration);
  delay(100);
  digitalWrite(ledPin, HIGH);
  tone(8, melody[10000], duration);
  delay(100);
  digitalWrite(ledPin, LOW);
  wdt_reset ();   //Watchdog
}

void zero(void)
{
  for (int count = 0; count < 10; count++)
  {
    
    digitalWrite(ledPin, LOW);
    tone(8, melody[0], duration);
    delay(100);
    digitalWrite(ledPin, HIGH);
    tone(8, melody[10000], duration);
    delay(100);
    digitalWrite(ledPin, LOW);
    wdt_reset ();   //Watchdog
  }
}
