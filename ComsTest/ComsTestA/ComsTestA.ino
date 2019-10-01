#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX
int bitein;
String readin = "";
int TimeNow;

String printTime(int no) {
  int H = floor(no/4);
  int M = no % 4;
  M = M * 15;
  char Time[17];
  sprintf(Time,"%02i:%02i",H,M);
  String Ttime = String(Time);
  return Time;
}


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  Serial.println("Testing Coms...");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() { // run over and over

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
