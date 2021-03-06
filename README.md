# RDA5807
RDA5807 fm chipset / arduino with a Nextion screen F5SWB@2021 / Version 1.18 (f5swb@hotmail.com) <br/>

French version : https://github-com.translate.goog/f5swb/RDA5807/blob/main/README.md?_x_tr_sl=en&_x_tr_tl=fr&_x_tr_hl=fr&_x_tr_pto=nui,elem

https://github.com/f5swb/RDA5807/blob/main/RDA5807M_datasheet_v1.pdf

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/f5swb.jpg" title = "f5swb">

Specifications : 
- detection of the RDA5807M chip I2C when the sketch ino start ; 
- the last frequency and the last volume level are saved into the arduino nano memory ;
- Screensaver function (saved into the Nextion memory) ;
- Brightness level function (saved into the Nextion memory) ;  
- SEEK function ;
- TUNE function ;
- VOLUME level function ;
- MUTE function ;
- DATE/TIME function (saved into the Nextion memory) ;
- RSSIFinder function ;
- RDS info station ;
- RDS info text from the station ;
- MEMORY BANK function ;
- Editable and save new MEMORY into the Nextion screen.  




NEXTION library from  https://github.com/Seithan/EasyNextionLibrary a light and simple library for the Nextion screen - By seithagta. <br/>
RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti. <br/>
Original Nextion HMI from https://github.com/PU4RLN/Arduino-FM-Radio-with-Nextion-Display with a TEA5767 Device Thanks to him.

### 1- What you need :
- the RDA5807M chip : https://www.aliexpress.com/item/4000694502415.html?spm=a2g0o.productlist.0.0.46ce2056Q6WnOW&algo_pvid=79b67fca-b240-497d-a16a-64bf4971c04d&algo_exp_id=79b67fca-b240-497d-a16a-64bf4971c04d-8&pdp_ext_f=%7B%22sku_id%22%3A%2210000006049664671%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/3d.png" width="150" height="150" title = "RDA5807M chip">

- the Nextion screen NX4832K035: https://www.aliexpress.com/item/1005003070416379.html?spm=a2g0o.productlist.0.0.27f163efVB6PZF&algo_pvid=04feb086-c9bf-4afa-b8c9-07704eea8086&algo_exp_id=04feb086-c9bf-4afa-b8c9-07704eea8086-4&pdp_ext_f=%7B%22sku_id%22%3A%2212000023784548675%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/NEXTION.png" width="250" height="150" title = "NEXTION screen">

To get the Real Time Control and the backup saved functions (screen saver, memory bank etc ...) you need also to put into the Nextion screen a Battery type CR1220 :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rtc_battery.jpg" width="800" height="600" title = "battery">

- the power amplifier PAM8403 mini 5V digital amplifier board: https://www.aliexpress.com/item/32681042149.html?spm=a2g0o.productlist.0.0.1e8d1271nbvlgH&algo_pvid=3b0ba04b-49a6-4d1c-b2aa-4a0ffdce129a&algo_exp_id=3b0ba04b-49a6-4d1c-b2aa-4a0ffdce129a-3&pdp_ext_f=%7B%22sku_id%22%3A%2260334573266%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/amp.png" width="400" height="400" title = "PAM8403 chip">

- two speaker 8 ohms 2 Watt : https://www.aliexpress.com/item/32951065463.html?spm=a2g0o.detail.1000014.35.62902166QYU9cM&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.183346.0&scm_id=1007.13338.183346.0&scm-url=1007.13338.183346.0&pvid=a5be1632-f57b-4fe1-b55b-c6c0257736d0&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.13338.183346.0,pvid:a5be1632-f57b-4fe1-b55b-c6c0257736d0,tpp_buckets:668%232846%238116%232002&&pdp_ext_f=%7B%22sceneId%22:%2223416%22,%22sku_id%22:%2266331553735%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/hp.PNG" title = "PAM8403 chip">


- one external antenna for the FM Band : https://www.aliexpress.com/item/32880451863.html?src=google&src=google&albch=shopping&acnt=248-630-5778&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&isSmbAutoCall=false&needSmbHouyi=false&albcp=11388352280&albag=111501228717&trgt=800756788546&crea=fr32880451863&netw=u&device=c&albpg=800756788546&albpd=fr32880451863&gclid=Cj0KCQjwnJaKBhDgARIsAHmvz6ezDb2Oxu1_sZV6K7LjcXVc28Ax-3irOp9N9VVF2jsIV6QMiWSNgfsaAkHwEALw_wcB&gclsrc=aw.ds

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/antenna.PNG" title = "PAM8403 chip">


