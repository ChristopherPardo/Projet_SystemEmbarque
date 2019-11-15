/* Project : Simon_ProjetSystemEmbarqué
 * Autor : Christopher Pardo
 * Date : 15.11.2019
 * Version : 1.0
 * Description :
 */

#include <Bounce2.h>
#include<time.h>

#define BluePin 2
#define YellowPin 3
#define RedPin 4
#define GreenPin 5

#define buzzer 6

#define BlueBtnPin A2
#define YellowBtnPin A3
#define RedBtnPin A4
#define GreenBtnPin A5

#define MaxTurns 32

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
int series[MaxTurns - 1];
float NOTE[] = {329.63, 261.63, 220, 164.81, 65.41};  //table for note

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

    randomSeed(analogRead(0));
}

void SerieNumbers() {
    for (int i = 0; i <= MaxTurns; i++) {
        int valrandom = random(1, 5);
        series[i] = valrandom;
    }
}

void Code() {
    for (int j = 0; j < points; j++) {
        for (int k = 1; k <= 4; k++) {
            if (series[j] == k) {
                LedAndNotesON(k);
                delay(600);
            }
            LedAndNotesOFF(k);
            delay(50);
        }
    }
}

void JingleBegin() {
    LedAndNotesON(1);
    delay(100);
    LedAndNotesOFF(1);
    delay(200);
    LedAndNotesON(4);
    delay(100);
    LedAndNotesOFF(4);
    delay(200);
    LedAndNotesON(1);
    delay(100);
    LedAndNotesOFF(1);
    delay(200);
    LedAndNotesON(2);
    delay(100);
    LedAndNotesOFF(2);
    delay(200);
    LedAndNotesON(4);
    delay(100);
    LedAndNotesOFF(4);
    delay(200);
    LedAndNotesON(3);
    delay(100);
    LedAndNotesOFF(3);
    delay(1000);
}

void JingleEnd() {
    LedAndNotesON(3);
    delay(100);
    LedAndNotesOFF(3);
    delay(200);
    LedAndNotesON(4);
    delay(100);
    LedAndNotesOFF(4);
    delay(200);
    LedAndNotesON(2);
    delay(100);
    LedAndNotesOFF(2);
    delay(200);
    LedAndNotesON(1);
    delay(100);
    LedAndNotesOFF(1);
    delay(200);
    LedAndNotesON(4);
    delay(100);
    LedAndNotesOFF(4);
    delay(200);
    LedAndNotesON(3);
    delay(100);
    LedAndNotesOFF(3);
}


void LedAndNotesON(int color) {
    if (color == 1) {
        digitalWrite(BluePin, HIGH);
        tone(buzzer, NOTE[0]);
    }
    if (color == 2) {
        digitalWrite(YellowPin, HIGH);
        tone(buzzer, NOTE[1]);
    }
    if (color == 3) {
        digitalWrite(RedPin, HIGH);
        tone(buzzer, NOTE[2]);
    }
    if (color == 4) {
        digitalWrite(GreenPin, HIGH);
        tone(buzzer, NOTE[3]);
    }
}

void LedAndNotesOFF(int color) {
    if (color == 1) {
        digitalWrite(BluePin, LOW);
    }
    if (color == 2) {
        digitalWrite(YellowPin, LOW);
    }
    if (color == 3) {
        digitalWrite(RedPin, LOW);
    }
    if (color == 4) {
        digitalWrite(GreenPin, LOW);
    }
    noTone(buzzer);
}

void BtsUpdate() {
    BlueBtn.update();         // Update the Bounce instance
    YellowBtn.update();       // Update the Bounce instance
    RedBtn.update();          // Update the Bounce instance
    GreenBtn.update();        // Update the Bounce instance
}


void loop() {
    // put your main code here, to run repeatedly:
    BtsUpdate();
    SerieNumbers();
    if (BlueBtn.rose()) {
        JingleBegin();
        while (1) {
            bool lose = false;
            Code();
            for (int i = 0; i < points; i++) {
                Serial.print(series[i]);
                while (touch == 0) {
                    BtsUpdate();

                    if (BlueBtn.fell()) {
                        LedAndNotesON(1);
                    }
                    if (BlueBtn.rose()) {
                        LedAndNotesOFF(1);
                        touch = 1;
                    }
                    if (YellowBtn.fell()) {
                        LedAndNotesON(2);
                    }
                    if (YellowBtn.rose()) {
                        LedAndNotesOFF(2);
                        touch = 2;
                    }
                    if (RedBtn.fell()) {
                        LedAndNotesON(3);
                    }
                    if (RedBtn.rose()) {
                        LedAndNotesOFF(3);
                        touch = 3;
                    }
                    if (GreenBtn.fell()) {
                        LedAndNotesON(4);
                    }
                    if (GreenBtn.rose()) {
                        LedAndNotesOFF(4);
                        touch = 4;
                    }
                }
                Serial.print("entré");
                if (touch != series[i]) {
                    Serial.print("sortie");
                    points = 1;
                    touch = 0;
                    lose = true;
                    tone(buzzer, NOTE[4], 800);
                    delay(800);
                    JingleBegin();
                    break;
                }
                touch = 0;
            }
            if (lose == false) {
                //Serial.print("c'esttoutbon");
                points++;
                delay(600);
            }
            if (points == MaxTurns) {
                JingleEnd();
                points = 1;
                break;
            }
        }
    }
}