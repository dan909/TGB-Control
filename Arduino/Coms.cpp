
#include <SoftwareSerial.h>

SoftwareSerial CR1000Serial(11, 12); // RX, TX


int getCR1000Time () {
  if (mySerial.available()) {
      int bitein = CR1000Serial.read();
      if (isDigit(bitein)) {
        readin += (char)bitein;
      } else {
        TimeNow = readin.toInt();
        readin = "";
        CR1000Serial.write("L13-R15");
      }
      return(TimeNow)
    }
    return(-1)
}
