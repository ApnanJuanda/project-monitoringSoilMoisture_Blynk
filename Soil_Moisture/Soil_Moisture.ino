#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2,3);
 
int msensor = A1; // moisture sensor is connected with the analog pin A1 of the Arduino
int msvalue = 0; // moisture sensor value 
 
long int data; 
int relay1 = 13; // to control the solenoid value 
int relay2 = 12; // to control the motor or anything else
 
 
int sdata1 = 0; // Moisture sensor value
 
 
String cdata; // complete data
 
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
pinMode(msensor, INPUT);
pinMode(relay1, OUTPUT);  
pinMode(relay2, OUTPUT);
 
  }
 
 
void loop()
{if(nodemcu.available() == 0 )
{
     msvalue = analogRead(msensor);
  Serial.println(msvalue);  
  sdata1 = msvalue; 
 
   cdata = cdata + sdata1+","; 
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(1000); // 1000 milli seconds
   cdata = ""; 
}

/*if (msvalue>1020){
  digitalWrite(relay1, HIGH);
}else{
  digitalWrite(relay1, LOW);
}*/
 
if ( nodemcu.available() > 0 ) 
{
  data = nodemcu.parseInt();
  delay(100); 
  Serial.println(data); 
 
  if ( data == 11 )
  {
    digitalWrite(relay1, LOW); 
  }
 
    if ( data == 10 )
  {
    digitalWrite(relay1, HIGH); 
  }
 
  // relay2 
 
    if ( data == 12 )
  {
    digitalWrite(relay2, LOW); 
  }
 
    if ( data == 13 )
  {
    digitalWrite(relay2, HIGH); 
  }
}
 
 
 
}
