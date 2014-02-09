#include <EEPROM.h>

// Pin attachments
int RGB_Red = 13;
int RGB_Blue = 10;
int RGB_Green = 9;
int on_sw = 4;
int up_sw = 12;
int down_sw = 6;
int supply_en = 8;
int bl_pwm_pin = 11;
int previous_on = LOW;
int previous_up = LOW;
int previous_down = LOW;
int bl_pwm = 0;

// Variables
int on, up, down, state;

void setup()  { 
  // Set all inputs/outptus
  pinMode(RGB_Red, OUTPUT);
  pinMode(RGB_Blue, OUTPUT);
  pinMode(RGB_Green, OUTPUT);
  pinMode(on_sw, INPUT);
  pinMode(up_sw, INPUT);
  pinMode(down_sw, INPUT);
  pinMode(supply_en, OUTPUT);
  pinMode(bl_pwm_pin, OUTPUT);
  
  //Turn on RGB_red to indicate standby
  analogWrite(RGB_Red, 1);
  digitalWrite(supply_en, 0);
  
  bl_pwm = EEPROM.read(0);
  
  Serial.begin(9600);


} 

void loop()  { 
  PORTB &= ~_BV(PORTB0); //Turn off Rx/Tx LEDs as wired as wrong polarity
  PORTD &= ~_BV(PORTD5); 
  
  previous_on = on; 
  previous_up = up;
  previous_down = down;
  
  on = !digitalRead(on_sw);
  up = !digitalRead(up_sw);
  down = !digitalRead(down_sw);
  
  state = digitalRead(supply_en);

  if(on == HIGH && previous_on == LOW){
     digitalWrite(supply_en,!state);
     if(state==LOW){
       analogWrite(RGB_Red, 20);
       analogWrite(RGB_Blue, 20);
       analogWrite(RGB_Green, 20);
     }
     else{
       analogWrite(RGB_Red, 1);
       analogWrite(RGB_Blue, 0);
       analogWrite(RGB_Green, 0);
     } 
  }

  if(state == HIGH){
      if(up == HIGH && previous_up == LOW){
        bl_pwm = bl_pwm + 5;
      }
      else if(down == HIGH && previous_down == LOW){
        bl_pwm = bl_pwm - 5;
      }
    analogWrite(bl_pwm_pin, bl_pwm);
  }
  else {
    analogWrite(bl_pwm_pin, 0);
  }
  
  EEPROM.write(0,bl_pwm);
  
  

  
  delay(20);
}

