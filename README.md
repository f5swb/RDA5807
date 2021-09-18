# RDA5807
RDA5807 fm chipset / arduino with a Nextion screen F5SWB@2021 / Version 1.16 (f5swb@hotmail.com)

NEXTION library from  https://github.com/Seithan/EasyNextionLibrary a light and simple library for the Nextion screen - By seithagta <br/>
RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti <br/>
Original Nextion HMI from https://github.com/PU4RLN/Arduino-FM-Radio-with-Nextion-Display with a TEA5767 Device Thanks to him

# 1- First step is what you need :
- the RDA5807M chip : https://www.aliexpress.com/item/4000694502415.html?spm=a2g0o.productlist.0.0.46ce2056Q6WnOW&algo_pvid=79b67fca-b240-497d-a16a-64bf4971c04d&algo_exp_id=79b67fca-b240-497d-a16a-64bf4971c04d-8&pdp_ext_f=%7B%22sku_id%22%3A%2210000006049664671%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/3d.png" width="150" height="150" title = "RDA5807M chip">

- the Nextion screen NX4832K035: https://www.aliexpress.com/item/1005003070416379.html?spm=a2g0o.productlist.0.0.27f163efVB6PZF&algo_pvid=04feb086-c9bf-4afa-b8c9-07704eea8086&algo_exp_id=04feb086-c9bf-4afa-b8c9-07704eea8086-4&pdp_ext_f=%7B%22sku_id%22%3A%2212000023784548675%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/NEXTION.png" width="250" height="150" title = "NEXTION screen">

Please don't ask me for another screen size, it takes a lot of time to program, you can download the hmi file if you want to change the size.
Have a look here if you don't know how to load the file into the nextion : https://www.youtube.com/watch?v=-EV5M9qNkUE

There are three files : <br/>
 RDA5807arduino.hmi = if you want to edit ; <br/>
 RDA5807arduino90.tft = a ready to load file to the nextion at 90°; <br/>
 RDA5807arduino270.tft =  a ready to load file to the nextion at 270°. <br/>

- the power amplifier PAM8403 mini 5V digital amplifier board: https://www.aliexpress.com/item/32681042149.html?spm=a2g0o.productlist.0.0.1e8d1271nbvlgH&algo_pvid=3b0ba04b-49a6-4d1c-b2aa-4a0ffdce129a&algo_exp_id=3b0ba04b-49a6-4d1c-b2aa-4a0ffdce129a-3&pdp_ext_f=%7B%22sku_id%22%3A%2260334573266%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/amp.png" width="200" height="200" title = "PAM8403 chip">

- and finally a arduino nano:  https://www.aliexpress.com/item/1005001333437432.html?spm=a2g0o.productlist.0.0.7c4f3473PFzYyZ&algo_pvid=e5a3d244-a2dd-4984-88da-f32683a0d0cd&aem_p4p_detail=202109180300471025981813601330000109028&algo_exp_id=e5a3d244-a2dd-4984-88da-f32683a0d0cd-6&pdp_ext_f=%7B%22sku_id%22%3A%2212000015727632652%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/61GU9zrBTOL._AC_SX522_.jpg" width="200" height="200" title = "ARDUINO NANO">

# 2- Prepare the RDA5807M chip :

<img src = "https://raw.githubusercontent.com/f5swb/RDA5807/main/Pictures/vs-elec-mini-module-de-radio-chip-fm-stereo-rda5.webp" title = "RDA5807 chip">
As we can see on the picture the chip is small so we have to solder it with component tabs like this : <br/> <br/>

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rda_solder.jpg" width="300" height="250" title = "RDA5807 solder">

# 3 - Here is the final schema :
<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/schema.png" title = "schema.png">
Do all the link according to the schema :)

# 4 - Load the ino sketch :

/* RDA5807 F5SWB@2021 / (f5swb@hotmail.com)
RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti
Nextion library from https://github.com/Seithan/EasyNextionLibrary a light and simple library for the Nextion screen - By seithagta
version 1.16 18/09/2021
*/

