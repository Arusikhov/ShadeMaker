//wireless module libraries
#include<SPI.h>
#include<RF24.h>

//light sensor libraries
int SW = 3;
int LS = A1; //Light Sensor

#include <printf.h>

// ce, csn pins
RF24 radio(9, 10) ;

void setup(void){
  Serial.begin(115200);
  
  radio.begin() ;
  radio.setPALevel(RF24_PA_MAX) ;
  radio.setChannel(0x76) ;
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.openReadingPipe(1,0xE8E8F0F0E1LL); 
  radio.enableDynamicPayloads() ;
  radio.setDataRate( RF24_1MBPS );
  radio.powerUp() ;
  
  pinMode(SW, INPUT);
}

void loop(void){
  //---------------------------------
  //Writing data to send
  int ls = 0;
  int turnval = 0;
  ls = analogRead(LS);
  //const char text[] = "empty";
  if(ls >= 500){
     const char text[] = "open";
     radio.write(&text, sizeof(text)) ;
  } else {
     const char text[] = "close";
     radio.write(&text, sizeof(text)) ;
  }
  Serial.print("Light Reading: ");
  Serial.print(ls);
  Serial.print("\n");
  //--------------------------------
  //recieving data
  radio.startListening();
  char receivedMessage[32] = {0};
  if(radio.available())
  {
    radio.read(receivedMessage, sizeof(receivedMessage));
    Serial.println(receivedMessage);
    Serial.println("Turning off the radio.");
    radio.stopListening();
    
    String stringMessage(receivedMessage);

    Serial.println(stringMessage);
  }
  delay(100) ;  
}
