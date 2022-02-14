#include <Adafruit_Keypad.h>
#include <Keypad.h>

//rows and cols for a 4x4 keypad
const byte ROWS = 4;
const byte COLS = 4;
char display_str[16] = "###############"; //String data

//initializing pins for LED and vibration
int vib_pin1=12;
int vib_pin2=13;
//keypad configuration (can be changed based on your specific keypad)
char charkeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'F', 'E', 'D'}
};

//pins to connect to the board
//this pin configuration worked for the keypads supplied at FYELIC,
//if your rows/cols are inverted, simply change the pin numbers accordingly
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {2, 3, 4, 5};

//create an instance of a Keypad using the above configuration
Keypad customKeypad = Keypad( makeKeymap(charkeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(vib_pin1,INPUT);
  pinMode(vib_pin2, INPUT);
}

int key_pos=0;
void loop() {
  //obtains the key from the keypay
  char customKey = customKeypad.getKey();
  //if there was a key pressed, print the key to the serial monitor
  if (customKey) {
    if(key_pos<14){
      //key writes to data
      display_str[key_pos]=customKey;
      key_pos++;
      Serial.write(display_str,16); //Write the serial data
      //check to see if password has been entered
      if(customKey=='E'){
        key_pos=0;
        for(int i=0;i<16;i++){
          display_str[i]='#';
        }
      }
    //edge case check to see if password has been entered
    }else if(customKey=='E'){
      display_str[key_pos]=customKey;
      key_pos=0;
      Serial.write(display_str,16); //Write the serial data
      for(int i=0;i<16;i++){
        display_str[i]='#';
      }
    }
  }
  //detects tampering via vibration and sends error code if vibrations detected
  if(digitalRead(vib_pin1)==1 or digitalRead(vib_pin2)==1){
    char error_code[16] = "TAMP3R D3T3CT3D"; //String data
    Serial.write(error_code,16); //Write error_code to the serial data
  }
}
