void updateDisplay() {
  //Updating the dispaly
  if (updateScreen) {
    u8g2.firstPage();
    do {
      int ch = (sMenuSelection);
      switch (ch) {
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
    } while (u8g2.nextPage());
  }
}

void settings() {
  sideMenu();
  topMenu();
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);

  u8g2.setCursor(65, 17);
  u8g2.print(F("Setting"));

  u8g2.setFontMode(0);

  u8g2.setCursor(47, 40);
  u8g2.print(F("Volume"));
  if (selection == 1 && !inSideMenuSelection) {
    u8g2.setFont(soundpod_icon_pack_font);
    if (volume > 0)
      u8g2.drawGlyph(85, 40, 69); // drawing left ajustment button next to the volume
    if (volume < 30) {
      if (volume < 10)
        u8g2.drawGlyph(100, 40, 70); // drawing right ajustment button next to the volume for single digit volume
      else
        u8g2.drawGlyph(105, 40, 70);  // drawing right ajustment button next to the volume for double digit volume
    }
  }
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.setCursor(95, 40);
  u8g2.print(volume);
  u8g2.setDrawColor(1);

  u8g2.setCursor(67, 60);
  u8g2.print(F("EQ"));
  if (selection == 2 && !inSideMenuSelection) {
    u8g2.setFont(soundpod_icon_pack_font);
    if (eq > 0)
      u8g2.drawGlyph(85, 60, 69); // drawing left ajustment button next to the volume
    if (eq < 5)
      u8g2.drawGlyph(100, 60, 70); // drawing right ajustment button next to the volume
  }
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.setCursor(95, 60);
  u8g2.print(eq);
  u8g2.setDrawColor(1);

  if (selection == 4 && !inSideMenuSelection) {
    u8g2.setDrawColor(0);
  }
  u8g2.setFont(soundpod_icon_pack_font);
  u8g2.drawGlyph(120, 60, 71); // drawing back button to the bottom off the screen
  u8g2.setDrawColor(1);
}

void flashPage() {
  drawIcon(soundpod_icon_pack_font, u8g2.getDisplayWidth() / 2 - 12, u8g2.getDisplayHeight() - 22, 66); //drawing spectrum for splash screen
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.setCursor(50, 63);
  u8g2.print(F("Soundpod"));
}

void topMenu() {
  u8g2.setFont(soundpod_icon_pack_font);

  if (volume >= 25)
    u8g2.drawGlyph(119, 9, 77);
  else if (volume > 10 && volume < 25)
    u8g2.drawGlyph(119, 9, 78);
  else if (volume <= 10)
    u8g2.drawGlyph(119, 9, 79);
  //
  //    u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  //    u8g2.setCursor(25,9);
  //    u8g2.print(batteryLevel);
  //    u8g2.setCursor(35,9);
  //    u8g2.print("%");
}

void sideMenu() {
  const uint8_t menuListGlpy[2] = { 77, 64 };

  u8g2.setFontMode(0);

  //Audio player selection
  if (abs(sMenuSelection) == 1 && inSideMenuSelection) {
    u8g2.drawRBox(0, 12, 20, 21, 3);
    u8g2.setDrawColor(0);
  }

  //Audio player
  drawIcon(soundpod_icon_pack_font, 2, 30, 76);

  u8g2.setDrawColor(1);

  //setting Selection
  if (abs(sMenuSelection) == 2 && inSideMenuSelection) {
    u8g2.drawRBox(0, 33, 20, 19, 3);
    u8g2.setDrawColor(0);
  }
  //settings
  drawIcon(soundpod_icon_pack_font, 2, 52, 65);
  //    u8g2.setFont(menuList[1][1]);
  //    u8g2.drawGlyph(2,52,menuList[1][0]);

  u8g2.setDrawColor(1);
  u8g2.drawLine(22, 0, 22, 68);
}

void player() {
  sideMenu();
  topMenu();

  u8g2_uint_t midOriginX = 64;
  u8g2_uint_t midOriginY = 44;

  u8g2.setFontMode(0);
  u8g2.setCursor(45, 25);
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  u8g2.print("Track : ");
  u8g2.setCursor(78, 25);
  u8g2.print(file);
  u8g2.setCursor(88, 25);
  u8g2.print('/');
  u8g2.setCursor(95, 25);
  u8g2.print(filecounts);

  if (selection == 1 && !inSideMenuSelection) {
    u8g2.drawRBox(midOriginX - 7, midOriginY - 5, 11, 9, 2);
    u8g2.setDrawColor(0);
  }
  u8g2.setFont(soundpod_icon_pack_font);
  u8g2.drawGlyph(midOriginX - 5, midOriginY + 4, 74);
  u8g2.setDrawColor(1);

  if (selection == 2 && !inSideMenuSelection) {
    u8g2.drawRBox(midOriginX + 7.5, midOriginY - 8.5, 16.5, 15, 3);
    u8g2.setDrawColor(0);
  }
  u8g2.setFont(soundpod_icon_pack_font);
  if (playing) {
    u8g2.drawGlyph(midOriginX + 7.5, midOriginY + 7.5, 72);
  } else {
    u8g2.drawGlyph(midOriginX + 7.5, midOriginY + 7.5, 73);
  }
  u8g2.setDrawColor(1);

  if (selection == 3 && !inSideMenuSelection) {
    u8g2.drawRBox(midOriginX + 25, midOriginY - 5, 12, 9, 2);
    u8g2.setDrawColor(0);
  }
  u8g2.setFont(soundpod_icon_pack_font);
  u8g2.drawGlyph(midOriginX + 27, midOriginY + 4, 75);
  u8g2.setDrawColor(1);

  if (selection == 4 && !inSideMenuSelection) {
    u8g2.setDrawColor(0);
  }
  u8g2.setFont(soundpod_icon_pack_font);
  u8g2.drawGlyph(120, 60, 71);
  u8g2.setDrawColor(1);
}

void drawIcon(const uint8_t* iconName, u8g2_uint_t x, u8g2_uint_t y, uint16_t glyph) {
  u8g2.setFont(iconName);
  u8g2.drawGlyph(x, y, glyph);
}
