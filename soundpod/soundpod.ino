#include <Arduino.h>
#include <SoftwareSerial.h>
//Constants for sending data to DFplayer
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]


#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SoftwareSerial DFplayer(8,9);
  
const int leftButton = 2;
const int selectionButton = 4;
const int rightButton = 3;

volatile int sMenuSelection = 2;
volatile int selection = 1;
volatile bool updateScreen = true;

bool playing = false;
bool inSideMenuSelection = true;

void setup(void) {
  u8g2.begin();  
  Serial.begin(115200);
  pinMode(leftButton,INPUT_PULLUP);
  pinMode(rightButton,INPUT_PULLUP);
  pinMode(selectionButton,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftButton),leftButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightButton),rightButtonISR, FALLING);
  //Initializing DFPlayer
  DFplayer.begin (9600);
  playFirst();
//  u8g2.firstPage(); 
//  do{
//    flashPage();    
//  }while(u8g2.nextPage());
//  delay(2000);
}

void loop(void) {

//Selection button
  if(!digitalRead(selectionButton) && inSideMenuSelection)
  {
      inSideMenuSelection = false;
      updateScreen = true;
  }
  else if(!digitalRead(selectionButton) && !inSideMenuSelection)
  {
       if(selection == 1)
       {
         //previous audio
         playPrevious(); 
       }
       else if(selection == 2)
       {
         //pause / play
         if(playing)
         {
          pause();
         }
         else
         {
          play();
         }
         playing = !playing;
         updateScreen = true;
       }
       else if(selection == 3)
       {
          //next audio
           playNext();
       }
       else if(selection == 4)
       {
         //back to side menu
         inSideMenuSelection = true;
         updateScreen = true;
       }
  }

//Updating the dispaly
  if(updateScreen)
  {
    u8g2.firstPage();  
    do {
      int ch = (sMenuSelection);
      switch(ch){
          case 1:
            fileList();
            break;
          case 2:
            player();
            break;
          case 3:
            settings();
            break;
          default:
            Serial.println("Default Screen");
        }
        Serial.println(sMenuSelection);
      updateScreen = false;
      }while ( u8g2.nextPage() );
  }

////Getting info from DFpalyer
  if (DFplayer.available()) {
//    printDetail(DFplayer.readType(), DFplayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  Serial.println(DFplayer.read());
  }
}

//
//void printDetail(uint8_t type, int value){}
