// this revision adds the functionality of reading all values from memory, calculating a running average and sending these data to serial communications
// the actual serial communications will be implemented in a later revision

#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "iEEPROM.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int address = 0;
int addressoff = 0;
int sensorLow = 0;
int sensorHigh = 1023;
int serialcounter = 0;
double runningSum = 0;
double average = 0;
int state = 0;


// the setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialize LCD
  lcd.begin(16,2);
  
  //iEEPROM_read(0, address);
  //iEEPROM_read(1, addressoff);
  
  // Serial.print("Reading,Average");
  // Serial.println();
}

// the loop routine runs over and over again forever:
// displays the analog voltage measurement and then displays the value saved to EEPROM for that measurement
// makes one reading every 3 seconds
void loop() {
  
  serialcounter++;
  
  // take measurement and save to EEPROM
  int digitalVoltage = readDigital();
  address += iEEPROM_write(address, digitalVoltage);
  
  delay(500);
  
  int voltage;
  addressoff += iEEPROM_read(addressoff, voltage);
  double analogVoltage = convertToAnalog(voltage);
  
  /*runningSum += analogVoltage;
  average = runningSum/serialcounter;

  displayData(analogVoltage);
 
  Serial.print(analogVoltage);
  Serial.print(",");
  Serial.print(average);
  Serial.println();*/
  /*
  if(Serial.available() > 0) {
    state = Serial.read();
    delay(1000);
  }
  
  // comment if only for test purpose 
  if (state) {
     toBlueTooth();
  }*/
  
  delay(1000);
  
  iEEPROM_write(0, address);
  iEEPROM_write(1, addressoff);

  delay(1000);

  displayClear();
  
  delay(500);
  
  // if address is 512 than the EEPROM is full and new values rewrite the old values
  if (address >= 64) {
    address = 2;
  }
  
  if (addressoff >= 64) {
    addressoff = 2;
  }
  
  /*if (serialcounter == 4) {
    calculations();
  }*/ 
  toBlueTooth();
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


//sends the values from the sensor over serial to BT module
void toBlueTooth()
 {
   int size;
   int readAddress; 
   int BTvoltage;
   int i = 0;
   
   if(addressoff>2){
       size = ((addressoff-2)/2);
        int data[size];
       readAddress = 2;
      
      
      while (readAddress < addressoff) 
      {
        readAddress += iEEPROM_read(readAddress, BTvoltage);
        data[i] = BTvoltage;
        i++;
      }
      Serial.println(size);
      Serial.println(addressoff);
      Serial.print("Data Start: ");
  
      for(int k = 0; k < size; k++)
        {
          Serial.print(data[k]);
          Serial.print(", ");
        }
       Serial.print(" Data Ends."); 
       Serial.println();
       delay(10);
     }
       
        
}
