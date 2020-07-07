#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include<Wire.h>
#include<MQ2.h>

LiquidCrystal_I2C lcd(0x27, 16,2);
SoftwareSerial gsm(2,3);
SoftwareSerial mySerial(2, 3);

#define buzzerPin 10
#define gasPin A0

int Analog_Input = A0;
MQ2 mq2(Analog_Input);

void setup()
{  
mySerial.begin(2400);    
Serial.begin(200);
lcd.begin();
pinMode(buzzerPin,OUTPUT);
lcd.backlight();
mq2.begin();
lcd.setCursor(0, 0);
lcd.print("Calibrating");
for(int i = 0; i <10; i++)
{
if (i==4) {
lcd.setCursor(0, 1);
lcd.print("."); }
else lcd.print(".");
delay(500);
}
lcd.setCursor(5, 1);
lcd.print("done"); delay(1000);
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("SENSOR ACTIVE");
delay(1500);
lcd.clear();
}

void loop()
{
int gasSensor = analogRead(gasPin);
if (gasSensor > 500)
{
sendmessage();
digitalWrite(buzzerPin,HIGH);
lcd.setCursor(0, 0);
lcd.print("Value : ");
lcd.print(gasSensor);
Serial.print(gasSensor);
Serial.print("\t");
lcd.setCursor(0, 1);
Serial.println("Gas is Detected");
lcd.print("Gas is Detected");
delay(300); 
lcd.clear();
}
else if (gasSensor < 500)
{
digitalWrite(buzzerPin,LOW);
lcd.setCursor(0, 0);
lcd.print("Value : ");
lcd.print(gasSensor);
Serial.print(gasSensor);
Serial.print("\t"); 
lcd.setCursor(0,1); 
Serial.println("No Gas");
lcd.print("No Gas");
delay(300);
}
}

void sendmessage()
{
  delay(10000);
  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919182156686\"\r"); //replace x by your number
  delay(1000);
  gsm.println("Gas Detected!!!PLEASE BE ALERT");
  delay(100);
  gsm.println((char)26);
  delay(1000); 
}
