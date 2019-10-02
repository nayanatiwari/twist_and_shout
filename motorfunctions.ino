#include "CPutil.h"
//Nayana Tiwari Team 3
  const int leftMotorPin1 = 7;
  const int leftMotorPin2 = 6;
  const int rightMotorPin1 = 5;
  const int rightMotorPin2 = 4;
  const int ledPin = 30;
  const int ledRedPin = 52;
  const int buttonPin = 11;
  Led led(ledPin);
  Led redLed(ledRedPin);
  Button button(buttonPin);


  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(30, LOW);
  digitalWrite(32, LOW);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW);
  digitalWrite(36, LOW);
  motorsSetup();
  delay(500);
  Serial.print("we r in bois"); 



}

void loop() {
  // put your main code here, to run repeatedly:

   if (sloHacks())
    {}
    delay(500);
    
}

int sloHacks()
{ 
  int state = 0;
  int returnValue = false;
  while (Serial.available()>0)
  {
    state = Serial.parseInt();
    Serial.flush();
    Serial.print(state);
   if (state < 9 && state > 0)
   {

     if (state == 1)
     {
      leftMotorForward(150);
      rightMotorForward(150);
      delay(1000);
      robotStop();
      returnValue = true;
     
     }      
  
     else if (state == 2)
     {
      leftMotorBackward(150);
      rightMotorBackward(150);
      delay(1000);
      robotStop();
      returnValue = true;
     }
  
     else if (state == 3)
     {
        motorControl(rightMotorPin1, rightMotorPin2, 180);
        delay(850);
        robotStop();
        returnValue = true;
     }
  
     else if (state == 4)
     {
      motorControl(leftMotorPin1,leftMotorPin2, 180);
      delay(800);
      robotStop();
      returnValue = true;
     }
  
     else if (state ==  5)
     {
        if (dance())
        {
          redLed.off();
          returnValue = true;
        }
     }
      
     else if (state == 7)
     {
        if (error())
        {
          redLed.off();
          returnValue = true;
        }
     }
  
     else if (state == 6)
     {
      robotStop();
      returnValue = true;
     }
  
     else if (state == 8)
     {
      if (startup())
        {
          redLed.off();
        }
     }
     returnValue = true;
   }



  }
 return returnValue;
}

int dance()
{
  int value = false;
  for (int i = 0; i < 4; i++)
  {
    int value = false;
    rightMotorForward(100);
    leftMotorBackward(100);
          
    for(int i = 30; i <= 38; i+=2)
    {
      digitalWrite(i,HIGH);
      delay(200);
      digitalWrite(i, LOW);
    }
   robotStop();
  }
  
  value = true;
  return value;
}


int startup()
{
  int returnValue = false;
  led.on();
  delay(500);
  led.off();

  rightMotorForward(100);
  leftMotorBackward(100);
  delay(800);

  leftMotorForward(100);
  rightMotorBackward(100);
  delay(850);
  
  robotStop();
  returnValue = true;
  return returnValue;
}

int error()
{
  int returnValue = false;
  for(int i = 0; i < 6; i++)
  {
    redLed.on();
    delay(200);
    redLed.off();
    delay(200);
    i++;
  }
  returnValue = true;
  return returnValue;
}


void robotStop()
{
  rightMotorStop();
  leftMotorStop();
}

void rightMotorStop()
{
  motorControl(rightMotorPin1, rightMotorPin2, 0);
}

void leftMotorStop()
{
  motorControl(leftMotorPin1, leftMotorPin2, 0);
}

void rightMotorBackward(int aSpeed)
{
  motorControl(rightMotorPin2, rightMotorPin1, aSpeed);
}

void leftMotorBackward(int aSpeed)
{
  motorControl(leftMotorPin2, leftMotorPin1, aSpeed);
}

void rightMotorForward(int aSpeed)
{
  motorControl(rightMotorPin1,rightMotorPin2, aSpeed);
}

void leftMotorForward(int aSpeed)
{
  motorControl(leftMotorPin1,leftMotorPin2, aSpeed);
}

void motorControl(int pin1, int pin2, int aSpeed)
{
  analogWrite(pin1,aSpeed);
  analogWrite(pin2,0);
}

void motorsSetup()
{
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  robotStop();
}
