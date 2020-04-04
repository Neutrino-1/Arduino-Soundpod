#include "SoftwareSerial.h"
SoftwareSerial DFplayer(9,10);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define ACTIVATED LOW

int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
int buttomnVolume = 5;

boolean isPlaying = false;

void setup () {
pinMode(buttonPause, INPUT);
digitalWrite(buttonPause,HIGH);
pinMode(buttonNext, INPUT);
digitalWrite(buttonNext,HIGH);
playFirst();
isPlaying = true;
pinMode(buttonPrevious, INPUT);
digitalWrite(buttonPrevious,HIGH);
DFplayer.begin (9600);
delay(1000);
}



void loop () { 
 if (digitalRead(buttonPause) == ACTIVATED)
  {
    if(isPlaying)
    {
      pause();
      isPlaying = false;
    }else
    {
      isPlaying = true;
      play();
    }
  }
 if (digitalRead(buttonNext) == ACTIVATED)
  {
    if(isPlaying)
    {
      playNext();
    }
  }
   if (digitalRead(buttonPrevious) == ACTIVATED)
  {
    if(isPlaying)
    {
      playPrevious();
    }
  }


   if (digitalRead(buttonVolume) == ACTIVATED)
  {
    if(isPlaying)
    {
      currentVolume -= 5;
      if(currentVolume  <= 0)
      {
        currentVolume = 30;
      }
      setVolume(currentVolume);
    }
  }
  
}

void playFirst()
{
  df_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(30);
  delay(500);
  df_CMD(0x11,0,1); 
  delay(500);
}

void pause()
{
  df_CMD(0x0E,0,0);
  delay(500);
}

void play()
{
  df_CMD(0x0D,0,1); 
  delay(500);
}

void playNext()
{
  df_CMD(0x01,0,1);
  delay(500);
}

void playPrevious()
{
  df_CMD(0x02,0,1);
  delay(500);
}

void setVolume(int volume)
{
  df_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

void df_CMD(byte CMD, byte Par1, byte Par2)
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the cmd to the module one byte at a time
for (byte k=0; k<10; k++)
{
DFplayer.write( Command_line[k]);
}
}
