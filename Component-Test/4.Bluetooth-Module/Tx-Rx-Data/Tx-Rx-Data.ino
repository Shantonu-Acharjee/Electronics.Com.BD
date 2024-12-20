// Define the pin for the LED
const int ledPinP = 8;
const int ledPinN = 9;
const int alarmPin = 11;
String message = "";

void setup() {
  Serial.begin(9600); // Begin serial communication with Arduino IDE (Serial Monitor)
  // Initialize the LED pin as output
  pinMode(ledPinP, OUTPUT);
  pinMode(ledPinN, OUTPUT);
  pinMode(alarmPin, OUTPUT);
}

void loop() {
  // Check if there's any data available from the Serial (Bluetooth module)
  if (Serial.available()) {
    message = Serial.readString(); // Read the incoming message
    message.toLowerCase(); // Convert the message to lowercase
    Serial.println(message); // Print the message in lowercase
  }

  if(message == "led on"){
    digitalWrite(ledPinP, HIGH); // Turn the LED on
    digitalWrite(ledPinN, LOW);
    Serial.println("LED ON");
  }
  else if (message == "led off") {
    digitalWrite(ledPinP, LOW); // Turn the LED off
    digitalWrite(ledPinN, LOW);
    Serial.println("LED OFF");
  }

  message = "";
}
