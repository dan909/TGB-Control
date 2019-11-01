
#include "UI.h"
#include "Coms.h"
#include "EEPROM.h"

float LeftEnd[96]; //this array will hold 
float RightEnd[96]; //this array will hold 

int Menu = 0;
int UsrSel = 0;
int CRTime;
int Rnd =0;

bool Setting;
int f;
int t;
float Temp;

//Menu shortcuts.
#define MENU_Main 0
#define MENU_View 5
#define MENU_Setup 9
#define MENU_SetupL 11
#define MENU_SetupR 12

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define SELECT 5


void setup() {
  Serial.begin(9600);
  startComs();
  initDisplay();
  Serial.println("Start");

  for(int i=0; i<96; i++) {  
    RightEnd[i] = readTemp(i,1);
    LeftEnd[i] = readTemp(i,0);
  }
}


void loop() {
  Serial.println(">");
  UsrSel = getButtonInput();

  CRTime = getCR1000Time();
  if(CRTime > -1) {
    Serial.println(printTime(CRTime));
    writeCR1000Temps(LeftEnd[CRTime],RightEnd[CRTime]);
    Rnd = random(1, 150);
  } else {
    Rnd = 0;
  }

  
 if (Menu == MENU_Main) {
    if(Rnd >= 100) {printToDisplay("TGB Running.",0);}
    if(Rnd < 100) {printToDisplay("TGB Running .",0);}
    if(Rnd < 50) {printToDisplay("TGB Running  .",0);}
    if(Rnd < 1) {printToDisplay("TGB Running",0);}
    printToDisplay("< Setup | View >",1);
    
    if (UsrSel == LEFT) {
      Menu = MENU_Setup;
    }
    if (UsrSel == RIGHT) {
      Menu = MENU_View;
    }    
  }


 if (Menu == MENU_View) {
  for (int i=0; i<96; i++){
    UsrSel = getButtonInput();
    printToDisplay(TimePartLCD(i),0);
    printToDisplay(TempPartLCD(RightEnd[i],LeftEnd[i]),1);
    if (i >= 0 && i < 96) {
      if (UsrSel == UP || UsrSel == RIGHT) {
        i=i+1;
      } else if (UsrSel == DOWN || UsrSel == LEFT) {
        i=i-2;
      } else if (UsrSel == SELECT){
        Menu = MENU_Main;
        break;
      } else {
        delay(500);
      }
      delay(100);
    }
  }
      Menu = MENU_Main;
      clearDisplay();
 }


 if (Menu == MENU_Setup) {
  printToDisplay(" Set TGB Temps? ",0);
  printToDisplay("< Left | Right >",1);
  
  UsrSel = getButtonInput();
  
  if (UsrSel == LEFT) {
    Menu = MENU_SetupL;
    printToDisplay(" Left ",0);
  }
  if (UsrSel == RIGHT) {
    Menu = MENU_SetupR;
    printToDisplay(" Right ",0);
  }
  if (UsrSel == UP || UsrSel == DOWN || UsrSel == SELECT){
    Menu = MENU_Main;
  }
 }


 
 if (Menu == MENU_SetupR) {
  Setting = true;
  f = 0;
  t = 0;
  while (f != 96) {
    Temp = RightEnd[f];

    for(int i=t; i<96; i++) {
      t = i;
      if(RightEnd[i] != Temp) {
        break;
      }
    }
    
    while (Setting){
      printToDisplay("R" + TimePartLCD2(f,t),0);
      printToDisplay("Temp = "+String(Temp)+"C",1);
      UsrSel = getButtonInput();
      if (UsrSel == UP) {
        Temp += 0.05;
      } else if (UsrSel == DOWN) {
        Temp -= 0.05;
      } else if (UsrSel == LEFT){
        t--;
      } else if (UsrSel == RIGHT){
        t++;
      } else if (UsrSel == SELECT){
        for(int i=f; i<=t; i++) {  
          RightEnd[i] = Temp;
        }
        f = t;
        Menu = MENU_Main;
      } else {
        delay(7);
      }

      if (Temp < -20) {
        Temp = -20;
      }  else if (Temp > 65) {
        Temp = 65;
      }

      if (f == 96) {
        Setting = false;
      } else if (t > 96) {
        t = 96;
      } else if (t <= f) {
        t = f+1;
      }
    }
  }
  
  printToDisplay("R Saving",0);
  for(int i=0; i<96; i++) {  
    saveTemp(RightEnd[i],i,1);
  }
  printToDisplay("R Temps Saved",0);
  printToDisplay("  [main menu]",1);
 }

 if (Menu == MENU_SetupL) {
  Setting = true;
  f = 0;
  t = 0;
  while (f != 96) {
    Temp = LeftEnd[f];

    for(int i=t; i<96; i++) {
      t = i;
      if(LeftEnd[i] != Temp) {
        break;
      }
    }
    
    while (Setting){
      printToDisplay("L" + TimePartLCD2(f,t),0);
      printToDisplay("Temp = "+String(Temp)+"C",1);
      UsrSel = getButtonInput();
      if (UsrSel == UP) {
        Temp += 0.05;
      } else if (UsrSel == DOWN) {
        Temp -= 0.05;
      } else if (UsrSel == LEFT){
        t--;
      } else if (UsrSel == RIGHT){
        t++;
      } else if (UsrSel == SELECT){
        for(int i=f; i<=t; i++) {  
          LeftEnd[i] = Temp;
        }
        f = t;
        Menu = MENU_Main;
      } else {
        delay(7);
      }

      if (Temp < -31) {
        Temp = -31;
      }  else if (Temp > 40) {
        Temp = 40;
      }

      if (f == 96) {
        Setting = false;
      } else if (t > 96) {
        t = 96;
      } else if (t <= f) {
        t = f+1;
      }
    }
  }
  
  printToDisplay("L Saving",0);
  for(int i=0; i<96; i++) {  
    saveTemp(LeftEnd[i],i,0);
  }
  printToDisplay("L Temps Saved",0);
  printToDisplay("  [main menu]",1);
 }
 
  delay(100);
  
}// end main loop
