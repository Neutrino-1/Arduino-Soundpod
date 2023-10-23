#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include "OneButton.h"

// 65 - Audio Settings Icon
// 66 - Flash screen Spectrum 
// 67 - Battery empty 
// 68 - Battery full 
// 69 - left adjustment button
// 70 - right adjustment button
// 71 - back button 
// 72 - pause button
// 73 - play button
// 74 - previous button
// 75 - Next button
// 76 - Music Icon
// 77 - volume full
// 78 - volume half 
// 79 - volume low

extern const uint8_t soundpod_icon_pack_font[350] U8G2_FONT_SECTION("soundpod_icon_pack_font") = 
  "\17\0\4\4\5\6\3\3\7\34 \0\0\16\0\16\0\0\0\0\0\1AA&p\341\241\22\64\214\310" 
  "!BE\210\11\24\206\210 !D\4\11!\42H\10\21ABD\10\25\42TL\320 \0BZ\34" 
  "$\301\17\202<H\362 \311\203$\17\202\20y\20\204\310\203 D\36\4!\362 \10QH\210BB"
  "\24\22\42\204\210\42D\24!\242\10\21E\210(BD\21\42\212\20\321\220\20\205\204($D!!\12"
  "\11\221\7A\210<\10B\344A\20\42\17\222<H\362 \311\203$\10\0C\17\310`\221p\42T\210"
  "PS\205\70\1\0D\14\310`\221p\342\304\3\24'\0E\12\303x\221\22\2\205\220\0F\13\303p" 
  "\221\20D\4\212 \0G\16\250\240\221\21(\304\220\21fH\211\1H\12\214\261\241@\10\377G\4I"
  "\24\213\261\241\20t`\261CI\36<\10r\250\330\300\240\0J\14\307`\221 h\14\11k\10\5K" 
  "\15\307`\221\20\210\214\11\23d\6\11L\35\20\42\241yj\21G\304\4\11\24$P\220@A\242\12"
  "\11\62Q\210W$\314\222\5M\24\10!\221\23L\204\10\42&B\224\10QD\12A\201\0N\16\6"
  ")\221\23H\10\25\25\211\12\2\0O\13\4\61\221\23\344\301\20\61\1\0\0\0\4\377\377\0";

const uint8_t leftButtonPin = 2;
const uint8_t selectionButtonPin = 3;
const uint8_t rightButtonPin = 4;

volatile uint8_t sMenuSelection = 2;
volatile uint8_t selection = 1;
volatile bool updateScreen = true;

// Variables
uint8_t filecounts;                     // total number of files in current folder
uint8_t foldercounts;                   // total number of folders on sd-card

uint8_t volume = 20;                    // current volume (0 .. 30)
uint8_t folder = 1;                     // current sd-card folder
uint8_t file   = 1;                     // curent file in current folder
uint8_t eq = 0;

uint8_t batteryLevel = 0;
uint8_t mins = 0;
unsigned long lastBatteryRead = 0;

boolean playing = false;
boolean inSideMenuSelection = true;

OneButton PreviousBTN(leftButtonPin, true);
OneButton PlayBTN(selectionButtonPin, true);
OneButton NextBTN(rightButtonPin, true);

SoftwareSerial customSoftwareSerial(12,13);
DFRobotDFPlayerMini myDFPlayer;

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  
  //being hardware serial for debugging
  Serial.begin(9600);

 // Initializing u8g2 library
  u8g2.begin();  
  u8g2.firstPage(); 
  do{
    
    flashPage();    
  
  }while(u8g2.nextPage());
  
  PreviousBTN.attachClick(preivousButtonClicked);
  PlayBTN.attachClick(playButtonClicked);
  NextBTN.attachClick(nextButtonClicked);
  
  PreviousBTN.setDebounceMs(50);
  PlayBTN.setDebounceMs(50);
  NextBTN.setDebounceMs(50);

  //Initializing software serial
  customSoftwareSerial.begin(9600);

  if (!myDFPlayer.begin(customSoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Please insert the SD card!")); 
  }
  volume = EEPROM.read(0);
  if(volume > 30)
  volume = 30;
  
  eq     = EEPROM.read(1);
  if(eq > 5)
  eq = 5;
  
  file   = EEPROM.read(2);
  if(file >= 255)
  file = 1;
  
  delay(1000);
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  delay(500);
  foldercounts = myDFPlayer.readFolderCounts();
  startFolderPlay();
//  
}

void loop() {

  //Check constantly for button inputs
  PreviousBTN.tick();
  PlayBTN.tick();
  NextBTN.tick();
  //Update the display as required 
  updateDisplay();
  updateDFplayer();

}
