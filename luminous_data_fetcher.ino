
//Arusyak Hovhannesyan
//5-26-19
//Luminous Data Fetcher
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//------------------------
//Joy Stick
int SW = 3;
int LS = A1; //Light Sensor
//-------------------------------
RF24 radio(4,10);   //CSn
const byte address[6] = "00001";
void setup()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_2MBPS);
  Serial.begin(115200);
  pinMode(SW, INPUT);
}
void loop() 
{
  int ls = 0;
  int turnval = 0;
  ls = analogRead(LS);
  Serial.print("Light Reading: ");
  Serial.print(ls);
  Serial.print("\n");
  delay(500);
}
