void playFirst()
{
  //sending initializing parameters
  df_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(30);
  delay(500);
  //stopping the repeat play
  df_CMD(0x11,0,0); 
  delay(500);
  //pause
  df_CMD(0x0E,0,0);
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

void selectTrack(int number)
{
  //number indicated the file name of the audio files in SD card
  df_CMD(0x03,0,number);
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