#include <Wire.h> // load the Wire library 
#include <RDA5807.h> // load the RDA5807 library
#include <EEPROM.h> // load the EPPROM libray
#include "EasyNextionLibrary.h"  // load the EasyNextion library
EasyNex myNex(Serial); // Create an object of EasyNex class with the name  "myNex"
// Set as parameter the Serial you are going to use

char *rdsMsg; // declare rdsmsg as characters
char *stationName; // declare station name as characters
String bufferStatioName = " "; // buffer station name as string
String bufferRdsMsg; // declare buffer rds message as string
float frequence = 0; // declare frequence as float
int volume = 0; // declare volume as integer
int bar_value = 0; // declare bar value as integer
char buffer[10] = {0}; // declare a buffer of 10 characters
float Rssi = 0; // declare rssi as float
float Stereo = 0; // declare stero as float
float Rds = 0; // declare rds as float
float RdsStatus = 0; // declare rds status as float
String STRrecu = " " ; // declare str recu as string
String MemNextion;



RDA5807 rx; // declare RDA5807 as rx value

void setup() {
  myNex.begin(115200); // we fix the bauds speed between the arduino and the nextion if no parameter was given in the begin(), the default baud rate of 9600 will be used
  Wire.begin(); //we scan the I2C bus to see if the RDA5807 chip is connected and find his 3 address
  Wire.beginTransmission (16); // address: 16 (0x10) I2C-Address RDA Chip for sequential  Access
  Wire.beginTransmission (17); // address: 17 (0x11) I2C-Address RDA Chip for random      Access
  Wire.beginTransmission (96); // address: 96 (0x60) I2C-Address RDA Chip for TEA5767like Access
  if (Wire.endTransmission () == 0)
  {
    myNex.writeStr("VaRDAinit.txt", "init"); // we send init to the nextion because 3 address were found
    delay(250);
    myNex.writeStr("VaRDAinit.txt", "init"); // bug if we send only on time this data is not received by the Nextion ?

  } else
  {
    myNex.writeStr("VaRDAinit.txt", "failed"); // the RDA5087 found address failed
  }
  trigger1(); // read the saved frequency inside the arduino eeprom
  delay(250); // wait 1/4 seconds
  if (frequence == 0) // if frequence is null
  {
    frequence = 102.50; // fix a frequency to start
  }
  //// start the RDA5807 and Nextion init ////
  rx.setup(); // stats the RDA5807 with default values. Normal operation
  rx.setSoftmute(true); // set the set softmute function to on we nedd later
  rx.setMute(true); // set to mute the RDA5807
  rx.setBass(true); // set bass on
  rx.setMono(false); // force stereo
  rx.setRDS(true); // set RDS on
  rx.setRdsFifo(true); // set RDS fifo
  rx.setFrequency(frequence);  // set frequency saved ******* TO DO : control with a new arduino !!!!!!!
  rx.setSeekThreshold(40);  // set the level for the seek function to 40 dBuV
  trigger3(); // read the saved volume into the arduino eeprom ******** TO DO : if no volume in memory choose volume !!!!!!!
  delay(1000); // wait 1 second before init the page 1 of the Nextion
  myNex.writeStr("page 1"); // going to page 1 of the Nextion
  myNex.writeStr("page page1"); // going to page 1 of the Nextion
  rx.setMute(false); // set the softmute to off
  rx.setVolume(volume); // set the RDA5807 volume
  info(); // read all the info to send to the nextion
  ///// end of the RDA5807 init and Nextion screen ////
}

void info() { // show info to the nextion
  frequence = rx.getRealFrequency(); // get the actual frequency in the RDA5807
  String freq = String(frequence / 100, 1); // string the result with 1 number after the decimal point
  myNex.writeStr("VaFreq.txt", freq); // send the format result to the Nextion
  delay(250); // wait 1/4 second before the next command
  showVol(); // read volume level to send it to the nextion
  bar_value = map(frequence, 8700, 10800, 1, 100); // get the frequence value to bar_value variable
  myNex.writeNum("VaBarre.val", bar_value); // send the bar_value to the Nextion
  delay(250); // wait 1/4 second before the next command
  String stereo = ("\%s", (rx.isStereo()) ? "STEREO" : "MONO" ); // get if it's a stereo or a mono station of the RDA5807
  myNex.writeStr("VaStereo.txt", stereo); // send the result to the Nextion
  delay(250); //wait 1/4 second before the next command
  Rssi = rx.getRssi(); // get the rssi level of the RDA5807
  myNex.writeNum("VaRssi.val", Rssi); // send the rssi level to the Nextion
  delay(500); // wait 1/2 second
  String rdsStatus = ("\%s", (rx.getRdsReady()) ? "ON" : "OFF"); // get if the rds function is on or off of the RDA5807
  myNex.writeStr("VaRdsStatus.txt", rdsStatus); // send the rds state to the Nextion
}

