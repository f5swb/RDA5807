// RDA5807 F5SWB@2021 / Version 1.4 (f5swb@hotmail.com)
// NEXTION library from https://github.com/itead/ITEADLIB_Arduino_Nextion
// RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti
// original Nextion sketch from https://github.com/PU4RLN/Arduino-FM-Radio-with-Nextion-Display with a TEA5767 Device Thanks to him
// and InterlinkKnight with https://www.youtube.com/watch?v=wIWxSLVAAQE 
// version 2.0e 28/07

#include <Wire.h>
#include <RDA5807.h>
#include "Nextion.h"
#include <EEPROM.h>
int adresse = 14;


/*********************************************************
   RDS
 *********************************************************/
char *rdsMsg; 
char *stationName;
String bufferStatioName = " ";
String bufferRdsMsg;
//String pOld = " ";
// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton buttonPlus = NexButton(1, 5, "buttonPlus");
NexButton buttonPlus1 = NexButton(1, 7, "buttonPlus1");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
NexButton buttonMinus = NexButton(1, 4, "buttonMinus");
NexButton buttonMinus1 = NexButton(1, 6, "buttonMinus1");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
NexButton buttonRssi = NexButton(4, 10, "buttonRssi");

// Declare a button object [page id:1,component id:51, component name: "buttonWriteFrq"].
NexButton buttonWriteFrq = NexButton(1, 51, "buttonWriteFrq"); 

NexProgressBar j0 = NexProgressBar(1, 1, "j0");

NexPage page0 = NexPage(0, 0, "page0"); //initial message
NexPage page1 = NexPage(1, 0, "page1"); //radio
NexPage page2 = NexPage(2, 0, "page2"); //optional


float frequence = 0;
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
  &buttonRssi,
  &buttonWriteFrq,
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
        if( frequence > 10800) frequence = 8700;
        rx.setFrequencyUp();
        rx.getRealFrequency();
        frequence = rx.getRealFrequency();                
        updown();
        cleanDatas(); 
}

void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");
        if( frequence < 8700) frequence = 10800 ;
        rx.setFrequencyDown();
        rx.getRealFrequency();
        frequence = rx.getRealFrequency();        
        updown();
        cleanDatas();
}

void buttonPlus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlus1PushCallback"); 
  if( frequence > 10800) frequence = 8700 ;
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP);
  delay(500);
  rx.getRealFrequency();
  delay(200);
  frequence = rx.getRealFrequency();
   updown();
  cleanDatas();      
}


void buttonMinus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinus1PushCallback");        
        if( frequence < 8700) frequence = 10800 ;
        rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN);
        delay(500);
        rx.getRealFrequency();
        delay(200);
        frequence = rx.getRealFrequency(); 
         updown();
        cleanDatas();
}

