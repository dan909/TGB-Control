#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX
char bitein;
char readin;


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
  delay(50);
  if (mySerial.available()) {
    delay(50);
    bitein = mySerial.read();
    Serial.println(bitein);
    if (bitein == '/') {
      Serial.println(readin);
      Serial.println(printTime(int(readin)));
      readin = '/';
    } else {
      readin = readin + bitein;
    }
    delay(50);
    mySerial.write("OK");
  }
}
