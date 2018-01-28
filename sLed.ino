void controlled() {

  //  // What mode you chose? HARDWARE SELECT
  //  for (int select = lowestSelectorPin; select <= highestSelectorPin; select++) {
  //    if (digitalRead(select) == HIGH) {
  //      Selector = select;
  //      Serial.print("Auswahl ist: ");
  //      Serial.println(Selector);
  //    }
  //  }


  CheckBrightness();
  CheckSpeed();
  CheckNearSensor();


  // Fade one Up and Down, through all
  if (Selector == 26) {
    //int dtime = 80;

    // Switch through the Output Pin's
    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {

      // Fade On all Led
      for (int brightness = LedOff; brightness < LedOn; brightness++) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }

      //Fade Off the Led
      for (int brightness = LedOn; brightness > LedOff; brightness--) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }

      // Delay
      delay(dtime);
    }
  } // Selector End

  // Fade all together Up and Down
  if (Selector == 27) {
    //int dtime = 200;
    int brightness = LedOff;

    // Fade On all Led
    while (brightness < LedOn) {
      brightness++;

      // Switch through the Output Pin's
      for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
        analogWrite(thisPin, brightness);
      }
      // Delay
      delay(dtime);

    }

    // Fade Off all Led
    while (brightness > LedOff) {
      brightness--;

      // Switch through the Output Pin's
      for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
        analogWrite(thisPin, brightness);
      }
      // Delay
      delay(dtime);
    }
  } // Selector End

  // Fade on after another UP and after that Down
  if (Selector == 28) {
    //int dtime = 20;

    // Switch through the Output Pin's
    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {

      // Fade On all Led
      for (int brightness = LedOff; brightness < LedOn; brightness++) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }
    }

    // Switch through the Output Pin's
    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {

      //Fade Off the Led
      for (int brightness = LedOn; brightness > LedOff; brightness--) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }
    }
  } // Selector End

  // Random LED On and Off
  if (Selector == 29) {
    //int dtime = 5;
    int thisPin;
    long PinState;

    randNumber = random((highestLedPin - lowestLedPin) + 1);
    thisPin = randNumber + lowestLedPin;
    Serial.print("Zufälliger Port: ");
    Serial.println(thisPin);

    PinState = pulseIn(thisPin, LOW); // PWM einlesen
    Serial.print("Port Status: ");
    Serial.println(PinState);

    if (PinState == LedOff) {
      Serial.println("Fade Up");
      // Fade Led Up
      for (int brightness = LedOff; brightness < LedOn; brightness++) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }
    }

    else {
      Serial.println("Fade Down");
      //Fade Off the Led
      for (int brightness = LedOn; brightness > LedOff; brightness--) {
        analogWrite(thisPin, brightness);
        delay(dtime);
      }
    }

  } // Selector End

  // All LED On
  if (Selector == 30) {
    int thisPin;

    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
      analogWrite(thisPin, LedOn);
      delay(dtime);
    }
    Selector == 32;
  } // Selector End

  // All LED Off
  if (Selector == 31) {
    int thisPin;

    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
      analogWrite(thisPin, LedOff);
      delay(dtime);
    }
      Selector == 32;
  } // Selector End

  // Sensor = LED
  if (Selector == 33) {
    int thisPin;

    for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
      if(thisPin == NearSensor)
      {
        analogWrite(thisPin, LedOn);
      }
      else{
        analogWrite(thisPin, LedOff);
      }
    }
  } // Selector End
  
} // Main Loop End



void CheckBrightness()
{
  int temp;
  temp = analogRead(PinAnalogBrightness);
//  Serial.print("Helligkeit Analog: ");
//  Serial.println(temp);
  
  if(temp >= 200)
    temp = (1024-temp) / 8;
   else
    temp = 50;

    //LedOn = temp;
    
    if (temp > MaxBrightness)
      LedOn = MaxBrightness;
    else
      LedOn = temp;

    LedOn = LedOn * 2.56;

//    Serial.print("Led On: ");
//    Serial.println(LedOn); 
    
//    Serial.print("Helligkeit Prozent: ");
//    Serial.println(temp); 

  delay(200);
}

void CheckSpeed()
{
  int temp;
  temp = analogRead(PinAnalogSpeed);
//  Serial.print("Geschwindigkeit Analog: ");
//  Serial.println(temp);
  
  if(temp >= 200)
    temp = (1024-temp) / 8;
   else
    temp = 50;

   dtime = temp;
//    Serial.print("Geschwindigkeit Prozent: ");
//    Serial.println(temp); 
}

void CheckNearSensor()
{
  int temp;
  temp = analogRead(PinAnalogNearSensor);
//  Serial.print("Näherungssensor Analog: ");
//  Serial.println(temp);
  
  if(temp >= 200)
    temp = (1024-temp) / 80;
   else
    temp = 5;

   NearSensor = temp;
//    Serial.print("Näherungssensor Prozent: ");
//    Serial.println(temp); 
}
