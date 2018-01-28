void showmedisplay() {

  drawMenu();

  downButtonState = digitalRead(PinButtonDown);
  selectButtonState = digitalRead(PinButtonUp);
  upButtonState =   digitalRead(PinButtonSelect);

//  Serial.print(downButtonState);
//  Serial.print(selectButtonState);
//  Serial.println(upButtonState);
  
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

  // Menü Hoch und Runter steuern
  if (page <= HighestMenuPage)
  {
    if (up)
    {
      up = false;
      menuitem--;
      if (menuitem == 0)
      {
        menuitem = 3;
        page--;
        if (page == 0)
        {
          page = HighestMenuPage;
        }
      }
    }
    else if (down)
    {
      down = false;
      menuitem++;
      if (menuitem == 4)
      {
        menuitem = 1;
        page++;
        if (page > HighestMenuPage)
        {
          page = 1;
        }
      }
    }
  }

  // Page 11 (page 1 punkt 1)
  if (up && page == 11 ) {
    up = false;
    contrast--;
    setContrast();
  }
  if (down && page == 11 ) {
    down = false;
    contrast++;
    setContrast();
  }
  if (up && page == 61 ) {
    up = false;
    if (MaxBrightness > 1)
      MaxBrightness--;

  }
  if (down && page == 61 ) {
    down = false;
    if (MaxBrightness < 100)
      MaxBrightness++;

  }

  if (middle) {
    middle = false;

    if (page <= HighestMenuPage)
    {

      switch (page)
      {
        case 1:
          switch (menuitem)
          {
            case 1:
              page = 11;
              break;
            case 2:
              if (backlight)
              {
                backlight = false;
                turnBacklightOff();
              }
              else
              {
                backlight = true;
                turnBacklightOn();
              }
              break;
            case 3:
              resetDefaults();
              break;
          }
          break;
        case 2:
          switch (menuitem)
          {
            case 1:
              //page = 21;
              Selector = 26;
              break;
            case 2:
              //page = 22;
              Selector = 27;
              break;
            case 3:
              //page = 23;
              Selector = 28;
              break;
          }
          break;
        case 3:
          switch (menuitem)
          {
            case 1:
              //page = 31;
              Selector = 29;
              break;
            case 2:
              //page = 32;
              Selector = 30;
              break;
            case 3:
              //page = 33;
              Selector = 31;
              break;
          }
          break;
        case 4:
          switch (menuitem)
          {
            case 1:
              page = 41;
              break;
            case 2:
              page = 42;
              break;
            case 3:
              page = 43;
              break;
          }
          break;
        case 5:
          switch (menuitem)
          {
            case 1:
              //page = 31;
              Selector = 33;
              break;
            case 2:
              //page = 32;
              Selector = 32;
              break;
            case 3:
              //page = 33;
              Selector = 32;
              break;
          }
          break;
        case 6:
          switch (menuitem)
          {
            case 1:
              page = 61;

              break;
            case 2:
              //page = 62;

              break;
            case 3:
              //page = 63;

              break;
          }
          break;
      }
    }

    else if (page == 11) {
      page = 1;
    }
    else if (page == 12) {
      page = 1;
    }
    else if (page == 13) {
      page = 1;
    }
    else if (page == 21) {

      page = 2;
    }
    else if (page == 22) {
      page = 2;
    }
    else if (page == 23) {

      page = 2;
    }
    else if (page == 31) {

      page = 3;
    }
    else if (page == 32) {

      page = 3;
    }
    else if (page == 33) {
      page = 3;
    }
    else if (page == 41) {
      page = 4;
    }
    else if (page == 42) {
      page = 4;
    }
    else if (page == 43) {
      page = 4;
    }
    else if (page == 51) {
      page = 5;
    }
    else if (page == 52) {
      page = 5;
    }
    else if (page == 53) {
      page = 5;
    }
    else if (page == 61) {
      setMaxBrighntess();
      page = 6;
    }
    else if (page == 62) {
      page = 6;
    }
    else if (page == 63) {
      page = 6;
    }
  }

}

void checkIfDownButtonIsPressed()
{
  if (downButtonState != lastDownButtonState)
  {
    if (downButtonState == 0)
    {
      down = true;
    }
    delay(50);
  }
  lastDownButtonState = downButtonState;
}



