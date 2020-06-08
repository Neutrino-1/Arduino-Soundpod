#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>

SoftwareSerial customSoftwareSerial(12,13);
DFRobotDFPlayerMini myDFPlayer;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const uint8_t leftButton = 2;
const uint8_t selectionButton = 5;
const uint8_t rightButton = 3;

volatile uint8_t sMenuSelection = 2;
volatile uint8_t selection = 1;
volatile bool updateScreen = true;

boolean playing = false;
boolean inSideMenuSelection = true;

// Variables
uint8_t filecounts;                     // total number of files in current folder
uint8_t foldercounts;                   // total number of folders on sd-card

uint8_t volume = 20;                    // current volume (0 .. 30)
uint8_t folder = 1;                     // current sd-card folder
uint8_t file   = 1;                     // curent file in current folder
uint8_t eq = 0;

uint8_t batteryLevel = 0;
float resistor_ratio_factor = 3.91;
uint8_t mins = 0;
unsigned long lastTimepassed = 0;

void setup(void) {
    //Initializing u8g2 library
    Serial.begin(9200);
  u8g2.begin();  
  u8g2.firstPage(); 
  do{
    flashPage();    
  }while(u8g2.nextPage());
  pinMode(leftButton,INPUT_PULLUP);
  pinMode(rightButton,INPUT_PULLUP);
  pinMode(selectionButton,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(leftButton),leftButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightButton),rightButtonISR, FALLING);
  
  //being hardware serial for debugging
  Serial.begin(9600);
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
  batteryReader();
//Selection button
  if(!digitalRead(selectionButton) && inSideMenuSelection)
  {
      inSideMenuSelection = false;
      updateScreen = true;
      delay(200);
  }
  else if(!digitalRead(selectionButton) && !inSideMenuSelection && sMenuSelection == 1)
  {
       if(selection == 1)
       {
        if(file > 1)
        {
         //previous audio
         myDFPlayer.previous();
         file--;
         if(!playing)
            playing = true;
         EEPROM.write(2, file);
        }
       }
       else if(selection == 2)
       {
         //pause / play
         if(playing)
         {
          myDFPlayer.pause();
         }
         else
         {
          myDFPlayer.start();
         }
         playing = !playing;
       }
       else if(selection == 3)
       {
          //next audio
          file++;
            myDFPlayer.next(); 
           if(!playing)
            playing = true;
            EEPROM.write(2, file);
       }
       else if(selection == 4)
       {
         //back to side menu
         selection = 1;
         inSideMenuSelection = true;
       }
       updateScreen = true;
       delay(200);
  }else if(!digitalRead(selectionButton) && !inSideMenuSelection && sMenuSelection == 2)
  {
     if(selection == 1)
     {
         selection = 2;
         myDFPlayer.volume(volume);
         EEPROM.write(0, volume);
     }
     else if(selection == 2)
     {
        selection = 4;
        myDFPlayer.EQ(eq);
        EEPROM.write(1, eq);
     }
     else if(selection == 4)
     {
         //back to side menu
         selection = 1;
         inSideMenuSelection = true;
     }
     updateScreen = true;
     delay(200);
  }

//Updating the dispaly
  if(updateScreen)
  {
    u8g2.firstPage();  
    do {
      int ch = (sMenuSelection);
      switch(ch){
          case 1:
            player();
            break;
          case 2:
            settings();
            break;
          default:
            Serial.println(F("Default Screen"));
        }
      updateScreen = false;
      }while ( u8g2.nextPage() );
  }

   // check player status
  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    int value = myDFPlayer.read();

    switch (type) {
      case DFPlayerPlayFinished:
        if (file < filecounts) {
          file++;
          myDFPlayer.playFolder(folder, file);
          EEPROM.write(2, file);
          updateScreen = true;
        }
        break;
      default:
        break;
    }
  } 
}
