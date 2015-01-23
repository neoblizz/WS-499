// this revision adds the functionality of reading all values from memory, calculating a running average and sending these data to serial communications
// the actual serial communications will be implemented in a later revision

#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "iEEPROM.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int address = 0;
int addressoff = 0;
int x;

// the setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialize LCD
  lcd.begin(16,2);
  
  iEEPROM_write(0, address);
  iEEPROM_write(1, addressoff);
}

// the loop routine runs over and over again forever:
// displays the analog voltage measurement and then displays the value saved to EEPROM for that measurement
// makes one reading every 3 seconds
void loop() {
  
  // take measurement and save to EEPROM
  iEEPROM_read(0, x);
  displayData();
  
  delay(1000);
  
  displayClear();
    
}


// Displays read data on the LCD:
void displayData () {
  
  lcd.setCursor(0,0); // set the cru
  lcd.print("ADDRESS READING");
  
  lcd.setCursor(5,1);
  lcd.print(x);
  lcd.setCursor(9,1);
  lcd.print(" ADD");
  
  return;
}

// Clears the display to cause blinking effect:
void displayClear() {
 lcd.setCursor(5,1);
 lcd.print("     ");
 return; 
}
