// RDA5807 F5SWB@2021 / Version 1.4 (f5swb@hotmail.com)
// NEXTION library from https://github.com/itead/ITEADLIB_Arduino_Nextion
// RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti
// original Nextion sketch from https://github.com/PU4RLN/Arduino-FM-Radio-with-Nextion-Display with a TEA5767 Device Thanks to him
// and InterlinkKnight with https://www.youtube.com/watch?v=wIWxSLVAAQE 

#include <Wire.h>
#include <RDA5807.h>
#include "Nextion.h"


// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton buttonPlus = NexButton(1, 5, "buttonPlus");
NexButton buttonPlus1 = NexButton(1, 7, "buttonPlus1");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
NexButton buttonMinus = NexButton(1, 4, "buttonMinus");
NexButton buttonMinus1 = NexButton(1, 6, "buttonMinus1");


NexProgressBar j0 = NexProgressBar(1, 1, "j0");

NexPage page0 = NexPage(0, 0, "page0"); //initial message
NexPage page1 = NexPage(1, 0, "page1"); //radio
NexPage page2 = NexPage(2, 0, "page2"); //optional
//float number = 0;
float number = 1044;
float freq = 104.4;
float bar_value = 0;
char buffer[10] = {0};
float Rssi = 0;
float Stereo = 0;
float Rds = 0;
float RdsStatus = 0;
String STRrecu = " " ; 
// Register object texNumber, buttonPlus, buttonMinus, to the touch event list.

NexTouch *nex_listen_list[] =
{
  &buttonPlus,
  &buttonMinus,
  &buttonPlus1,
  &buttonMinus1,
  NULL
};

RDA5807 rx;

/*
   buttonPlus component pop callback function.
   In this example,the value of the "number" component will plus 1 any time when buttonPlus is pressed.
*/
void buttonPlusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlusPushCallback");
  
        if( number > 10800) number = 8700;
        rx.setFrequencyUp();
        rx.getRealFrequency();
        number = rx.getRealFrequency(); //number = number + 1;
        //  info();        
        updown();
 
  
}

void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");
        if( number < 8700) number = 10800 ;
        rx.setFrequencyDown();
        rx.getRealFrequency();
        number = rx.getRealFrequency(); //number = number + 1;
        //info();
        updown();
 
  
}
void buttonPlus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlus1PushCallback");
  
  if( number > 10800) number = 8700 ;
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP);
  delay(500);
  rx.getRealFrequency();
  delay(200);
  number = rx.getRealFrequency();
    info();
  
  
      
}


void buttonMinus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinus1PushCallback");

        //number = number -10 ;
        if( number < 8700) number = 10800 ;
        rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN);
        delay(500);
        rx.getRealFrequency();
        delay(200);
        number = rx.getRealFrequency(); //number = number + 1; 
        info();       
        
  
  
}




void setup() {
    nexInit();
    Serial.begin(9600);
    Serial.setTimeout(500);    
    Wire.begin();
    rx.setup(); // Stats the receiver with default valuses. Normal operation
    rx.setVolume(6);
    rx.setBass(true);
    rx.setMono(false); // Force stereo    
    rx.setRDS(true);
    rx.setRdsFifo(true);   
    delay(100);
    page1.show();
    rx.setFrequency(10140);  // Tune on 95.5 MHz
    rx.setSeekThreshold(40);       
    number = 10140;    
    info();    
    
          
    buttonPlus.attachPush(buttonPlusPushCallback);
    buttonPlus1.attachPush(buttonPlus1PushCallback);

    buttonMinus.attachPush(buttonMinusPushCallback);
    buttonMinus1.attachPush(buttonMinus1PushCallback);
  
 
}

void info() {
   
   Serial.print("frequence.txt=");
   Serial.print("\""); // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
   Serial.print(number/100,1);  // This is the value you want to send to that object and atribute mention before.
   Serial.print("\""); 
   Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
   Serial.write(0xff);
   Serial.write(0xff);
   bar_value = map(number, 8700, 10800, 1, 100);
   j0.setValue(bar_value);
   delay(500);
   Rssi = rx.getRssi();
   rx.getRssi();
   delay(500);
  Serial.print("Rssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char stereo[6];
  sprintf(stereo,"\%s",(rx.isStereo()) ? "Stereo" : "Mono" );
  delay(200);
  Serial.print("Stereo.txt=");
  Serial.print("\""); 
  Serial.print(stereo);
  Serial.print("\""); 
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(500);
  char RdsStatus[6];
  sprintf(RdsStatus,"\%s",(rx.getRdsReady()) ? "RDS" : "");
  delay(800);
  Serial.print("RdsStatus.txt=");
  Serial.print("\""); 
  Serial.print(RdsStatus);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);   
  
}

void updown() {   
   Serial.print("frequence.txt=");
   Serial.print("\""); // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
   Serial.print(number/100,1);  // This is the value you want to send to that object and atribute mention before.
   Serial.print("\""); 
   Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
   Serial.write(0xff);
   Serial.write(0xff);
   bar_value = map(number, 8700, 10800, 1, 100);
   j0.setValue(bar_value);  
   delay(1200);
   Serial.print("Rssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char stereo[6];
  sprintf(stereo,"\%s",(rx.isStereo()) ? "Stereo" : "Mono" );
  Serial.print("Stereo.txt=");
  Serial.print("\""); 
  Serial.print(stereo);
  Serial.print("\""); 
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);  
  Rssi = rx.getRssi();  
  rx.getRssi();
  Serial.print("Rssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char RdsStatus[6];
  sprintf(RdsStatus,"\%s",(rx.getRdsReady()) ? "RDS" : "");
  Serial.print("RdsStatus.txt=");
  Serial.print("\""); 
  Serial.print(RdsStatus);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);   
  
}


void loop(void) {
   nexLoop(nex_listen_list);
  
}


    