void showFrequency() { // show the frequency
  frequence = rx.getRealFrequency(); // get the frequency of the RDA5807
  String freq = String(frequence / 100, 1); // string the result with 1 number after the decimal point
  myNex.writeStr("VaFreq.txt", freq); // send the format result to the Nextion
}

void showRDSStation() // show the rds station
{
  char *pOld; // declare old char
  char *pNew; // declare new char
  pNew = rx.getRdsText0A(); // get the rdstext of the RDA5807
  delay(250);  // wait 1/4 second
  if (pNew != "" && pOld != pNew)
  {
    myNex.writeStr("VaRdsStation.txt", pNew);
    pOld = pNew;
  }
}

void showRDSMsg() { // show the rds message
  rdsMsg = rx.getRdsText2A(); // get the rds message of the RDA5807
  delay(250); // wait 1/4 second
  myNex.writeStr("VaRdsText.txt", rdsMsg); // send the rds message to the Nextion
}

void showVol() { // show the actual volume level
  volume = rx.getVolume(); // get the volume level of the RDA5807
  delay(250);  // wait 1/4 second
  myNex.writeNum("VaVolume.val", volume); // send the volume level to the Nextion
}

void cleanDatas() { // clean the datas
  String rdsStatus = ("\%s", "OFF"); // clean the rds status
  myNex.writeStr("VaRdsStatus.txt", rdsStatus); // send the rds status to the Nextion
  int Rssi = 0; // set the rssi level to zero
  myNex.writeNum("VaRssi.val", Rssi); // send the rssi value zero to the Nextion
  myNex.writeStr("VaRdsText.txt", ""); // clean and send the rds text to Nextion ******* TO DO : clear the rdsfifo how to ????
  //delay(250);
}

/* void trigger nextion button send command
  Numbers in HEX:
  0   00  -   16  10  -   32  20  -   48  30
  1   01  -   17  11  -   33  21  -   49  31
  2   02  -   18  12  -   34  22  -   50  32
  3   03  -   19  13  -   35  23  -   51  33
  4   04  -   20  14  -   36  24  -   52  34
  5   05  -   21  15  -   37  25  -   53  35
  6   06  -   22  16  -   38  26  -   54  36
  7   07  -   23  17  -   39  27  -   55  37
  8   08  -   24  18  -   40  28  -   56  38
  9   09  -   25  19  -   41  29  -   57  39
  10  0A  -   26  1A  -   42  2A  -   58  3A
  11  0B  -   27  1B  -   43  2B  -   59  3B
  12  0C  -   28  1C  -   44  2C  -   60  3C
  13  0D  -   29  1D  -   45  2D  -   61  3D
  14  0E  -   30  1E  -   46  2E  -   62  3E
  15  0F  -   31  1F  -   47  2F  -   63  3F
  trigger(0) / savefreq : writefreq = printh 23 00 54 00
  trigger(1) / readsavefreq : readfreq = printh 23 02 54 01
  trigger(2) / savevol = printh 23 02 54 02
  trigger(3) / readsavevolume : readvol = printh 23 02 54 03
  trigger(4) / volume + : volumeplus = printh 23 02 54 04
  trigger(5) / volume - : volumeminus = printh 23 02 54 05
  trigger(6) / muteon : mute = printh 23 02 54 06
  trigger(7) / unmute = unmute = printh 23 02 54 07
  trigger(8) / seek + : seekplus = printh 23 02 54 08
  trigger(9) / seek - : seekminus = printh 23 02 54 09
  trigger(16) / tune + : tuneplus = printh 23 02 54 10
  trigger(17) / tune - : tuneminus = printh 23 02 54 11
  trigger(18) / get Rssi : getrssi = printh 23 02 54 12
  trigger(19) / set new freq : setnewfreq = printh 23 02 54 13
*/

