
/*
Automatic Tea Timer by lluisgl7

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VDD pin to 5V
 * LCD LEDA pin to digital pin 9
 * LCD LEDB pin to ground
 * 10K contrast potentiometer:
   * ends to 5V and ground
   * wiper to LCD VO pin
 
 * selection button to digital pin 2 and ground
 * 10K selection potentiometer:
   * ends to 5V and ground
   * wiper to analog pin A0
 * servo motor:
   * power wire to 5V
   * ground wire to ground
   * signal wire to digital pin 7
 * buzzer to digital pin 8 and ground
*/

#include <LiquidCrystal.h>
#include <Servo.h>

//state identifiers:
#define MENU 0
#define INPROCESS 1
#define DONE 2

const String welcomeMessage = ("Welcome!");
const String doneMessage = ("Done!");

const int buttonPin = 2;
const int servoPin = 7;
const int buzzerPin = 8;
const int backlightPin = 9;
const int potPin = A0; // selection potentiometer
const int servoHighPosition = 150;
const int servoLowPosition = 70;
const int servoSpeedDelay = 20; // decrease this value to increase the servo speed

unsigned long steepingTime;
unsigned long startTime;
long timeLeft;

volatile int state;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
Servo servo;

//custom LCD characters:
byte leftArrow[8] = {0,0,4,12,28,12,4,0};
byte rightArrow[8] = {0,0,4,6,7,6,4,0};
byte clock[8] = {0,14,21,23,17,14,0,0};
byte sandTimer[8] = {31,17,10,4,10,31,31,0};
byte teaCup[8] = {10,5,0,31,25,9,15,0};

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(backlightPin, OUTPUT);
  
  attachInterrupt(0, buttonISR, CHANGE);
  servo.attach(servoPin);
    
  digitalWrite(backlightPin, HIGH);
  
  lcd.createChar(0, leftArrow);
  lcd.createChar(1, rightArrow);
  lcd.createChar(2, clock);
  lcd.createChar(3, sandTimer);
  lcd.createChar(4, teaCup);
  
  state = MENU;
  
  lcd.begin(16, 2);
  lcd.print(welcomeMessage);
}

void loop() {

  switch(state){
  
    case MENU:       moveServoTo(servoHighPosition);
                     lcd.clear();
                       
                     lcd.setCursor(11,1);
                     lcd.print("start");
                     
                     lcd.setCursor(8,1); 
                     lcd.write(byte(0));  //display selection arrows
                     lcd.write(byte(1));
                     
                     lcd.setCursor(1,0); 
                     lcd.write(byte(2));  //display clock symbol
                                                                        
                     while(state == MENU){
                                              
                       steepingTime = 30000 * map(analogRead(potPin),0,1023,1,20);
                       lcd.setCursor(3,0);
                       lcd.print(millisToTime(steepingTime));
                       delay(200);                                               
                     }
      break;
    
    case INPROCESS:  moveServoTo(servoLowPosition);
                     startTime = millis();
                     
                     lcd.clear();
                     
                     lcd.setCursor(12,1);
                     lcd.print("stop");
                     
                     lcd.setCursor(1,0); 
                     lcd.write(byte(3));  //display sand timer symbol              
          
                     while(state == INPROCESS){
                      
                       timeLeft = steepingTime - (millis() - startTime);
                       
                       if(timeLeft > 0){                    
                         
                         lcd.setCursor(3,0);
                         lcd.print(millisToTime(timeLeft));
                       }
                       else state = DONE;    
                       
                       delay(500);                    
                     }               
      break;
       
    case DONE:       lcd.clear();
                     lcd.setCursor(1,0);
                     lcd.print(doneMessage + " ");
                     
                     lcd.write(byte(4));  //display tea cup symbol
                                          
                     moveServoTo(servoHighPosition);
                                        
                     doneBeep();
                     
                     lcd.setCursor(12,1);
                     lcd.print("menu");
                     
                     while(state == DONE);                
      break; 
  }
}


void buttonISR(){
  
  static unsigned long lastInterruptTime = 0; //used to debounce button input
  unsigned long interruptTime = millis();
  
  if(interruptTime - lastInterruptTime > 500){ //long debounce time to allow long presses
       
    switch(state){
    
      case MENU:       state = INPROCESS;
                  
        break;
      
      case INPROCESS:  state = MENU;
                     
        break;
      
     case DONE:        state = MENU;
                  
        break;
    }
  }
  lastInterruptTime = interruptTime;
} 


void moveServoTo(int finalPosition){ //move the servo slowly to the desired position

  int currentPosition = servo.read();
  
  if(finalPosition > currentPosition){
  
    for(int i = currentPosition; i <= finalPosition; i++){
    
      servo.write(i);
      delay(servoSpeedDelay);
    }
  }
  else if(finalPosition < currentPosition){
  
    for(int i = currentPosition; i >= finalPosition; i--){
    
      servo.write(i);
      delay(servoSpeedDelay);
    }
  }
}  

String millisToTime(long milliseconds){

  unsigned long minutes = (milliseconds/1000) / 60;
  unsigned long seconds = (milliseconds/1000) % 60;
  
  String minutesString = String(minutes);
  String secondsString = String(seconds);
  
  if(minutes < 10) minutesString = "0" + minutesString;
  
  if(seconds < 10) secondsString = "0" + secondsString;
   
  return minutesString + ":" + secondsString; 
}

void doneBeep(){

  tone(buzzerPin, 4000, 700);
}