- and finally a arduino nano:  https://www.aliexpress.com/item/1005001333437432.html?spm=a2g0o.productlist.0.0.7c4f3473PFzYyZ&algo_pvid=e5a3d244-a2dd-4984-88da-f32683a0d0cd&aem_p4p_detail=202109180300471025981813601330000109028&algo_exp_id=e5a3d244-a2dd-4984-88da-f32683a0d0cd-6&pdp_ext_f=%7B%22sku_id%22%3A%2212000015727632652%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/61GU9zrBTOL._AC_SX522_.jpg" width="400" height="400" title = "ARDUINO NANO">

### 2- Prepare the RDA5807M chip :

<img src = "https://raw.githubusercontent.com/f5swb/RDA5807/main/Pictures/vs-elec-mini-module-de-radio-chip-fm-stereo-rda5.webp" title = "RDA5807 chip">
As we can see on the picture the chip is small so we have to solder it with component tabs like this : <br/> <br/>

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rda_solder.jpg" width="300" height="250" title = "RDA5807 solder">

### 3 - Here is the final schema :
<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/schema.png" title = "schema.png">
Do all the links according to the schema :)

### 4 - Load the ino sketch into the arduino nano : <br/>
https://github.com/f5swb/RDA5807/blob/main/arduino%20nano%20sketch%20v1.18/rda5807Nextionv1.18a.ino

### 5 - Load the tft file into the nextion screen :
Please don't ask me for another screen size, it takes a lot of time to program, you can download the hmi file if you want to change the size.  <br/>
Have a look here if you don't know how to load the file into the nextion : https://www.youtube.com/watch?v=-EV5M9qNkUE

There are three files : <br/>
 RDA5807arduino.hmi = if you want to edit ; <br/>
 https://github.com/f5swb/RDA5807/blob/main/nextion_files/rda5807Nextionv1.18.HMI <br/>
 RDA5807arduino90.tft = a ready to load file to the nextion at 90??;<br/>
 https://github.com/f5swb/RDA5807/blob/main/nextion_files/rda5807Nextionv1.18_90deg.tft <br/>
 RDA5807arduino270.tft =  a ready to load file to the nextion at 270??. <br/>
 https://github.com/f5swb/RDA5807/blob/main/nextion_files/rda5807Nextionv1.18_270deg.tft <br/>

### 6 - First start of the system :
<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/boot1.PNG" title = "boot1.png">

When you power on the arduino nano there is a scan of the I2C address to control if the RDA5807M is present at the begin of the void setup : <br/>

