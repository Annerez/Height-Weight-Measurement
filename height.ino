#include <LiquidCrystal.h>
#include "HX711.h"

float calibration_factor = 1.00; //your calibration factor
#define zero_factor //Your zero factor
#define DOUT  A3
#define CLK   A2
#define DEC_POINT  2

float offset=0;
float get_units_kg();

HX711 scale;
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;

void setup() {
  
scale.begin(DOUT, CLK);
Serial.begin(115200);
Serial.println("Load Cell");
scale.set_scale(calibration_factor); 
scale.set_offset(zero_factor);
lcd.begin(16,2);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

}

void loop() {
const int x = 200;  

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
String data = String(get_units_kg()+offset, DEC_POINT);

lcd.setCursor(0,0); 
lcd.print("Your Height: ");
lcd.print(x - distanceCm); 
lcd.print("  cm");
lcd.setCursor(0,1);
lcd.print("Your Weight: "); 
lcd.print(data);
lcd.print(" kg");
delay(500);

lcd.setCursor(0,1);
lcd.print("  Have Fun^_^");

}

float get_units_kg()
{
  return(scale.get_units()*0.453592);
}
