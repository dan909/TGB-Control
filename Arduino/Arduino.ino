
#include "UI.h"
#include "Coms.h"

float HotEnd[96]; //this array will hold integers
float ColdEnd[96]; //this array will hold integers

int Menu = 0;
int UsrSel = 0;
int CRTime;

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
  startComs();
  initDisplay();
  memset(HotEnd,0,sizeof(HotEnd));
  memset(ColdEnd,0,sizeof(ColdEnd));
  
  Serial.println("Start");
}


void loop() {
  Serial.println(">");
  UsrSel = getButtonInput();

  CRTime = getCR1000Time();
  if(CRTime > -1) {
    Serial.println(printTime(CRTime));
    writeCR1000Temps(HotEnd[CRTime],ColdEnd[CRTime]);
  }

  
 if (Menu == MENU_Main) {
    printToDisplay("TGB view ^",0);
    printToDisplay("< Setup | Run >",1);
    
    if (UsrSel == LEFT) {
      Menu = MENU_Setup;
    }
    if (UsrSel == UP) {
      Menu = MENU_View;
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
  bool Setting = true;
  int f = 0;
  int t = 96;
  while (f < 96) {
    float Temp = ColdEnd[f];
    while (Setting){
      UsrSel = getButtonInput();
      printToDisplay("L" + TimePartLCD2(f,t),0);
      printToDisplay("Temp = "+String(Temp)+"C",1);
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
          ColdEnd[i] = Temp;
        }
        f = t;
        Menu = MENU_Main;
      } else {
        delay(7);
      }

      if (f == 96) {
        Setting = false;
      } else if (t <= f) {
        t = f-1
      }
    }
  }
 }

 
  delay(100);
  
}// end main loop
