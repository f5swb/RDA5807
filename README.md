# RDA5807
RDA5807 fm chipset / arduino with a Nextion screen F5SWB@2021 / Version 1.16 (f5swb@hotmail.com)

NEXTION library from  https://github.com/Seithan/EasyNextionLibrary a light and simple library for the Nextion screen - By seithagta. <br/>
RDA5807 library from https://pu2clr.github.io/RDA5807/ Arduino Library for RDA5807 Devices - By Ricardo Lima Caratti. <br/>
Original Nextion HMI from https://github.com/PU4RLN/Arduino-FM-Radio-with-Nextion-Display with a TEA5767 Device Thanks to him.

### 1- The first step is what you need :
- the RDA5807M chip : https://www.aliexpress.com/item/4000694502415.html?spm=a2g0o.productlist.0.0.46ce2056Q6WnOW&algo_pvid=79b67fca-b240-497d-a16a-64bf4971c04d&algo_exp_id=79b67fca-b240-497d-a16a-64bf4971c04d-8&pdp_ext_f=%7B%22sku_id%22%3A%2210000006049664671%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/3d.png" width="150" height="150" title = "RDA5807M chip">

- the Nextion screen NX4832K035: https://www.aliexpress.com/item/1005003070416379.html?spm=a2g0o.productlist.0.0.27f163efVB6PZF&algo_pvid=04feb086-c9bf-4afa-b8c9-07704eea8086&algo_exp_id=04feb086-c9bf-4afa-b8c9-07704eea8086-4&pdp_ext_f=%7B%22sku_id%22%3A%2212000023784548675%22%7D

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/NEXTION.png" width="250" height="150" title = "NEXTION screen">

To get the Real Time Control and the backup saved functions (screen saver, memory bank etc ... you need also to put into the Nextion screen a Battery type CR1220 :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rtc_battery.jpg" width="800" height="600" title = "battery">

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

### 2- Prepare the RDA5807M chip :

<img src = "https://raw.githubusercontent.com/f5swb/RDA5807/main/Pictures/vs-elec-mini-module-de-radio-chip-fm-stereo-rda5.webp" title = "RDA5807 chip">
As we can see on the picture the chip is small so we have to solder it with component tabs like this : <br/> <br/>

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/rda_solder.jpg" width="300" height="250" title = "RDA5807 solder">

### 3 - Here is the final schema :
<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/schema.png" title = "schema.png">
Do all the link according to the schema :)

### 4 - Load the ino sketch into the arduino nano :

### 5 - Load the tft file into the nextion screen :


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
 
 <img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/boot2.PNG" title = "boot1.png">
 
 another way, have a look at your build there's a problem ....


### 7 - First page of the system : 
  
  <img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page1.PNG" title = "page1.png">

   
###### Explanation:

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/Page_1_explaination.png" title = "page1.png">

Good to know: to get a good RDS information, the signal should be upper than 50 dBuV, a lower value give invalid RDS datas or nothing ....

### 8 - Normal operation stand alone:

After 10 seconds if you don't touch anything, the screen page is going to change to a different point of view :

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page2.PNG" title = "page1.png">

###### Explanation:

The RDS station will be updated and the information text in live mode.  

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/Page_2_explaination!.png" title = "page1.png">

Good to know: if you want to get back to the first page, just touch the FM clipart, it's also the same operation from page 1 to go to this page !

### 9 - SEEK and TUNE operation:

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/page1.PNG" title = "page1.png">

If SEEK button is blue you are in SEEK MODE operation, so if you touch the >> you are going to seek up and << will seek down. 


<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/tune.PNG" title = "page1.png">


Touch TUNE button to go to the TUNE MODE operation, so if you touch the + you are going to seek up and - will seek down.

Good to know: if you see the MEMORY button in blue the frequency tuned is already in the memory bank (see MEMORY BANK).

### 10 - VOLUME operation:

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/volume.PNG" title = "page1.png">

Touch the VOLUME button to get the + and - function volume level.

**Good to know: you will see a level bar value instead of the frequency bar value, you can also control the level with the volume number at the right screen corner.**  

To mute the volume just touch to the MUTE button. 

<img src = "https://github.com/f5swb/RDA5807/blob/main/Pictures/mute.PNG" title = "page1.png">


### 11 - MEEMORY BANK operation :


