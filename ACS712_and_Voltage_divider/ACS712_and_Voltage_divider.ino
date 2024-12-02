#include <LiquidCrystal.h>
#define VT                        A0      // Pin connected to Voltage divider to sense the voltage above 5v
#define sensorPin                 A1      // Pin connected to ACS712 output
const float Vref                = 5.0;    // Reference voltage of Arduino (5V)
const int ADC_Resolution        = 1023;   // 10-bit ADC resolution
const float sensitivity         = 0.0715; // Sensitivity of ACS712 (e.g., 0.066 V/A for 30A module) I might change it for calibration 
const float zeroCurrentVoltage  = 2.5;    // Output voltage at 0A current (for ACS712)

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(VT,INPUT);
  pinMode(sensorPin,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop()
{
  int VTreadings = analogRead(VT);
  float Voltage = VTreadings * (5.0/1023.0) * 5;
  float Current = Current_Measures()*1000;

  Serial.print("Voltage: ");
  Serial.print(Voltage);
  Serial.print(" V");
  Serial.print(" - Current: ");
  Serial.print(Current, 3);
  Serial.print(" mA");
  Serial.print(" - Power: ");
  Serial.print(Current * Voltage, 3);
  Serial.println(" mW");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(Voltage);
  lcd.print(" - I:");
  lcd.print(Current);
  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(Current * Voltage);
  lcd.print(" mW");
  delay(300);
}

float Current_Measures()
{
  // Read the analog value
  int adcValue = analogRead(sensorPin);

  // Convert ADC value to voltage
  float voltage = adcValue * (Vref / ADC_Resolution);

  // Calculate the current
  float current = (voltage - zeroCurrentVoltage) / sensitivity;
  
  return current;
}
