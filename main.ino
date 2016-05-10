#include <AirQuality.h>
#include"AirQuality.h"
#include"Arduino.h"
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
AirQuality airqualitysensor;
int current_quality =-1;
void setup()
{
    Serial.begin(9600);
    airqualitysensor.init(14);
     // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
}
void loop()
{
  lcd.clear();
  lcd.print("Starting......");
   delay(20000);
  lcd.clear();
    current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
      
        if (current_quality==0){
            lcd.print("Very High");
             lcd.setCursor(0, 1);
            lcd.print("pollution!");} 
        else if (current_quality==1)
          lcd.print("High pollution!");
        else if (current_quality==2)
            lcd.print("Low pollution!");
        else if (current_quality ==3)
            lcd.print("Fresh air");
     delay(160000);
     
    }
   
}
ISR(TIMER1_OVF_vect)
{
  if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
  {

      airqualitysensor.last_vol=airqualitysensor.first_vol;
      airqualitysensor.first_vol=analogRead(A0);
      airqualitysensor.counter=0;
      airqualitysensor.timer_index=1;
      PORTB=PORTB^0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}