void setup() { <br/>
  myNex.begin(115200); // we fix the bauds speed between the arduino and the nextion at 115200 bauds <br/>
  Wire.begin(); //we scan the I2C bus to see if the RDA5807 chip is connected and find his 3 address <br/>
  Wire.beginTransmission (16); // address: 16 (0x10) I2C-Address RDA Chip for sequential  Access <br/>
  Wire.beginTransmission (17); // address: 17 (0x11) I2C-Address RDA Chip for random      Access <br/>
  Wire.beginTransmission (96); // address: 96 (0x60) I2C-Address RDA Chip for TEA5767like Access <br/>
  if (Wire.endTransmission () == 0) <br/>
  { <br/>
    myNex.writeStr("VaRDAinit.txt", "init"); // we send init to the nextion because 3 address were found <br/>
    delay(250); <br/>
    myNex.writeStr("VaRDAinit.txt", "init"); // bug if we send only on time this data is not received by the Nextion ?<br/> 
  } else <br/>
  { <br/>
    myNex.writeStr("VaRDAinit.txt", "failed"); // the RDA5087 found address failed <br/>
  } <br/>
   
 if you see this picture your RDA5807M is well detected : 
 
<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/boot.gif" title = "f5swb">

 another way, if you see this picture have a look at your assemblly there's a problem ....

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/no%20boot.gif" title = "f5swb">


### 7 - First page of the system : 
  
  <img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page1.PNG" title = "page1.png">

   
###### Explanation:

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/Page_1_explaination.png" title = "page1.png">

**Good to know: to get a good RDS information, the signal should be upper than 50 dBuV, a lower value give invalid RDS datas or nothing ....**

### 8 - Normal operation stand alone:

After 10 seconds if you don't touch anything, the screen page is going to change to a different view :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page2.PNG" title = "page1.png">

###### Explanation:

The RDS station will be updated and the information text in live mode.  

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/Page_2_explaination!.png" title = "page1.png">

**Good to know: if you want to get back to the first page, just touch the FM clipart, it's also the same operation from page 1 to go to this page !**

### 9 - SEEK and TUNE operation:

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page1.PNG" title = "page1.png">

If SEEK button is blue you are in SEEK MODE operation, so if you touch the >> you are going to seek up and << will seek down. 


<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/tune.PNG" title = "page1.png">


Touch TUNE button to go to the TUNE MODE operation, so if you touch the + you are going to tune up and - will tune down.

**Good to know: if you see the MEMORY button in blue the frequency tuned is already in the memory bank (see MEMORY BANK).**

### 10 - VOLUME operation :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/volume.PNG" title = "page1.png">

Touch the VOLUME button to get the + and - function volume level.

**Good to know : you will see a level bar value instead of the frequency bar value, you can also control the level with the volume number at the right screen corner.**  

To mute the volume just touch the MUTE button. 

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/mute.PNG" title = "page1.png">


### 11 - MEMORY BANK operation :

If you press on the MEMORY button this page will be open :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/memory%20bank.PNG" title = "page1.png">

Just press on the memory button to go to the new frequency, the screen will be back on the first page automaticaly.

**Good to know : with the MENU button, MEMORY BANK it will be possible to record new frequencies into the Nextion memory according to your country place.** 


### 12 - MENU operation :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/menu.PNG" title = "page1.png">

You can choose the DATE/TIME, SCREEN, MEMORY BANK or the RSSIFinder function.

1 - DATE/TIME : 

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/date.PNG" title = "page1.png">

On this page it's possible to control the date, the time (also the day saving time) and choose the PM/AM mode.<br/>

**Good to know : all the values will be recorded for the next power on of the screen if there is a battery in the Nextion screen.
https://raw.githubusercontent.com/f5swb/RDA5807/main/Pictures/rtc_battery.jpg**


2 - SCREEN : 

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/screen.PNG" title = "page1.png">

On this page it's possible to control the brightness of the screen and load a screen saver function.

**Good to know : all this settings will be saved into the Nextion memory and will be available with the next power on.<br/>
The screensaver is only active on the page 2, if you change of page it will be in standby mode it starts after +/- 2 minutes.**


3 - RSSIFinder :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rssi.PNG" title = "page1.png">

This page give you an extra opportunity to catch the RSSI level in live and rotate your antenna to get the more powerful signal.<br/>
Just touch the START button (the level is refreshed each second). <br/>

**Good to know : the frequency is from 88 Mhz to 108 Mhz. <br/>
If we choose the middle of the band and we calculate the antenna approximativaly : 
<br/>
Middle frequency is 108 - 88 = 20 so the middle frequency is 88 + 10 = 108 Mhz. <br/>
So now we calculate with the lambda formula : <br/>
Lambda = 300 / F(Mhz) <br/>
So Lambda is in our case : 300/108 = 2.77 meters.<br/>
Now we want a 1/4 vertical antenna so 2.77m / 4 = 0.69m.<br/>
So we need a vertical antenna of +/- 70cm to get the more power receive.** <br/>

4 - MEMORY BANK :

At the first start, all the MEMORY BANK are free, just select a memory bank to record a new frequency. <br/>

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/free%20memory.PNG" title = "memory ok.png">

After that, if you touch the MEMORY BANK button in the MENU, you will be invited to choose a memory channel to record the actual frequency of the RDA5807M, just select the memory bank where you want to record a new frequency. 

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/memory.PNG" title = "memory.png">

Then a new page will propose to you to save the new frequency into the memory bank you have choosen.<br/> 
The 97.2 Mhz frequency will be stored into the memory bank number 7 in this example.

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/mem%20ok.PNG" title = "memory ok.png">

You can cancel you choice or validate it if you press the green button.<br/> 
If you press the green button, a new page will tell you that the memory operation is ok.

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/memory7.PNG" title = "memory ok.png">

If you press on page 1, on the MEM button, we can see now that 97.2 Mhz is now recorded in the MEM 7 bank.<br/>   


<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/newmem7.PNG" title = "memory ok.png">

09/20/2021 To do status (not in the 1.18 version) :
- stop the RDS function when we start the RSSIFinder function ; 
- clear the RDSFIFO (RDS station and RDS informations) when we change the frequency ; 
- add a buzzer connected to the arduino when we touch the screen ;

To be continued ....

"if we conquer without peril, we triumph without glory"

