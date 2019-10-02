
#include "Arduino.h"
#include <SoftwareSerial.h>



SoftwareSerial CR1000Serial(11, 12); // RX, TX

void startComs() {
  CR1000Serial.begin(9600);
}


int getCR1000Time() {
  String readin = "";
  while (CR1000Serial.available()) {
      int bitein = CR1000Serial.read();
      if (isDigit(bitein)) {
        readin += (char)bitein;
      } else {
        int TimeNow = readin.toInt();
        readin = "";
        return(TimeNow);
      }
    }
    return(-1);
}


void writeCR1000Temps(float L, float R) {
  char Lc[5]; char Rc[5];
  dtostrf(L, 4, 2, Lc); dtostrf(R, 4, 1, Rc);
  Serial.print(Lc);
  Serial.println(Rc);
  String toLogger = "L=";
  toLogger += Lc;
  toLogger += "_R=";
  toLogger += Rc;
  toLogger += " ";
  char chrToLogger[50];
  toLogger.toCharArray(chrToLogger, 50);
  Serial.println(chrToLogger);
  CR1000Serial.write(chrToLogger);
}
