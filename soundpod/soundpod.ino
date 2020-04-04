#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int sMenuSelection = 4;

bool updateScreen = true;

void setup(void) {
  u8g2.begin();  
  Serial.begin(115200);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

}

void loop(void) {

if(!digitalRead(2))
{
  sMenuSelection++;
    if(sMenuSelection <= 0)
      sMenuSelection = 2; 
     updateScreen = true;
    delay(20);
}
if(!digitalRead(3))
{
  sMenuSelection--;
   if(sMenuSelection >= 4)
     sMenuSelection = 2; 
     updateScreen = true;
    delay(20);
}
  if(updateScreen)
  {
    u8g2.firstPage();  
    do {
      switch(abs(sMenuSelection)%4){
          case 1:
            player();
            break;
          case 2:
            player();
            break;
          case 3:
            about();
            break;
          case 4:
            settings();
            break;
          default:
            Serial.println("Default Screen");
        }
        Serial.println(sMenuSelection);
      updateScreen = false;
      }while ( u8g2.nextPage() );
  }

}
