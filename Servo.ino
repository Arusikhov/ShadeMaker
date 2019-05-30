#include <Servo.h>

Servo myservo;
int SW = 3;
int PWM = 9;

int VRY = A1;
int VRX = A0;
int xval = 0;
int yval = 0;

void setup()
{
  pinMode(SW, INPUT);
  myservo.attach(PWM);   //setting servo to D6 (SW in diagram)
  Serial.begin(9600);
}
void loop()
{
  Serial.print("x-Axis:");
  Serial.print(analogRead(VRX));
  Serial.print("\n");
  Serial.print("y-axis:");
  Serial.print(analogRead(VRY));
  Serial.print("\n\n");
  
  xval = analogRead(VRX);
  yval = analogRead(VRY);
  myservo.write(1500);        //setting servo to a stand still

if(xval > 550)                 //if VRX input isnt at rest, turn CC
  {
    myservo.write(1400);
  }
else if(xval < 480)                 //if VRY input isnt at rest, turn clockwise
  {
    myservo.write(1600);
  }
else
  {
    myservo.write(1500);
  } 
  delay(1000); 
}
