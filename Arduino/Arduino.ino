
#include "UI.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, TX

float HotEnd[96]; //this array will hold integers
float ColdEnd[96]; //this array will hold integers

int R = 0;
int Menu = 0;
int UsrSel = 0;
int bitein;
int TimeNow;

String readin = "";


//Menu shortcuts.
#define MENU_Main 0
#define MENU_View 5
#define MENU_Temp 10
#define MENU_Setup 9
#define MENU_SetupL 11
#define MENU_SetupR 12
#define MENU_Save 20

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define SELECT 5


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  initDisplay(); 
}


void loop() {
  //Serial.print("R: "); Serial.println(R);
  UsrSel = getButtonInput();
    
 if (Menu == MENU_Main) {
  if (R == 0) {
    printToDisplay("TGB stopped",0);
    printToDisplay("< Setup | Run >",1);
    
    if (UsrSel == RIGHT) {
      R = 1;
    }
    if (UsrSel == LEFT) {
      Menu = MENU_Setup;
    }
  } else {
    printToDisplay("Running | view ^",0);
    printToDisplay("< Temp | Stop >",1);
    if (UsrSel == RIGHT) {
      R = 0;
    }
    if (UsrSel == LEFT) {
      Menu = MENU_Temp;
    }
    if (UsrSel == UP) {
      Menu = MENU_View;
    }

    if (mySerial.available()) {
      bitein = mySerial.read();
      if (isDigit(bitein)) {
        readin += (char)bitein;
      } else {
        TimeNow = readin.toInt();
        Serial.println(printTime(TimeNow));
        readin = "";
        mySerial.write("L 13 - R 5");
      }
    }
  
  }
 }


 if (Menu == MENU_View) {
  for (int i=0; i<96; i++){
    UsrSel = getButtonInput();
    printToDisplay(TimePartLCD(i),0);
    printToDisplay(TempPartLCD(ColdEnd[i],HotEnd[i]),1);
    if (i >= 0 && i < 96) {
      if (UsrSel == UP || UsrSel == RIGHT) {
        i=i+1;
      } else if (UsrSel == DOWN || UsrSel == LEFT) {
        i=i-2;
      } else if (UsrSel == SELECT){
        Menu = MENU_Main;
        break;
      } else {
        delay(600);
      }
      delay(100);
    }
  }
      Menu = MENU_Main;
      clearDisplay();
 }


 if (Menu == MENU_Setup) {
  UsrSel = getButtonInput();
  if (UsrSel == LEFT) {
    Menu = MENU_SetupL;
    printToDisplay(" Left ",0);
  } else if (UsrSel == RIGHT) {
    Menu = MENU_SetupR;
    printToDisplay(" Right ",0);
  } else if (UsrSel == UP || UsrSel == DOWN || UsrSel == SELECT){
    Menu = MENU_Main;
  } else {
    printToDisplay(" Set TGB Temps? ",0);
    printToDisplay("< Left | Right >",1);
  }  
 }


 
 if (Menu == MENU_SetupL) {
  int i = 0;
  float Temp = 0.00;
  bool Setting = true;
  while (Setting) {
    UsrSel = getButtonInput();
    printToDisplay("L" + TimePartLCD(i),0);
    printToDisplay("Temp = "+String(ColdEnd[i])+"C",1);
    if (UsrSel == UP) {
      ColdEnd[i] = ColdEnd[i] + 0.1;
    } else if (UsrSel == DOWN) {
      ColdEnd[i] = ColdEnd[i] - 0.1;
    } else if (UsrSel == LEFT){
      i--;
    } else if (UsrSel == RIGHT){
      i++;
    } else if (UsrSel == SELECT){
      Temp = ColdEnd[i];
    } else {
      delay(10);
    }
  }
 }

 
  delay(100);
  
}// end main loop
