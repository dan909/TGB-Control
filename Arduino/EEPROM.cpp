/*
 * Header file for UI.cpp
 */
#include <EEPROM.h>
#include "Arduino.h"

int addressFind(int no, bool side, bool Int) {
  int address = no;

  if (Int) {
    address = address + 100;
  }
  
  if(side) {//Falce == left
    address = address + 300;
  }

  //Serial.print("Address = ");
  //Serial.println(address);
  
  return address;
}

void saveTemp(float Temp, int no, char side) {
 
  Temp = Temp + 100.0;

  int Tmp = floor(Temp);
  int Des = round((Temp - Tmp)*100);

  if (side == "R") {
    EEPROM.update(addressFind(no,1,1), Tmp);
    EEPROM.update(addressFind(no,1,0), Des);
  } else {
    EEPROM.update(addressFind(no,0,1), Tmp);
    EEPROM.update(addressFind(no,0,0), Des);
  }

}


float readTemp(int no, char side) {
  int Tmp;
  int Des;
  float Temp;
  
  if (side == "R") {
    Tmp = EEPROM.read(addressFind(no,1,1));
    Des = EEPROM.read(addressFind(no,1,0));
  } else {
    Tmp = EEPROM.read(addressFind(no,0,1));
    Des = EEPROM.read(addressFind(no,0,0));
  }

  Temp = Tmp;
  Temp = (Temp-100) + (float(Des)/100);

  //Serial.print("Line is = ");
  //Serial.println(Temp);

  return Temp;
}
