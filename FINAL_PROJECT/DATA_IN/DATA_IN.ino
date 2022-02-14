#include <LiquidCrystal.h>  //LCD library
#include <Servo.h>
#include<string.h>

char read_in[16]="###############"; //Initialized variable to store recieved data
char password[17]="123456789E######";
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
int buzzer_pin= 6;
Servo servo1;
Servo servo2;
bool stop_servo=false;

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  lcd.begin(16, 2); //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear(); //clear the display
  lcd.setCursor(0,0);
  lcd.print("Password: ");//preliminary lcd display prints
  //sets up pin mode for vibration module
  pinMode(buzzer_pin,OUTPUT);
  //servo setup code
  servo1.attach(4);
  servo2.attach(5);
  servo1.write(90);
  servo2.write(0);
}

void loop() {
  lcd.setCursor(0,1); //set cursor to second row
  Serial.readBytes(read_in,16); //Read the serial data and store in var  
  //main password detector
  lcd.print(read_in);//prints read in data, aka password entered to screen
  if(read_in[0]=='T'){
    //tamper detection script
    tone(buzzer_pin,165,500);
  }
  //checks to see if data has been passed, if so checks to see if password entered
  if (read_in[0]!='#'){
    //servo move to constrain user until correct password
    if(!stop_servo){
      servo1.write(0);
      servo2.write(90);
      stop_servo=true;
    }
    //check data for if password entered and correct
    String comp_read= String(read_in);
    String comp_pass= String(password);
    if(comp_read.equals(comp_pass)){
      lcd.setCursor(0,1);
      lcd.print("PASSWORD CORRECT");
      servo1.write(90);
      servo2.write(0);
      delay(1000);
    }else{
      stop_servo=false;
    }
  }
}
