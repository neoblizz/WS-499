#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

// the setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialize LCD
  lcd.begin(16,2);
}

// the loop routine runs over and over again forever:
void loop() {
  
  double analogVoltage = readAnalog();
  displayData(analogVoltage);
  delay(1000);
  displayClear();
  delay(1000);
  
}

// Reads and return analog voltage:
double readAnalog() {
  // read the input on analog pin 2:
  int sensorValue = analogRead(A2); // using anolg to read the input
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  double voltage = sensorValue * (5.0 / 1023.0);
  return voltage; 
}

// Displays read data on the LCD:
void displayData (double voltage) {
  
  lcd.setCursor(0,0); // set the cru
  lcd.print("VOLTAGE READING");
  
  if (voltage == 0) {
    lcd.setCursor(5,1);
    lcd.print("ERROR");
  } else {
    lcd.setCursor(5,1);
    lcd.print(voltage);
    lcd.setCursor(9,1);
    lcd.print("V");
  }
  return;
}

// Clears the display to cause blinking effect:
void displayClear() {
 lcd.setCursor(5,1);
 lcd.print("     ");
 return; 
}
