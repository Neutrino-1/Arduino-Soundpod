void preivousButtonClicked()
{

  updateScreen = true;  
  if(inSideMenuSelection && sMenuSelection < 2)
  {
   sMenuSelection++;
  }
  else if(selection < 4 && sMenuSelection == 1)
  {
     selection++; 
  }
  else if(selection == 1 && volume < 30 &&sMenuSelection == 2 && !inSideMenuSelection)
  {
     volume++; 
  }
  else if(selection == 2 && eq < 5 && sMenuSelection == 2 && !inSideMenuSelection)
  {
     eq++; 
  }

}

void nextButtonClicked()
{
  updateScreen = true;  
  if(inSideMenuSelection && sMenuSelection > 1)
  {
   sMenuSelection--;  
  }
  else if(selection > 1 && sMenuSelection == 1)
  {
    selection--;  
  }
  else if(selection == 1 && volume > 0 &&sMenuSelection == 2)
  {
     volume--; 
  }
  else if(selection == 2 && eq > 0 && sMenuSelection == 2)
  {
     eq--; 
  }
}

void playButtonClicked()
{
  //Selection button
  if(inSideMenuSelection)
  {
      inSideMenuSelection = false;
      updateScreen = true;
      delay(100);
  }
  else if(!inSideMenuSelection && sMenuSelection == 1)
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
  }else if(!inSideMenuSelection && sMenuSelection == 2)
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

}