void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState)
  {
    if (upButtonState == 0) {
      up = true;
    }
    delay(50);
  }
  lastUpButtonState = upButtonState;
}


void checkIfSelectButtonIsPressed()
{
  if (selectButtonState != lastSelectButtonState)
  {
    if (selectButtonState == 0) {
      middle = true;
    }
    delay(50);
  }
  lastSelectButtonState = selectButtonState;
}


void drawMenu()
{

  if (page == 1)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print(">Contrast");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print(">Light: ");

    if (backlight)
      display.print("ON");
    else
      display.print("OFF");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print(">Reset");

    display.display();
  }

  else if (page == 2)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU 2");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("26:OneUpAndDow");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("27:AllUpAndDow");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print("28:FlitzeKacke");

    display.display();
  }
  else if (page == 3)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU 3");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("29:RandomShit");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("30:All On");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print("31:All Off");

    display.display();
  }
  else if (page == 4)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU 4");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("-> Clock");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("is it hot");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print("dark?");

    display.display();
  }
  else if (page == 5)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU 5");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("-> Analog Poti");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("free space");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print("same");

    display.display();
  }
  else if (page == 6)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU 6");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("-> Maximum Hell");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("Many Led's");

    // Menu Item 3
    display.setCursor(0, 35);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 3)
      display.setTextColor(WHITE, BLACK);
    display.print("same");

    display.display();
  }
  else if (page == 11)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("CONTRAST");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(5, 15);
    display.print("Value");

    // Menu Item 2
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(contrast);

    display.display();
  }

  else if (page == 21)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("OneUpAndDo");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 1)
      display.setTextColor(WHITE, BLACK);
    display.print("Return with");

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);
    if (menuitem == 2)
      display.setTextColor(WHITE, BLACK);
    display.print("Select");

    display.display();

  }
  else if (page == 41)
  {

    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Clockwork");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(5, 15);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print(MyDateAndTime.Hour);
    display.print(":");
    display.print(MyDateAndTime.Minute);
    display.print(":");
    display.println(MyDateAndTime.Second);

    // Menu Item 2
    display.setCursor(0, 25);
    display.print(MyDateAndTime.Day);
    display.print(".");
    display.print(MyDateAndTime.Month);
    display.print(".");
    display.println(MyDateAndTime.Year);
    display.display();

  }

  else if (page == 42)
  {

    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("is it hot");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(5, 15);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    display.print(MyFloatTemperature);

    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);

    display.print("Celsius");

    display.display();

  }

  else if (page == 43)
  {

    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Lux");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(5, 15);

    // Menu Item 1
    display.setCursor(0, 15);
    display.setTextColor(BLACK, WHITE);
    if (valf < 0)
      display.print("> 65535");
    else
      display.print((int)valf, DEC);
    display.println(" lx");

    delay(100);
    // Menu Item 2
    display.setCursor(0, 25);
    display.setTextColor(BLACK, WHITE);

    display.display();

  }
  else if (page == 61)
  {
    // Head Line
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Max Helligk");
    display.drawFastHLine(0, 10, 83, BLACK);

    // Menu Item 1
    display.setCursor(5, 15);
    display.print("Value");

    // Menu Item 2
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(MaxBrightness);

    display.display();
  }
}


void resetDefaults()
{
  contrast = 50;
  setContrast();
  backlight = true;
  turnBacklightOn();
  MaxBrightness = 25;
  setMaxBrighntess();
}

void setContrast()
{
  display.setContrast(contrast);
  display.display();
  EEPROM.write(EeAdrContrast, contrast);
}

void turnBacklightOn()
{
  digitalWrite(PinBacklight, HIGH);
  EEPROM.write(EeAdrBacklight, 1);

  int temp;
  temp = EEPROM.read(EeAdrBacklight);
  Serial.println(temp);
}

void turnBacklightOff()
{
  digitalWrite(PinBacklight, LOW);
  EEPROM.write(EeAdrBacklight, 0);
}

void setMaxBrighntess()
{
   EEPROM.write(EeAdrMaxBrightness, MaxBrightness);
}


