void settings()
{
   u8g2.setFont(u8g2_font_ncenB14_tr);
   u8g2.drawStr(28,u8g2.getDisplayHeight()/2-5,"Soundpod");
   u8g2.setFont(u8g2_font_crox1cb_tf );
   u8g2.drawStr(55,u8g2.getDisplayHeight()/2+12,"0.1V");
   u8g2.setFont(u8g2_font_glasstown_nbp_tf);
   u8g2.drawStr(50,u8g2.getDisplayHeight()-5,"By Neutrino");
   sideMenu();
   topMenu();
}

void flashPage()
{
  drawIcon(u8g2_font_open_iconic_play_4x_t,u8g2.getDisplayWidth()/2-12,u8g2.getDisplayHeight()-22,64); 
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.drawStr(50,u8g2.getDisplayHeight()-5,"Soundpod"); 
}

void fileManager()
{
  
}
 
void topMenu()
{
    u8g2.setFont(u8g2_font_open_iconic_play_1x_t);
    u8g2.drawGlyph(u8g2.getDisplayWidth()-9,9,79);
}

void sideMenu()
{
    uint16_t menuList[3][2] = {{67,u8g2_font_open_iconic_mime_2x_t},{77,u8g2_font_open_iconic_play_2x_t},{72,u8g2_font_open_iconic_embedded_2x_t},};

    u8g2.setFontMode(0);
    
    //selection for file manager
    if(abs(sMenuSelection) == 1 && inSideMenuSelection)
    {
    u8g2.drawRBox(0,0,20,20,3);
    u8g2.setDrawColor(0);
    }
    //file manager
    drawIcon(menuList[0][1],2,17,menuList[0][0]);
    
    u8g2.setDrawColor(1);

    //Audio player selection
    if(abs(sMenuSelection) == 2 && inSideMenuSelection)
    {
    u8g2.drawRBox(0,21,20,21,3);
    u8g2.setDrawColor(0);
    }

    //Audio player
    drawIcon(menuList[1][1],2,40,menuList[1][0]);
    
    u8g2.setDrawColor(1);

    //About Selection
    if(abs(sMenuSelection) == 3 && inSideMenuSelection)
    {
    u8g2.drawRBox(0,u8g2.getDisplayHeight()-20,20,19,3);
    u8g2.setDrawColor(0);
    }
    //About
    drawIcon(menuList[2][1],2,62,menuList[2][0]);
    
    u8g2.setDrawColor(1);
    u8g2.drawLine(22,0,22,u8g2.getDisplayHeight());   
}

void player()
{
  u8g2_uint_t midOriginX = u8g2.getDisplayWidth()/2;
  u8g2_uint_t midOriginY = u8g2.getDisplayHeight()/2;

  u8g2.setFont(u8g2_font_mozart_nbp_tn);
  u8g2.drawStr(30,10,"12/455");
    
  u8g2.setFontMode(0);
 
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
    u8g2.drawRBox(2*midOriginX-17,2*midOriginY-10,11,8,2);
    u8g2.setDrawColor(0);
    }
    u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);
    u8g2.drawGlyph(2*midOriginX-15,2*midOriginY-1,79);
    u8g2.setDrawColor(1);
    
    u8g2.setFont(u8g2_font_IPAandRUSLCD_tf );
    u8g2.drawStr(30,midOriginY+20,"first_Song.mp3");

    
    sideMenu();
    topMenu();
}

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph)
{
    u8g2.setFont(iconName);
    u8g2.drawGlyph(x,y,glyph);
}

void fileList()
{
  sideMenu();
  topMenu();
}
