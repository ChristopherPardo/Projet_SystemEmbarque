/* Project : Simon_ProjetSystemEmbarqué
 * Autor : Christopher Pardo
 * Date : 13.11.2019
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

int points = 1;
int touch = 0;
int tour = 0;
int series[] = {1, 2, 3, 4, 1, 2, 3, 4};

void setup() {
    // put your setup code here, to run once:
    BlueBtn.attach(BlueBtnPin, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    BlueBtn.interval(25); // Use a debounce interval of 25 milliseconds

    YellowBtn.attach(YellowBtnPin, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    YellowBtn.interval(25); // Use a debounce interval of 25 milliseconds

    RedBtn.attach(RedBtnPin, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    RedBtn.interval(25); // Use a debounce interval of 25 milliseconds

    GreenBtn.attach(GreenBtnPin, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
    GreenBtn.interval(25); // Use a debounce interval of 25 milliseconds


    pinMode(BluePin, OUTPUT); // Setup the LED
    pinMode(YellowPin, OUTPUT); // Setup the LED
    pinMode(RedPin, OUTPUT); // Setup the LED
    pinMode(GreenPin, OUTPUT); // Setup the LED

    /*digitalWrite(2,ledState_1); // Apply LED state
    digitalWrite(3,ledState_2); // Apply LED state
    digitalWrite(4,ledState_3); // Apply LED state
    digitalWrite(5,ledState_4); // Apply LED state*/

    Serial.begin(9600);


}

// code qui devient de + en + long
void Code() {
    for (int j = 0; j < points; j++) {
        if (series[j] == 1) {
            BlueAndNoteON();
            delay(600);
        }
        if (series[j] == 2) {
            digitalWrite(YellowPin, HIGH);
            delay(600);
        }
        if (series[j] == 3) {
            digitalWrite(RedPin, HIGH);
            delay(600);
        }
        if (series[j] == 4) {
            digitalWrite(GreenPin, HIGH);
            delay(600);
        }
        for (int k = 2; k <= 5; k++) {
            digitalWrite(k, LOW);
        }
        Serial.print("entré\n");
    }
}

void JingleBegin() {

}

void JingleEnd() {
    Serial.print("gagné");
}

void JigleLose() {
    Serial.print("perdu");
}

/*void ButtonsGame(char Color){
  long Just = random(1,5);
  if(){

  }
}*/

void BlueAndNoteON() {
    digitalWrite(BluePin, HIGH);
}

void BlueAndNoteOFF() {
    digitalWrite(BluePin, LOW);
}


void loop() {
    // put your main code here, to run repeatedly:
    JingleBegin();
    while (1) {
        Code();
    }
}