#include <LiquidCrystal.h> //Please replace the single quote characters ('') with the parenthesis character (<>)
#include "HX711.h"

float calibration_factor =34779.00; 
#define zero_factor 8535481
#define DOUT  A3
#define CLK   A2
#define DEC_POINT  2

float offset=0;
float get_units_kg();

HX711 scale;
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

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
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
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

lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("Your Height: "); // Prints string "Distance" on the LCD
lcd.print(x - distanceCm); // Prints the distance value from the sensor
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
