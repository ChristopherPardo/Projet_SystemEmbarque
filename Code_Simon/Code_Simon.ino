/* Project : Simon
 * Autor : Christopher Pardo
 * Date : 04.11.2019
 * Version : 1.0
 * Description : 
 */

#include <Bounce2.h>

#define BluePin 2
#define YellowPin 3
#define RedPin 4
#define GreenPin 5

#define BlueBtnPin A2
#define YellowBtnPin A3
#define RedBtnPin A4
#define GreenBtnPin A5

// Declare and Initialize global variables. 
int ledState_1 = LOW;
int ledState_2 = LOW;
int ledState_3 = LOW;
int ledState_4 = LOW;


// Instantiate a four Bounce object
Bounce BlueBtn = Bounce(); 
Bounce YellowBtn = Bounce(); 
Bounce RedBtn = Bounce(); 
Bounce GreenBtn = Bounce();

int points = 0;
 
void setup() {
  // put your setup code here, to run once:
  BlueBtn.attach(BlueBtnPin,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  BlueBtn.interval(25); // Use a debounce interval of 25 milliseconds

  YellowBtn.attach(YellowBtnPin,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  YellowBtn.interval(25); // Use a debounce interval of 25 milliseconds

  RedBtn.attach(RedBtnPin,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  RedBtn.interval(25); // Use a debounce interval of 25 milliseconds

  GreenBtn.attach(GreenBtnPin,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  GreenBtn.interval(25); // Use a debounce interval of 25 milliseconds
  
    
  pinMode(BluePin,OUTPUT); // Setup the LED
  pinMode(YellowPin,OUTPUT); // Setup the LED
  pinMode(RedPin,OUTPUT); // Setup the LED
  pinMode(GreenPin,OUTPUT); // Setup the LED
  
  /*digitalWrite(2,ledState_1); // Apply LED state
  digitalWrite(3,ledState_2); // Apply LED state
  digitalWrite(4,ledState_3); // Apply LED state
  digitalWrite(5,ledState_4); // Apply LED state*/
}

void JingleBegin(){
  
}

void JingleEnd(){

}

/*void ButtonsGame(char Color){
  long Just = random(1,5);
  if(){
    
  }
}*/

void BlueAndNoteON(){
  digitalWrite(BluePin,HIGH);
}
void BlueAndNoteOFF(){
  digitalWrite(BluePin,LOW);
}



void loop() {
  // put your main code here, to run repeatedly:
  JingleBegin();
  do{
    BlueBtn.update();          // Update the Bounce instance
    YellowBtn.update();          // Update the Bounce instance
    RedBtn.update();          // Update the Bounce instance
    GreenBtn.update();          // Update the Bounce instance

    if(BlueBtn.fell()){
     BlueAndNoteON();
    }
    if(BlueBtn.rose()){
      BlueAndNoteOFF();
    }
    if(YellowBtn.fell()){
      digitalWrite(YellowPin,HIGH);
    }
    if(YellowBtn.rose()){
      digitalWrite(YellowPin,LOW);
    }
    if(RedBtn.fell()){
      digitalWrite(RedPin,HIGH);
    }
    if(RedBtn.rose()){
      digitalWrite(RedPin,LOW);
    }
    if(GreenBtn.fell()){
      digitalWrite(GreenPin,HIGH);
    }
    if(GreenBtn.rose()){
      digitalWrite(GreenPin,LOW);
    }
    /*else{
      for(int i = 2;i <= 5;i++){
        digitalWrite(i,LOW);
      }
    }*/
    points++;
  }while(points < 31);
}