void trigger0() { //save the frequency
  frequence = EEPROM.put(14, frequence);  // save the frequency into the arduino eeprom, adress "14"
  delay(250); // wait 1/4 second
}
void trigger1() { // read the saved frequency
  frequence = EEPROM.get(14, frequence);  // get the saved frequency into the arduino eeprom, adress "14"
  delay(250); // wait 1/4 second
}

void trigger2() { // save the volume level
  volume = EEPROM.put(20, volume);  // save the volume level into the arduino eeprom, adress "20"
  delay(250); // wait 1/4 second
}

void trigger3() { // read the saved volume
  volume = EEPROM.get(20, volume);  // get the saved level volume into the arduino eeprom, adress "20"
  delay(250); // wait 1/4 second
}

void trigger4() { // volume up
  rx.setVolumeUp(); // up the level volume
  volume = rx.getVolume(); // send the get volume level to the RDA5807
  showVol(); // send the volume level to the Nextion
  trigger2(); // save the new volume level into the the arduino eeprom, adress "20"
}

void trigger5() { // volume down
  rx.setVolumeDown(); // down the level volume
  volume = rx.getVolume(); // send the get volume level to the RDA5807
  showVol(); //  send the volume level to the Nextion
  trigger2(); // save the new volume level into the the arduino eeprom, adress "20"
}

void trigger6() { // mute the volume
  rx.setVolume(0);
}

void trigger7() { // unmute the volume
  rx.setVolume(volume); //set the volume to the volume value
  myNex.writeNum("VaVolume.val", volume); // send the volume level to the Nextion
}

void trigger8() { // seek up
  cleanDatas(); // clean all datas of the Nextion
  if ( frequence > 10800) frequence = 8700 ; // if frequency is more than 10800 go to 8700
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP, showFrequency); // send the seek up tune command to the RDA5807
  info(); // send the new datas infos to the Nextion
}

void trigger9() { // seek down
  cleanDatas(); // clean all datas of the Nextion
  if ( frequence < 8700) frequence = 10800 ; // if frequency is less than 870 go to 10800
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showFrequency); // send the seek down tune command to the RDA5807
  info(); // send the new datas infos to the Nextion
}

void trigger16() { // tune up
  cleanDatas(); // clean all datas of the Nextion
  if ( frequence > 10800) frequence = 8700; // if frequency is more than 10800 go to 8700
  rx.setFrequencyUp(); // send the up frequency tune command to the RDA5807
  info(); // send the new datas infos to the Nextion
}

void trigger17() { // tune down
  cleanDatas(); // clean all datas of the Nextion
  if ( frequence < 8700) frequence = 10800 ; // if frequency is more than 10800 go to 8700
  rx.setFrequencyDown(); // send the up frquency tune command to the RDA5807
  info(); // send the new datas infos to the Nextion
}

void trigger18() { // get the rssi level
  Rssi = rx.getRssi(); // send the rssi command to the RDA5807
  myNex.writeNum("VaRssi.val", Rssi); // send the rssi level to the Nextion
}

void trigger19() { // set the RDA5807 to a new memory frequency
  MemNextion = myNex.readStr("MemNextion.txt"); // get the memnextion.txt value
  delay(250); // waut 1/4 seconds
  float freq = MemNextion.toFloat(); // transform memnetxion string to float valuye
  int a = freq; // declare a as freq integer
  float b = 100; // declare b as 100
  int MemFreq = freq * 100; // multiply freq by 100
  rx.setFrequency(MemFreq);  // send the new frequency
  delay(250); // wait 1/4 seconds
  myNex.writeStr("page page1"); // going to page 1 of the Nextion
  info(); // send the new frequency to the Nextion
}

void loop(void) {

  myNex.NextionListen(); // // This function must be called repeatedly to response touch events from Nextion touch panel. Actually, you should place it in your loop function.
  if (rx.hasRdsInfo() ) { // if the RDA5807 get rds info :
    showRDSStation(); // - send the rds station to the Nextion
    showRDSMsg(); // - send the rds message to the Nextion
  }
}
