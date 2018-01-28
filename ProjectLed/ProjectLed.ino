#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <DS3231_Simple.h>    // RTC_ADDRESS =0x68;
#include <Wire.h>             // GY-30 = 0x23;
#include <EEPROM.h>

boolean backlight = true;
volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int EeAdrBacklight = 0;
int EeAdrContrast = 1;
int EeAdrNumberOfLed = 2;
int EeAdrMaxBrightness = 4;

int MaxLed = 5;
int MaxBrightness = 25;
int LedOff = 0 ;
int LedOn = 3;
int dtime = 20;
int NearSensor = 5;
int contrast = 50;
int menuitem = 1;
int page = 1;
int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int Selector = 32;  // Connect 22 to 26-30 for Mode Selecct
int HighestMenuPage = 6;
int BH1750_address = 0x23; // i2c Addresse

float valf=0;
float MyFloatTemperature;
long randNumber;


byte PinAnalogRandom = 0 ;
byte PinAnalogBrightness = 1;
byte PinAnalogSpeed = 2;
byte PinAnalogNearSensor = 3;
byte PinAnalogSensorLowest = A6;
byte PinAnalogSensorHighest = A15;
byte lowestLedPin = 2;
byte highestLedPin = 7;
byte PinInterruptUp = 18;
byte PinLcdDC  = 35;
byte PinLcdRST = 36;
byte PinLcdCS = 37; // Is on GND
byte PinButtonUp = 38;
byte PinButtonDown = 40;
byte PinButtonSelect = 42;
byte PinBacklight = 44;
//byte lowestSelectorPin = 26;
//byte highestSelectorPin = 32;


Adafruit_PCD8544 display = Adafruit_PCD8544(PinLcdDC, PinLcdCS, PinLcdRST); // 35,37,36
DS3231_Simple Clock;
DateTime MyDateAndTime;
// Software SPI (slower updates, more flexible pin options):
// pin  7 - Serial clock out (SCLK)
// pin  6 - Serial data out (DIN)
// pin 35 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS)      -> Masse
// pin 36 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(13, 12, 10, 8, 9);



void setup() {
  Serial.begin(9600);
  Serial.println("Setup Start");
  
  Serial.println("Setup EEPROM");
  int temp;

  temp = EEPROM.read(EeAdrBacklight);
//  if(0 != temp)
//    EEPROM.write(EeAdrBacklight, backlight);
//  else
   backlight = temp;

  temp = EEPROM.read(EeAdrContrast);
  if( 100 < temp || 1 > temp)
    EEPROM.write(EeAdrContrast, contrast);
  else
   contrast = temp;

  temp = EEPROM.read(EeAdrNumberOfLed);
  if( 8 < temp || 3 > temp)
    EEPROM.write(EeAdrNumberOfLed, MaxLed);
  else
   MaxLed = temp;

  temp = EEPROM.read(EeAdrMaxBrightness);
  if( 100 < temp)
    EEPROM.write(EeAdrMaxBrightness, MaxBrightness);
  else
   MaxBrightness = temp;
   
  Serial.print("Hintergrundbeleuchtung: ");
  Serial.println(EEPROM.read(EeAdrBacklight));
  Serial.print("Kontrast: ");
  Serial.println(EEPROM.read(EeAdrContrast));
  Serial.print("Anzahl der LED's: ");
  Serial.println(EEPROM.read(EeAdrNumberOfLed));
  Serial.print("Maximale Helligkeit: ");
  Serial.println(EEPROM.read(EeAdrMaxBrightness));

  

  Serial.println("Setup In- and Output");
  // Setup Led Pin's Output
  for (int thisPin = lowestLedPin; thisPin <= highestLedPin; thisPin++) {
    pinMode(thisPin, OUTPUT);
    analogWrite(thisPin, LedOff);
  }

//  // Setup Near Sensor Analog Pins
  Serial.println("Setup NearSensor Analog Input");
  for (int thisAnPin = PinAnalogSensorLowest; thisAnPin <= PinAnalogSensorHighest; thisAnPin++) {
    digitalWrite(thisAnPin, INPUT_PULLUP);
  }

    
  // Analog Pin 0, Please leave it open
  randomSeed(analogRead(PinAnalogRandom));

  pinMode(PinButtonDown, INPUT_PULLUP);
  pinMode(PinButtonUp, INPUT_PULLUP);
  pinMode(PinButtonSelect, INPUT_PULLUP);
  pinMode(PinBacklight, OUTPUT);
  pinMode(PinInterruptUp, INPUT_PULLUP);
  //pinMode(PinInterruptExit, INPUT_PULLUP);
  
  Serial.println("Setup Interrupt");  
  attachInterrupt(digitalPinToInterrupt(PinInterruptUp), AttachUp, FALLING);    
  digitalWrite(PinBacklight,backlight); //Turn Backlight ON

  Serial.println("Setup Display");
  display.begin();
  display.clearDisplay();   
  display.setContrast(contrast);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  display.println("LED");
  display.println("Flitze-");
  display.println("kacke");  
  display.display();        


  Serial.println("Setup Real Time Clock");
  Clock.begin();
  Clock.printDateTo_YMD(Serial);
  Serial.println();
  Clock.printTimeTo_HMS(Serial);
  Serial.println();
  // Create a variable to hold the data
  MyDateAndTime = Clock.read(); 
  MyFloatTemperature   = Clock.getTemperatureFloat();


  Serial.println("Setup Helligkeitssensor");
  Wire.begin();
  Wire.beginTransmission(BH1750_address);
  Wire.write(0x10); // 1 [lux] aufloesung
  Wire.endTransmission();


   
  Serial.println("Setup Ende");

  //If you not like to press a button
  //showmedisplay();
}

void loop() {
  showmedisplay();
  controlled();
  ClockUpdate();
//  TempReadSensor();
}

void AttachUp()
{
  Serial.println("Intterrupt Up wurde ausgelöst");
  showmedisplay();
  
}

void ClockUpdate()
{
  //detachInterrupt(digitalPinToInterrupt(PinInterruptUp));
  MyDateAndTime = Clock.read(); 
  MyFloatTemperature   = Clock.getTemperatureFloat();
  BH1750_Read();
  //attachInterrupt(digitalPinToInterrupt(PinInterruptUp), AttachUp, FALLING);  
}



void BH1750_Read()
{
  byte i=0;
  byte gy_buff[2];
  Wire.beginTransmission(BH1750_address);
  Wire.requestFrom(BH1750_address, 2);
  while(Wire.available()){
    gy_buff[i] = Wire.read(); 
    i++;
  }
  Wire.endTransmission(); 

    valf=((gy_buff[0]<<8)|gy_buff[1])/1.2;   
}


void TempReadSensor()
{
  int sensorValue = 0;
     
    for (int thisAnPin = PinAnalogSensorLowest; thisAnPin <= PinAnalogSensorHighest; thisAnPin++) {
      sensorValue = analogRead(thisAnPin);
      Serial.print("Sensor: ");
      Serial.print(thisAnPin); 
      Serial.print(" Wert: ");
      Serial.println(sensorValue);   
    }
    delay(1000);      
}


