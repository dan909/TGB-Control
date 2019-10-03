
#include "Arduino.h"
#include "UI.h"
#include <LiquidCrystal.h>


//LCD pin to Arduino
#define pin_RS 8 
#define pin_EN 9
#define pin_d4 4 
#define pin_d5 5 
#define pin_d6 6 
#define pin_d7 7 
#define pin_BL 10


LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);



//Low and high values for buttons.
#define RIGHT_LOW -100
#define RIGHT_HIGH 75

#define LEFT_LOW 300
#define LEFT_HIGH 500

#define UP_LOW 80
#define UP_HIGH 120

#define DOWN_LOW 150
#define DOWN_HIGH 300

#define SEL_LOW 520
#define SEL_HIGH 750

int INPUT_BUTTONS = 0;


/*
 * Function to initialize LCD display. Code from Neal Snooke (nns@aber.ac.uk)
 */
void initDisplay() {
  delay(300);
  lcd.begin(16, 2);
  
  lcd.home();      
}


/*
 * Given a raw value, this function works out and returns which button was pressed.
 */
byte getButtonNum(int rawVal) {

  if(rawVal > RIGHT_LOW && rawVal < RIGHT_HIGH) {
    return 1;
  }
  else if(rawVal > LEFT_LOW && rawVal < LEFT_HIGH) {
    return 2;
  }
  else if(rawVal > UP_LOW && rawVal < UP_HIGH) {
    return 3;
  }
  else if(rawVal > DOWN_LOW && rawVal < DOWN_HIGH) {
    return 4;
  }
  else if(rawVal > SEL_LOW && rawVal < SEL_HIGH) {
    return 5;
  }
  else {
    return 0;
  }
}


/*
 * Function to clear a specific line on the LCD display. Code from Neal Snooke (nns@aber.ac.uk)
 */
void clearLCDLine(byte line) {
  
  lcd.setCursor (0, line);        // go to the next line
  lcd.print ("                    ");
  lcd.setCursor (0, line);
}

void clearDisplay() {
  clearLCDLine(0);
  clearLCDLine(1);
}


/*
 * Clear the display line specified, then print to it. Code from Neal Snooke (nns@aber.ac.uk)
 */
void printToDisplay(String message, byte line) {
  lcd.home();
  clearLCDLine(line);
  lcd.print(message);
}


/*
 * Make into time of day
 */
String printTime(int no) {
  int H = floor(no/4);
  int M = no % 4;
  M = M * 15;
  char Time[17];
  sprintf(Time,"%02i:%02i",H,M);
  String Ttime = String(Time);
  return Time;
}


/*
 * Make a char of the times
 */
String TimePartLCD(int T) {
  String LineChar = "@ "+ String(printTime(T)) +" - "+ String(printTime(T++));
  return LineChar;
}

/*
 * Make a char of the times
 */
String TimePartLCD2(int T1, int T2) {
  String LineChar = "@ "+ String(printTime(T1)) +" - "+ String(printTime(T2));
  return LineChar;
}

/*
 * Make a char of the Temps
 */
String TempPartLCD(float A,float B) {
  String LineChar = "L " + String(A) + " R " + String(B);
  return LineChar;
}


/*
 * Function which takes an average of ten readings from the input buttons, and returns
 * that average.
 */
int getButtonPress() {

  int buttonInput;
  unsigned int buttonAvg = 0;
  byte i;

  //Take ten readings and average them
  for(i=0; i<10; i++) {                       
    buttonInput = analogRead(INPUT_BUTTONS);
    buttonAvg += buttonInput;
  }
    
  buttonInput = buttonAvg / 10;
  
  delay(250);   //A delay here stops the button press from running into the next option
  
  return buttonInput;
}


/*
 * Function to read from the input buttons. The function will time out after 5 seconds
 * if no buttons are pressed.
 */
byte getButtonInput() {

  unsigned long startTime = millis();
  int buttonVal;
  byte buttonNum = 0; //Default to no button pressed

  while(millis() - startTime < 8000) { //Timeout after 8 seconds of inactivity

    if(analogRead(INPUT_BUTTONS) != 1023) {

      buttonVal = getButtonPress();
      buttonNum = getButtonNum(buttonVal);
      
      break;
    }
  }

  return buttonNum;
}
