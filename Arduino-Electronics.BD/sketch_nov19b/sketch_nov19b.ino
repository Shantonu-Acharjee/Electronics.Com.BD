#include <SoftwareSerial.h>
SoftwareSerial nano(14,12);
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
  nano.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (nano.available()) {
Serial.write(nano.read());
}
}
