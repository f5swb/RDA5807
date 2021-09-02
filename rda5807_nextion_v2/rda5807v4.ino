// RDA5807 F5SWB@2021 / (f5swb@hotmail.com)
// RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti
// version 3.0f 24/08/21

#include <RDA5807.h>
#include <EEPROM.h>
#include "EasyNextionLibrary.h"  // Include EasyNextionLibrary
EasyNex myNex(Serial); // Create anint adresse = 14;

/*********************************************************
   RDS
 *********************************************************/
char *rdsMsg;
char *stationName;
String bufferStatioName = " ";
String bufferRdsMsg;
float frequence = 0;
float volume = 0;
int bar_value = 0;
char buffer[10] = {0};
float Rssi = 0;
float Stereo = 0;
float Rds = 0;
float RdsStatus = 0;
String STRrecu = " " ;




RDA5807 rx;

void freq_read() {
  frequence = EEPROM.get(14, frequence);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence en mémoire est = "); Serial.println(frequence / 100, 1);
}

void freq_write() {
  frequence = EEPROM.put(14, frequence);  // Ecrit la nouvelle frequqnce dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence mémorisée est = "); Serial.println(frequence / 100, 1);
}

void showFrequency() {
  frequence = rx.getRealFrequency();
  String freq = String(frequence / 100, 1);
  myNex.writeStr("VaFreq.txt", freq);
}


void setup() {

  myNex.begin(115200);
  freq_read();
  //trigger1(); // read freq save
  rx.setup(); // Stats the receiver with default valuses. Normal operation
  //rx.setMute(true);
  rx.setVolume(0);
  rx.setBass(true);
  rx.setMono(false); // Force stereo
  rx.setRDS(true);
  rx.setRdsFifo(true);
  rx.setFrequency(frequence);  // Tune on 95.5 MHz
  rx.setSeekThreshold(40);
  initNextion();
  delay(2000);
  info();
}

void initNextion() {
// int    RDA5807_adrs=0x10;       // I2C-Address RDA Chip for sequential  Access
// int    RDA5807_adrr=0x11;       // I2C-Address RDA Chip for random      Access
// int    RDA5807_adrt=0x60;       // I2C-Address RDA Chip for TEA5767like Access

  myNex.writeStr("VaRDAinit.txt", "init");
  delay(250);
  myNex.writeStr("VaRDAinit.txt", "init");

}


void info() {

  frequence = rx.getRealFrequency();
  String freq = String(frequence / 100, 1);
  myNex.writeStr("VaFreq.txt", freq);
  delay(250);
  bar_value = map(frequence, 8700, 10800, 1, 100);
  myNex.writeNum("VaBarre.val", bar_value);
  delay(250);
  String stereo = ("\%s", (rx.isStereo()) ? "STEREO" : "MONO" );
  myNex.writeStr("VaStereo.txt", stereo);
  delay(250);
  Rssi = rx.getRssi();
  myNex.writeNum("VaRssi.val", Rssi);
  delay(250);
  String rdsStatus = ("\%s", (rx.getRdsReady()) ? "ON" : "OFF");
  myNex.writeStr("VaRdsStatus.txt", rdsStatus);
  rx.setVolume(6);
}

void showRDSMsg()
{
  rdsMsg = rx.getRdsText2A();
  delay(250);
  myNex.writeStr("VaRdsText.txt", rdsMsg);  
}

void showRDSStation()
{
  char *pOld;
  char *pNew;
  pNew = rx.getRdsText0A();
  delay(250);
  if (pNew != "" && pOld != pNew)
  {
    myNex.writeStr("VaRdsStation.txt", pNew);   
    pOld = pNew;
  }
}

void cleanDatas()
{
  String rdsStatus = ("\%s", "OFF");
  myNex.writeStr("VaRdsStatus.txt", rdsStatus);
  int Rssi = 0;
  myNex.writeNum("VaRssi.val", Rssi);
  myNex.writeStr("VaRdsText.txt", "                                                                                             ");  
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
  trigger(18) / get Rssi : getressi = printh 23 02 54 12
*/

void trigger0() { //savefreq

  frequence = EEPROM.put(14, frequence);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence mémorisée est maintenant = "); Serial.println(frequence / 100.0, 1);
  delay(250);

}
void trigger1() { // readsave freq
  frequence = EEPROM.get(14, frequence);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "14"
  Serial.print("La fréquence qui est en mémoire est = "); Serial.println(frequence / 100.0, 1);
  delay(250);
}



void trigger2() { // save vol
  volume = EEPROM.put(15, volume);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "14"
  Serial.print("Le volume mémorisé est maintenant = "); Serial.println(volume);
  delay(250);

}

void trigger3() { // readsave vol
  volume = EEPROM.get(15, volume);  // Retourne la frequence contenue dans l'eeprom, à l’adresse "15"
  Serial.print("Le volume qui est en mémoire est = "); Serial.println(volume);
  delay(250);

}

void trigger4() { // volume plus
  //rx.volumeUp();
  //trigger2();

}

void trigger5() { // volume minus
  //rx.volumeDown();
  //trigger2();

}

void trigger6() { // volume mute
  rx.setVolume(0);
  delay(250);
}

void trigger7() { // volume unmute
  trigger3();
  rx.setVolume(volume);
  delay(250);
}


void trigger8() { // seek plus
  cleanDatas();
  if ( frequence > 10800) frequence = 8700 ;
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP, showFrequency);
  info();

}

void trigger9() { // seek minus
  cleanDatas();
  if ( frequence < 8700) frequence = 10800 ;
  rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showFrequency);
  info();

}

void trigger16() { // tune plus
  cleanDatas();
  if ( frequence > 10800) frequence = 8700;
  rx.setFrequencyUp();
  info();

}

void trigger17() { // tune minus
  cleanDatas();
  if ( frequence < 8700) frequence = 10800 ;
  rx.setFrequencyDown();  
  info();
}

void loop(void) {

  myNex.NextionListen();
  if (rx.hasRdsInfo() ) {
    showRDSStation();
    showRDSMsg();
  }
}
