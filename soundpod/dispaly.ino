void settings()
{
   sideMenu();
   topMenu();
   u8g2.setFont(u8g2_font_glasstown_nbp_tf);
   
   u8g2.setCursor(65,17);
   u8g2.print(F("Setting"));

   u8g2.setFontMode(0);
      
   u8g2.setCursor(47,40);
   u8g2.print(F("Volume"));
   if(selection == 1 && !inSideMenuSelection)
    {
    u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
    if(volume > 0)
    u8g2.drawGlyph(85,40,77);
    if(volume < 30)
    {
    if(volume < 10)
    u8g2.drawGlyph(100,40,78);
    else
    u8g2.drawGlyph(105,40,78);
    }
    }
   u8g2.setFont(u8g2_font_glasstown_nbp_tf);
   u8g2.setCursor(95,40);
   u8g2.print(volume);
   u8g2.setDrawColor(1);
   
   u8g2.setCursor(67,60);
   u8g2.print(F("EQ"));
   if(selection == 2 && !inSideMenuSelection)
    {
    u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
    if(eq > 0)
    u8g2.drawGlyph(85,60,77);
    if(eq < 5)
    u8g2.drawGlyph(100,60,78);
    }
   u8g2.setFont(u8g2_font_glasstown_nbp_tf);
   u8g2.setCursor(95,60);
   u8g2.print(eq);
   u8g2.setDrawColor(1);
   
    if(selection == 4 && !inSideMenuSelection)
    {
    u8g2.setDrawColor(0);
    }
   u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
   u8g2.drawGlyph(120,60,83);
   u8g2.setDrawColor(1);
}

void flashPage()
{
  drawIcon(u8g2_font_open_iconic_play_4x_t,u8g2.getDisplayWidth()/2-12,u8g2.getDisplayHeight()-22,64); 
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.setCursor(50,63);
  u8g2.print(F("Soundpod"));
//  u8g2.drawStr(50,u8g2.getDisplayHeight()-5,"Soundpod"); 
}

void topMenu()
{
    u8g2.setFont(u8g2_font_open_iconic_play_1x_t);
    
    if(volume > 20)
    u8g2.drawGlyph(119,9,79);
    
    if(volume <= 20)
    u8g2.drawGlyph(119,9,80);
    
    if(volume < 10)
    u8g2.drawGlyph(119,9,81);
//
//    u8g2.setFont(u8g2_font_glasstown_nbp_tf);
//    u8g2.setCursor(25,9);
//    u8g2.print(batteryLevel);
//    u8g2.setCursor(35,9);
//    u8g2.print("%");
}

void sideMenu()
{
   const uint8_t menuListGlpy[2] = {77,64};
   const uint8_t *menuList[2] = {u8g2_font_open_iconic_play_2x_t,u8g2_font_open_iconic_mime_2x_t};

    u8g2.setFontMode(0);

    //Audio player selection
    if(abs(sMenuSelection) == 1 && inSideMenuSelection)
    {
    u8g2.drawRBox(0,12,20,21,3);
    u8g2.setDrawColor(0);
    }

    //Audio player
    drawIcon(menuList[0],2,30,menuListGlpy[0]);
    
    u8g2.setDrawColor(1);

    //About Selection
    if(abs(sMenuSelection) == 2 && inSideMenuSelection)
    {
    u8g2.drawRBox(0,33,20,19,3);
    u8g2.setDrawColor(0);
    }
    //About
    drawIcon(menuList[1],2,52,menuListGlpy[1]);
//    u8g2.setFont(menuList[1][1]);
//    u8g2.drawGlyph(2,52,menuList[1][0]);
    
    u8g2.setDrawColor(1);
    u8g2.drawLine(22,0,22,68);   
}

void player()
{
  sideMenu();
  topMenu();
  
  u8g2_uint_t midOriginX = 64;
  u8g2_uint_t midOriginY = 44;

  u8g2.setFontMode(0);
  u8g2.setCursor(45,25);
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.print("Track : ");
  u8g2.setCursor(78,25);
  u8g2.print(file);
  u8g2.setCursor(88,25);
  u8g2.print('/');
  u8g2.setCursor(95,25);
  u8g2.print(filecounts);
  
  if(selection == 1 && !inSideMenuSelection)
    {
    u8g2.drawRBox(midOriginX-7,midOriginY-5,11,9,2);
    u8g2.setDrawColor(0);
    }    
    u8g2.setFont( u8g2_font_open_iconic_play_1x_t);
    u8g2.drawGlyph(midOriginX-5,midOriginY+4,73);
    u8g2.setDrawColor(1);

    if(selection == 2 && !inSideMenuSelection)
    {
    u8g2.drawRBox(midOriginX+7.5,midOriginY-8.5,16.5,15,3);
    u8g2.setDrawColor(0);
    }
    u8g2.setFont(u8g2_font_open_iconic_play_2x_t);
    if(playing)
    {
      u8g2.drawGlyph(midOriginX+7.5,midOriginY+7.5,68);
    }
    else
    {
     u8g2.drawGlyph(midOriginX+7.5,midOriginY+7.5,69);
    }
    u8g2.setDrawColor(1);

    if(selection == 3 && !inSideMenuSelection)
    {
    u8g2.drawRBox(midOriginX+25,midOriginY-5,12,9,2);
    u8g2.setDrawColor(0);
    }
    u8g2.setFont(u8g2_font_open_iconic_play_1x_t);
    u8g2.drawGlyph(midOriginX+27,midOriginY+4,74);
    u8g2.setDrawColor(1);

     if(selection == 4 && !inSideMenuSelection)
    {
    u8g2.setDrawColor(0);
    }
    u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
    u8g2.drawGlyph(120,60,80);
    u8g2.setDrawColor(1);
}

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph)
{
    u8g2.setFont(iconName);
    u8g2.drawGlyph(x,y,glyph);
}
