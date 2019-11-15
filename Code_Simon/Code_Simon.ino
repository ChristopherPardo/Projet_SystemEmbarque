/* Project : Simon_ProjetSystemEmbarqué
 * Autor : Christopher Pardo
 * Date : 15.11.2019
 * Version : 1.0
 * Description : Simon Game for a project of CPNV
 */

#include <Bounce2.h>

// Difine the LEDs
#define BluePin 2
#define YellowPin 3
#define RedPin 4
#define GreenPin 5

#define buzzer 6 // Difine the buzzer

// Difine the Buttons
#define BlueBtnPin A2
#define YellowBtnPin A3
#define RedBtnPin A4
#define GreenBtnPin A5

#define MaxTurns 32  // Max turns of the game for winning


// Instantiate a four Bounce object
Bounce BlueBtn = Bounce();
Bounce YellowBtn = Bounce();
Bounce RedBtn = Bounce();
Bounce GreenBtn = Bounce();

int points = 1;           // Nubers of Turn of play
int series[MaxTurns - 1];  // Serie of code
float NOTE[] = {329.63, 261.63, 220, 164.81, 65.41};  // Table for the notes

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

    //Setup the LED
    pinMode(BluePin, OUTPUT);
    pinMode(YellowPin, OUTPUT);
    pinMode(RedPin, OUTPUT);
    pinMode(GreenPin, OUTPUT);

    randomSeed(analogRead(0));  // Find randoms Nubers
}

// Put random values in "Serie"
void SerieNumbers() {
    for (int i = 0; i <= MaxTurns; i++) {
        int valrandom = random(1, 5);
        series[i] = valrandom;
    }
}

// The serie of lights and Notes
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

// A jingle of Begining start
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

// A jingle of end start
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

// Turn on the leds and the note
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

// Turn off the leds
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

// Update of bounce
void BtsUpdate() {
    BlueBtn.update();         // Update the Bounce instance
    YellowBtn.update();       // Update the Bounce instance
    RedBtn.update();          // Update the Bounce instance
    GreenBtn.update();        // Update the Bounce instance
}


void loop() {
    // put your main code here, to run repeatedly:
    int touch = 0;          // Button pushed
    BtsUpdate();            // Update of bounce
    SerieNumbers();         // Put random values in "Serie"
    if (BlueBtn.rose()) {   // The player have to push BlueBtn for starting
        JingleBegin();    // A jingle of Begining start
        while (1) {
            bool lose = false;  // If the game is lost
            Code();              // The serie of lights and Notes
            for (int i = 0; i < points; i++) { // Turn
                while (touch == 0) {
                    BtsUpdate();

                    if (BlueBtn.fell()) {
                        LedAndNotesON(1); // Turn on the blue leds and the note
                    }
                    if (BlueBtn.rose()) {
                        LedAndNotesOFF(1); // Turn off the leds and the note
                        touch = 1;
                    }
                    if (YellowBtn.fell()) {
                        LedAndNotesON(2); // Turn on the Yellow leds and the note
                    }
                    if (YellowBtn.rose()) {
                        LedAndNotesOFF(2); // Turn off the leds and the note
                        touch = 2;
                    }
                    if (RedBtn.fell()) {
                        LedAndNotesON(3); // Turn on the red leds and the note
                    }
                    if (RedBtn.rose()) {
                        LedAndNotesOFF(3); // Turn off the leds and the note
                        touch = 3;
                    }
                    if (GreenBtn.fell()) {
                        LedAndNotesON(4); // Turn on the Green leds and the note
                    }
                    if (GreenBtn.rose()) {
                        LedAndNotesOFF(4); // Turn off the leds and the note
                        touch = 4;
                    }
                }
                if (touch != series[i]) {
                       // Game over
                       // Restart the parameters for restart
                    points = 1;
                    touch = 0;
                    lose = true;
                    tone(buzzer, NOTE[4], 800);
                    delay(800);
                    JingleBegin(); // A jingle of Begining start
                    break;
                }
                touch = 0;
            }
            if (lose == false) {
                   // Add one of the serie
                points++;
                delay(600);
            }
            if (points == MaxTurns) {
                   // End game
                JingleEnd(); // A jingle of Begining start
                points = 1;
                break;
            }
        }
    }
}