void buttonRssiPushCallback(void *ptr)
{
  dbSerialPrintln("buttonRssiPushCallback");
  Rssi = rx.getRssi();  
  rx.getRssi();
  Serial.print("VaRssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);   
}

void buttonWriteFrqPushCallback(void *ptr)
{
  dbSerialPrintln("buttonWriteFrqPushCallback");
  frequence = EEPROM.put(adresse, frequence);  // Ecrit la nouvelle frequence dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence mémorisée est = "); Serial.println(frequence/100,1); 
}
  
void freq_read() {
  frequence = EEPROM.get(adresse, frequence);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence en mémoire est = "); Serial.println(frequence/100,1); 
}

void freq_write() {
  frequence = EEPROM.put(adresse, frequence);  // Ecrit la nouvelle frequqnce dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence mémorisée est = "); Serial.println(frequence/100,1); 
}


void setup() {  
    Serial.begin(9600);
    Serial.setTimeout(500);    
    Wire.begin();
    freq_read();   
    rx.setup(); // Stats the receiver with default valuses. Normal operation
    rx.setVolume(6);
    rx.setBass(true);
    rx.setMono(false); // Force stereo    
    rx.setRDS(true);
    rx.setRdsFifo(true);   
    delay(300);
    nexInit();
    page1.show();
    rx.setFrequency(frequence);  // Tune on 95.5 MHz
    rx.setSeekThreshold(40);        
    info(); 
          
    buttonPlus.attachPush(buttonPlusPushCallback);
    buttonPlus1.attachPush(buttonPlus1PushCallback);

    buttonMinus.attachPush(buttonMinusPushCallback);
    buttonMinus1.attachPush(buttonMinus1PushCallback);
  
    buttonRssi.attachPush(buttonRssiPushCallback);

    buttonWriteFrq.attachPush(buttonWriteFrqPushCallback);

}

void info() {   
   Serial.print("VaFreq.txt=");
   Serial.print("\""); // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
   Serial.print(frequence/100,1);  // This is the value you want to send to that object and atribute mention before.
   Serial.print("\""); 
   Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
   Serial.write(0xff);
   Serial.write(0xff);
   bar_value = map(frequence, 8700, 10800, 1, 100);
   j0.setValue(bar_value);
   delay(500);
   Rssi = rx.getRssi();
   rx.getRssi();
   delay(500);
  Serial.print("VaRssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char stereo[6];
  sprintf(stereo,"\%s",(rx.isStereo()) ? "STEREO" : "MONO" );
  delay(200);
  Serial.print("VaStereo.txt=");
  Serial.print("\""); 
  Serial.print(stereo);
  Serial.print("\""); 
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(500);
  char RdsStatus[6];
  sprintf(RdsStatus,"\%s",(rx.getRdsReady()) ? "ON" : "OFF");
  delay(800);
  Serial.print("VaRdsStatus.txt=");
  Serial.print("\""); 
  Serial.print(RdsStatus);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);   
  
}

void updown() {   
   Serial.print("VaFreq.txt=");
   Serial.print("\""); // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
   Serial.print(frequence/100,1);  // This is the value you want to send to that object and atribute mention before.
   Serial.print("\""); 
   Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
   Serial.write(0xff);
   Serial.write(0xff);
   bar_value = map(frequence, 8700, 10800, 1, 100);
   j0.setValue(bar_value);  
   delay(1200);
   Serial.print("VaRssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char stereo[6];
  sprintf(stereo,"\%s",(rx.isStereo()) ? "STEREO" : "MONO" );
  Serial.print("VaStereo.txt=");
  Serial.print("\""); 
  Serial.print(stereo);
  Serial.print("\""); 
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);  
  Rssi = rx.getRssi();  
  rx.getRssi();
  Serial.print("VaRssi.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\""); 
  Serial.print(Rssi);  // This is the value you want to send to that object and atribute mention before.
  Serial.print("\""); 
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
  char RdsStatus[6];
  sprintf(RdsStatus,"\%s",(rx.getRdsReady()) ? "ON" : "OFF");
  Serial.print("VaRdsStatus.txt=");
  Serial.print("\""); 
  Serial.print(RdsStatus);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);   
  
}

void showRDSMsg()
{
  rdsMsg = rx.getRdsText2A();
  delay(250);
  Serial.print("VaRdsText.txt=");  
  Serial.print("\""); 
  Serial.print(rdsMsg);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);    
}

void showRDSStation()
{
  char *pOld;
  char *pNew;
  pNew = rx.getRdsText0A();
  delay(500);
  if (pNew != "" && pOld != pNew)
  {
  Serial.print("VaRdsStation.txt=");
  Serial.print("\""); 
  Serial.print(pNew);
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  pOld = pNew;
  }  
} 

void cleanDatas()
{
  Serial.print("VaRdsStation.txt=");
  Serial.print("\""); 
  Serial.print("                ");
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.print("VaRdsText.txt=");
  Serial.print("\""); 
  Serial.print("                ");
  Serial.print("\"");   
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);   
}
  
void loop(void) {
   nexLoop(nex_listen_list);
 
 if (rx.hasRdsInfo() ) {
    showRDSStation();
    showRDSMsg();
    
}
}
