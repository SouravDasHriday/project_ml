
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
              
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myServo;

int red=2;
int ir=8;
int irval;
int ir2=9;
int ir2val;
int ir3=10;
int ir3val;

int trigPin = 12;
int echoPin = 13;

int pump1=4;
int pump2=5;
int buzzer=7;
int cam=6;
int camval;

int tmp=A0;
int tmpval;

int beat=A3;
int beatval;


void setup()
{
  Serial.begin(9600);
  //lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Welcome To Our");
  lcd.setCursor(0,1);
  lcd.print("     Project   ");
  
  myServo.attach(11);
  pinMode(ir,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(cam,INPUT);
  
  pinMode(red,OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pump1,OUTPUT);
  pinMode(pump2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(beat,INPUT);
  pinMode(tmp,INPUT);
  delay(100);
  lcd.clear();
}

void loop()
{

 long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);
 
 if((distance<=500)) 
   {
    digitalWrite(red, HIGH);
   }
 else 
   {
     digitalWrite(red, LOW);
   }




  

  irval=digitalRead(ir);
   ir2val=digitalRead(ir2);
    ir3val=digitalRead(ir3);
  

if (irval==1)
{
  digitalWrite(pump1,HIGH);
}
else
{
  digitalWrite(pump1,LOW);
}

if (ir2val==1)
{
  digitalWrite(pump2,HIGH);
  digitalWrite(buzzer,HIGH);
}
else
{
  digitalWrite(pump2,LOW);
  digitalWrite(buzzer,LOW);
}

camval=digitalRead(cam);
tmpval=analogRead(tmp);
tmpval=map(tmpval,1,307,0,200);

lcd.setCursor(10,0);
lcd.print("T:");
lcd.print(tmpval);
Serial.print("tmp");
Serial.println(tmpval);

if (ir3val==1)
{
  if(tmpval<=50 && camval==1)
  {
    myServo.write(90);
  }

}
else
{
  myServo.write(0);
}


  beatval = analogRead(beat);
  beatval=map(beatval,0,1023,0,200);


  lcd.setCursor(0,0);
  lcd.print("BPM:");
  lcd.print(beatval);

  lcd.setCursor(0,1);
  lcd.print("SpO2:");
  lcd.print(beatval-25);
  

  
      delay(10);

}
