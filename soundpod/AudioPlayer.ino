// starts to play the actual file in the actual folder
void startFolderPlay() {
  filecounts = myDFPlayer.readFileCountsInFolder(folder);
  myDFPlayer.playFolder(folder, file);
  playing = false;
}

//Battery management

void batteryReader()
{
  if((millis() -  lastTimepassed) > 60000)
  {
  mins++;
  Serial.println("One min");
  lastTimepassed = millis();
  }

  if(mins > 5 || mins == 0)
  {
   /*Add battery logic here*/
  mins = 1;
  updateScreen = true;
  }
}
