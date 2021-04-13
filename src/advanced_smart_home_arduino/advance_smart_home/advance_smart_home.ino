/**
 * Author: Minh Nguyen
 * 4/27/2020
 * Description: This is the combination for the whole system, including:
 *          AC LED Bluetooth (DONE)
 *          Intruder system (DONE)
 *          Automatically night light (DONE)
 *          Fire Detection unit (Done)
 *          Weather Station (Done)
 *          Clapping Sensor (Done)
 */
//___________________________________________________________________________________
/**
 * Initialization for AC Unit LED Control
 */
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial BT(12,1); //RX, TX respetively
String state;// string to store incoming message from bluetooth

/**
 * Just create the heart icon
 */
byte customChar[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

/**
 * Initialization for Intruder System
 */
//This is requirement for Motion sensor
int calibrationTime = 30;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000; 
 
boolean lockLow = true;
boolean takeLowTime; 
 
int pirPin = 26;    //the digital pin connected to the PIR sensor's output
int ledPin = 30; 
const int buzzerPin = 28;

/**
 * Initialization for Photoresistor automatic night light.
 */
const int ledPinRED = 48;
const int ledPinColor = 50;
const int prPin = A0; // Photoresistor Pin

/**
 * Initialization for Fire Detection
 */
#define FLAME 39 // Pin 2 for Flame sensor DO (Digital OUT)
#define ALARM 44 // pin 8 for Alarm LIGHT 
const int buzzer = 23; // pin 9 Digital for Buzzer 

/**
 * Initialization for Weather Station
 */
int sensorPin = A1; // Adjustment for what Analog Pin, currently A0
int tempC, tempF;

/**
 * Initialization for Water Sensor
 */
int resval = 0;  // holds the value
int respin = A3; // sensor pin used

/**
 * Initialization for Clap Sensor
 */
int soundSensor = 2;
int LED = 4;
boolean LEDStatus = false;

//_____________________________________________________________________________________
void setup() {
/** 
 *  Set up for AC Unit
 */
  BT.begin(9600);// bluetooth serial communication will happen on pin 10 and 11
  Serial.begin(9600); // serial communication to check the data on serial monitor
  pinMode(51, OUTPUT); // LED connected to 11th pin                
  lcd.begin(16,4); // Initialize the LCD with column and row
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello Boss!");
//_______________________________________________________________________________________
/**
 * Set up for Intruder Motion System
 */
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  pinMode(buzzerPin, OUTPUT);
/**
 * Set up for Automatic Night Light
 */
  pinMode(ledPinRED, OUTPUT);
  pinMode(ledPinColor, OUTPUT);
  pinMode(prPin, INPUT);

/**  
 * Set up for Flame Sensor
 */
  pinMode(FLAME, INPUT);//define FLAME input pin
  pinMode(ALARM, OUTPUT);//define ALARM output pin
  pinMode(buzzer, OUTPUT);

/**
 * Set up for Weather Station
 */
  lcd.setCursor(4,3);
  lcd.print("Temp: ");

/**
 * Create the Heart
 */
  lcd.createChar(1, customChar);
  lcd.home();
  lcd.setCursor(15,0);
  lcd.write(1);

/**
 * Set up for Water Sensor
 */
  lcd.setCursor(0,1);
  lcd.print("Pool Level:"); 

/**
 * Set Up for Clap Sensor
 */
  pinMode(soundSensor,INPUT);
  pinMode(LED,OUTPUT);
}

//_______________________________________________________________________________________

void loop() {

// Initialize string for parsing
String ret = "";

/** 
 *  Loop for Bluetooth Control
 */
  while (BT.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable 
    char c = BT.read(); //Conduct a serial read
    state += c; //build the string- either "On" or "off"    
  }  
  if (state.length() > 0) {
    if(state == "On") // Check 
    {
      digitalWrite(51, HIGH);
      lcd.setCursor(4,2); // column 0 row 0
      lcd.print("AC Unit is On!");
    } 
    else if(state == "Off") 
    {
      digitalWrite(51, LOW);
      lcd.setCursor(4,2); // column 0 row 0
      lcd.print("AC Unit is Off!");
    }
      state ="";
   }
   
/** 
 *  Loop for Weather Station
 */
  tempC = get_temperature(sensorPin);
  tempF = celsius_to_fahrenheit(tempC);
  
  lcd.setCursor(10,3);
  lcd.print(tempF); lcd.print((char)223); lcd.print("F");

  lcd.setCursor(15,3);
  lcd.print(tempC); lcd.print((char)223); lcd.print("C");

  ret += tempC;
  ret += "|";
  ret += tempF;
  ret += "|";
  delay(200);

/**    
 *  Loop for Intruder system    
 */
   if(digitalRead(pirPin) == HIGH){
     tone(buzzerPin, 100);
     digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
     if(lockLow){ 
       //makes sure we wait for a transition to LOW before any further output is made:
       lockLow = false;           
       ret += "Intruder detected at ";
       ret += millis()/1000;
       ret += " sec";
       delay(100);
     }        
     takeLowTime = true;
   }
 
   if(digitalRead(pirPin) == LOW){  
     noTone(buzzerPin);    
     digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
     if(takeLowTime){
     lowIn = millis();          //save the time of the transition from high to LOW
     takeLowTime = false;       //make sure this is only done at the start of a LOW phase
     }
   //if the sensor is low for more than the given pause,
   //we assume that no more motion is going to happen
     if(!lockLow && millis() - lowIn > pause){ 
       //makes sure this block of code is only executed again after
       //a new motion sequence has been detected
       lockLow = true;                       
       ret += "Intruder stopped at ";
       ret += (millis() - pause)/1000;
       ret += " sec";
       delay(100);
     }
   }
   Serial.println(ret);
  
/**
 * Clap Sensor Loop
 */
  int SensorData = digitalRead(soundSensor); 
  if(SensorData == 1){
    if(LEDStatus == false){
        LEDStatus = true;
        digitalWrite(LED,HIGH);
    }
    else{
        LEDStatus = false;
        digitalWrite(LED,LOW);
    }
  }

/**
 * Loop for Automatic Night Light
 */
  int prStatus = analogRead(prPin);

  // Check if the prStatur <= 300
  // If it is, LED is High
  if (prStatus >= 300){
    digitalWrite(ledPinRED, HIGH);
    digitalWrite(ledPinColor, HIGH);
  }
  else{
    digitalWrite(ledPinRED, LOW);
    digitalWrite(ledPinColor, LOW);
  }

/**
 * Loop for Flame Sensor
 */
  int fire = digitalRead(FLAME);// read FLAME sensor
  if(fire == HIGH)
  {
    digitalWrite(ALARM,HIGH);// set the buzzer ON
    tone(buzzer, 1000);
  }// Send 1KHz sound signal...
  else{
    digitalWrite(ALARM,LOW); // Set the buzzer OFF
    noTone(buzzer);     // Stop sound...
  }
  delay(200);

 /**
  * Loop for Water Sensor
  */
  lcd.setCursor(12, 1); 
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  if (resval<=200)
  { 
    lcd.println("Empty"); 
  } 
  else if (resval>200 && resval<=250)
  {
    lcd.println("Low"); 
  } 
  else if (resval>250 && resval<=275)
  { 
    lcd.println("Medium"); 
  } 
  else if (resval>275)
  { 
    lcd.println("High"); 
  }
  delay(1000); 
}

//Helper Method 1
  int get_temperature(int pin) {
// We need to tell the function which pin the sensor is hooked up to. We're using
// the variable pin for that above
// Read the value on that pin
  
  int temperature = analogRead(pin);
// Calculate the temperature based on the reading and send that value back
  
  float voltage = temperature * 5.0;
  voltage = voltage / 1024.0;
  return ((voltage - 0.5) * 100);
}

//Helper Method 2: Convert Celsius to Fareheign
  int celsius_to_fahrenheit(int temp) {
    return (temp * 9 / 5) + 32; 
} 
