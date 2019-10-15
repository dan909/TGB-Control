
#include "UI.h"
#include "Coms.h"
#include "EEPROM.h"

float LeftEnd[96]; //this array will hold integers
float RightEnd[96]; //this array will hold integers

int Menu = 0;
int UsrSel = 0;
int CRTime;
int Rnd =0;

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
    RightEnd[i] = readTemp(i,"R");
    LeftEnd[i] = readTemp(i,"L");
  }
}


void loop() {
  Serial.println(">");
  UsrSel = getButtonInput();

  CRTime = getCR1000Time();
  if(CRTime > -1) {
    Serial.println(printTime(CRTime));
    writeCR1000Temps(LeftEnd[CRTime],RightEnd[CRTime]);
  }

  
 if (Menu == MENU_Main) {
    Rnd = random(1, 200);
    if(Rnd >= 150) {printToDisplay("TGB Running.",0);}
    if(Rnd < 150) {printToDisplay("TGB Running .",0);}
    if(Rnd < 100) {printToDisplay("TGB Running  .",0);}
    if(Rnd < 50) {printToDisplay("TGB Running   .",0);}
    if(Rnd < 10) {printToDisplay("TGB Running    .",0);}
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
        delay(600);
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
  bool Setting = true;
  int f = 0;
  int t = 96;
  while (f != 96) {
    float Temp = RightEnd[f];
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
    saveTemp(RightEnd[i],i,"R");
  }
  printToDisplay("R Temps Saved",0);
  printToDisplay("  [main menu]",1);
 }

 if (Menu == MENU_SetupL) {
  bool Setting = true;
  int f = 0;
  int t = 96;
  while (f != 96) {
    float Temp = LeftEnd[f];
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
    saveTemp(LeftEnd[i],i,"L");
  }
  printToDisplay("L Temps Saved",0);
  printToDisplay("  [main menu]",1);
 }
 
  delay(100);
  
}// end main loop
