/*
  TCS230 color recognition sensor
  modified on 7 May 2019
  by Mohammadreza Akbari @ Electropeak
  https://electropeak.com/learn/

Color Sensor      Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                8
 s1                9
 s2                10
 s3                11
 OUT               12
 OE                GND
*/
const int s0 = 7;  
const int s1 = 8;  
const int s2 = 10;  
const int s3 = 11;  
const int out = 12;   
// LED pins connected to Arduino
int redLed = 2;  
int greenLed = 3;  
int blueLed = 4;
// Variables  
int red = 0;  
int green = 0;  
int blue = 0;
int cal_min = 5;
int cal_max_r = 50;
int cal_max_g = 50;
int cal_max_b = 50;
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void calibrate() {
  Serial.println("Clear sensor area. Then enter c again");
    while (Serial.read() != 'c') {
      //do nothing
      ;
    }
    color();
    cal_max_r = red;
    cal_max_g = green;
    cal_max_b = blue;
    Serial.println("Put white color infront of sensor, Then enter c again");
    while (Serial.read() != 'c') {
      //do nothing
      ;
    }
    color();
    cal_min = (red + green + blue) / 3;
    Serial.println("calibrated successfully.");
    delay(300);
}
    
void setup()   
{  
  Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  pinMode(redLed, OUTPUT);  
  pinMode(greenLed, OUTPUT);  
  pinMode(blueLed, OUTPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  //calibrate();
}  
    
void loop() 
{  
  color(); 
  //red = map(red, cal_min, cal_max_r, 255, 0);
  //green = map(green, cal_min, cal_max_g, 255, 0);
  //blue = map(blue, cal_min, cal_max_b, 255, 0);
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
  //Serial.println();  

  if (red < blue && red < green && red < 30)
  {  
   Serial.println(" - (Red Color)");  
   digitalWrite(redLed, HIGH); // Turn RED LED ON 
   digitalWrite(greenLed, LOW);  
   digitalWrite(blueLed, LOW); 
   delay(2000); 
  }  

  else if (blue < red && blue < green)   
  { 
    if(blue < 60) {
      Serial.println(" - (Blue Color)");  
      digitalWrite(redLed, LOW);  
      digitalWrite(greenLed, LOW);  
      digitalWrite(blueLed, HIGH); // Turn BLUE LED ON 
      delay(2000); 
    }
    else{
      Serial.println(" - (NO Color)"); 
    }
  }  

  else if (green < red && green < blue)  
  {  
   Serial.println(" - (Green Color)");  
   digitalWrite(redLed, LOW);  
   digitalWrite(greenLed, HIGH); // Turn GREEN LED ON 
   digitalWrite(blueLed, LOW);  
   delay(2000); 
  }  
  else{
  Serial.println();  
  }
  delay(300);   
  digitalWrite(redLed, LOW);  
  digitalWrite(greenLed, LOW);  
  digitalWrite(blueLed, LOW);  
 }