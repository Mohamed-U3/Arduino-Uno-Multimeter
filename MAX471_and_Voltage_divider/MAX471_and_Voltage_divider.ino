#include <LiquidCrystal.h>
#define VT A0
#define AT A1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(VT,INPUT);
  pinMode(AT,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop()
{
  float VTreadings = analogRead(VT);
  float ATreadings = analogRead(AT);
  float Voltage = VTreadings * (5.0/1023.0) * 5;
  float Current = ATreadings * (5000.0/1023.0);

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
