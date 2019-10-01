
#include <SoftwareSerial.h>
#include "Arduino.h"


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
        CR1000Serial.write("L13-R15 ");
        return(TimeNow);
      }
    }
    return(-1);
}
