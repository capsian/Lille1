// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <math.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

int a;
float t;
int B=3975;                  //B value of the thermistor
float resistance;
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop()
{
  a=analogRead(0);
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  t=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet ;
  
  Serial.print("Current temperature is ");
  Serial.println(t);
  
  if (t <=12) pos = 0;
  else if(t > 20 && t < 30)
  {
    pos = map(t,12,30,180,0);
  }
  else if (t>= 30) pos = 180;
  else pos = 180;
  myservo.write(pos);
  delay(1000);
 }
