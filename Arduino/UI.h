/*
 * Header file for UI.cpp
 */

void initDisplay();
byte getButtonNum(int rawVal);
void clearDisplay();
void clearLCDLine(byte line);
void printToDisplay(String message, byte line);
String printTime(int no);
String TimePartLCD(int T);
String TimePartLCD2(int T1, int T2);
String TempPartLCD(float A,float B);
int getButtonPress();
byte getButtonInput();
