#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "iEEPROM.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int address = 0;
int addressoff = 0;
int sensorLow = 0;
int sensorHigh = 1023;

// the setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialize LCD
  lcd.begin(16,2);
}

// the loop routine runs over and over again forever:
// displays the analog voltage measurement and then displays the value saved to EEPROM for that measurement
// makes one reading every 3 seconds
void loop() {
  
  // take measurement and save to EEPROM
  int digitalVoltage = readDigital();
  address += iEEPROM_write(address, digitalVoltage);
  
  delay(1000);
  
  int voltage;
  addressoff += iEEPROM_read(addressoff, voltage);
  double analogVoltage = convertToAnalog(voltage);

  displayData(analogVoltage);

  delay(3000);

  displayClear();
  
  delay(1000);
  
  // if address is 512 than the EEPROM is full and new values rewrite the old values
  if (address == 512) {
    address = 0;
  }
  
  if (addressoff == 512) {
    addressoff = 0;
  }
  
}

// Reads and return digital voltage:
int readDigital() {
  // read the input on analog pin 2:
  int sensorValue = analogRead(A2); // using anolg to read the input
  
  if (sensorValue > sensorHigh) {
    sensorValue = sensorHigh;
  } else if (sensorValue < sensorLow) {
    sensorValue = sensorLow;
  }
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  int voltage = sensorValue;
  return voltage; 
}

double convertToAnalog(double voltage) {
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  voltage = voltage * (5.0 / 1023.0);
  return voltage;
}

// Displays read data on the LCD:
void displayData (double voltage) {
  
  lcd.setCursor(0,0); // set the cru
  lcd.print("VOLTAGE READING");
  
  lcd.setCursor(5,1);
  lcd.print(voltage);
  lcd.setCursor(9,1);
  lcd.print("V");
  
  return;
}

// Clears the display to cause blinking effect:
void displayClear() {
 lcd.setCursor(5,1);
 lcd.print("     ");
 return; 
}

// We need:
// Display original analog reading.
// Display from memory.
// Serial port writing to a text file.

