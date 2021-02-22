#define BLYNK_PRINT Serial
 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
 
int pinValue1;
int pinValue2;
int pinValue3;
int pinValue4;
 
 
char auth[] = "DhzZu6iMci2sEX6fKJM7xYQCld2y70PR";
const int sensorPin = 4; 
int sensorState = 0;
int lastState = 0;
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ASUS_X00TD";
char pass[] = "apnanjoo";
 
SimpleTimer timer;
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
//for soild moisture
int firstVal ; 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  
}
 
 
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  
 
  Blynk.begin(auth, ssid, pass);
  pinMode(sensorPin, INPUT);
 
    timer.setInterval(1000L,sensorvalue1); 
 
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
      Blynk.run();
      /*sensorState = digitalRead(sensorPin);
      Serial.println(sensorState);

      if (sensorState == 1 && lastState == 0) {
      Serial.println("needs water, send notification"); //KONDISI NGIRIM NOTIFIKASI WAER YOUR PLANTTTSSSSS
      Blynk.notify("Water your plants");
      lastState = 1;
      delay(1000);  
  } 
  
  else if (sensorState == 1 && lastState == 1) 
  {
  //TANAH MASIH LEMBAB
  Serial.println("has not been watered yet");
  delay(1000);
  }
  
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }
  delay(100);*/
  timer.run(); // Initiates BlynkTimer
   }
   
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
// new code
String l = getValue(myString, ',', 0);
 
 
 
firstVal = l.toInt();
 
 
  myString = "";
// end new code
    }
  }
 
}
 
void sensorvalue1()
{
int sdata = firstVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, sdata);
 
}
 
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
 
// in Blynk app writes values to the Virtual Pin 10
BLYNK_WRITE(V10)
{
   pinValue1 = param.asInt(); // assigning incoming value from pin V10 to a variable
 
  Serial.print(pinValue1);
 
}
 
 
// in Blynk app writes values to the Virtual Pin 11
BLYNK_WRITE(V11)
{
   pinValue2 = param.asInt(); // assigning incoming value from pin V10 to a variable
 
  Serial.print(pinValue2);
 
}
