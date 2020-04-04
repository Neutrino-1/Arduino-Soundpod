void about()
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
  
}

void volumeControl()
{
    
}
 
void topMenu()
{
    u8g2.setFont(u8g2_font_open_iconic_play_1x_t);
    u8g2.drawGlyph(u8g2.getDisplayWidth()-19,9,79);
    u8g2.drawGlyph(u8g2.getDisplayWidth()-30,9,67);
    u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);   
    u8g2.drawGlyph(u8g2.getDisplayWidth()-9,9,73);
}

void sideMenu()
{
    uint16_t menuList[4][2] = {{67,u8g2_font_open_iconic_mime_2x_t},{77,u8g2_font_open_iconic_play_2x_t},{72,u8g2_font_open_iconic_embedded_2x_t},{77,u8g2_font_open_iconic_embedded_2x_t}};
    int Menu_1 = 0;
    int Menu_2 = 1;
    int Menu_3 = 2;
    
    if(sMenuSelection > 3 || sMenuSelection < 0)
    {
      Menu_1 = (abs(sMenuSelection) % 4);
      Menu_2 = (abs(sMenuSelection+1) % 4);
      Menu_3 = (abs(sMenuSelection+2) % 4);
      Serial.println("Inside cyclic loop");
    }
    u8g2.setFontMode(0);
    
    //selection for file manager
    if(sMenuSelection <= 1)
    {
    u8g2.drawRBox(0,0,20,20,3);
    u8g2.setDrawColor(0);
    }
    //file manager
    drawIcon(menuList[Menu_1][1],2,17,menuList[Menu_1][0]);
    
    u8g2.setDrawColor(1);

    //Audio player selection
    if(sMenuSelection == 2)
    {
    u8g2.drawRBox(0,21,20,21,3);
    u8g2.setDrawColor(0);
    }

    //Audio player
    drawIcon(menuList[Menu_2][1],2,40,menuList[Menu_2][0]);
    
    u8g2.setDrawColor(1);

    //About Selection
    if(sMenuSelection >= 3)
    {
    u8g2.drawRBox(0,u8g2.getDisplayHeight()-20,20,19,3);
    u8g2.setDrawColor(0);
    }
    //About
    drawIcon(menuList[Menu_3][1],2,62,menuList[Menu_3][0]);
    
    u8g2.setDrawColor(1);
    u8g2.drawLine(22,0,22,u8g2.getDisplayHeight());   
}

void player()
{
    u8g2.setFont( u8g2_font_open_iconic_play_1x_t);
    u8g2.drawGlyph(u8g2.getDisplayWidth()/2-5,u8g2.getDisplayHeight()/2+4,73);
    u8g2.drawGlyph(u8g2.getDisplayWidth()/2+25,u8g2.getDisplayHeight()/2+4,74);
    u8g2.setFont(u8g2_font_open_iconic_play_2x_t);
    u8g2.drawGlyph(u8g2.getDisplayWidth()/2+7.5,u8g2.getDisplayHeight()/2+7.5,69);
    u8g2.drawRFrame(30,u8g2.getDisplayHeight()/2+12,u8g2.getDisplayWidth()-30,5,1);
    u8g2.drawRBox(30,u8g2.getDisplayHeight()/2+12,u8g2.getDisplayWidth()-60,5,1);
    u8g2.setFont(u8g2_font_mozart_nbp_tn);
    u8g2.drawStr(30,10,"12/455");
    u8g2.setFont(u8g2_font_IPAandRUSLCD_tf );
    u8g2.drawStr(30,u8g2.getDisplayHeight()/2+30,"first_Song.mp3");
    sideMenu();
    topMenu();
}

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph)
{
    u8g2.setFont(iconName);
    u8g2.drawGlyph(x,y,glyph);
}

void settings()
{
    drawIcon(u8g2_font_open_iconic_play_2x_t,30,u8g2.getDisplayHeight()/2-5,64);
    sideMenu();
    topMenu();
}

void fileList()
{
  
}
