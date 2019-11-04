/* Project : Simon
 * Autor : Christopher Pardo
 * Date : 04.11.2019
 * Version : 1.0
 * Description : 
 */

#include <Bounce2.h>

// Declare and Initialize global variables. 
int ledState_1 = LOW;
int ledState_2 = LOW;
int ledState_3 = LOW;
int ledState_4 = LOW;

// Instantiate a four Bounce object
Bounce debouncer_1 = Bounce(); 
Bounce debouncer_2 = Bounce(); 
Bounce debouncer_3 = Bounce(); 
Bounce debouncer_4 = Bounce();

int points = 0;
 
void setup() {
  // put your setup code here, to run once:
  debouncer_1.attach(8,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_1.interval(25); // Use a debounce interval of 25 milliseconds

  debouncer_2.attach(9,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_2.interval(25); // Use a debounce interval of 25 milliseconds

  debouncer_3.attach(10,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_3.interval(25); // Use a debounce interval of 25 milliseconds

  debouncer_4.attach(11,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_4.interval(25); // Use a debounce interval of 25 milliseconds
  
    
  pinMode(2,OUTPUT); // Setup the LED
  pinMode(3,OUTPUT); // Setup the LED
  pinMode(4,OUTPUT); // Setup the LED
  pinMode(5,OUTPUT); // Setup the LED
  
  digitalWrite(2,ledState_1); // Apply LED state
  digitalWrite(3,ledState_2); // Apply LED state
  digitalWrite(4,ledState_3); // Apply LED state
  digitalWrite(5,ledState_4); // Apply LED state
}

void JingleBegin(){
  
}

void JingleEnd(){

}

void loop() {
  // put your main code here, to run repeatedly:
  JingleBegin();
  do{
    debouncer_1.update();          // Update the Bounce instance
    debouncer_2.update();          // Update the Bounce instance
    debouncer_3.update();          // Update the Bounce instance
    debouncer_4.update();          // Update the Bounce instance
    
    if(deboucer_1.fell()){
      
    }
    points++;
  }while(points < 30)
}
