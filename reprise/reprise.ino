/*
  Author Benoit Pierrehumbert
  Project SIMON
  DATE 08.11.2019
  VERSION 1
*/
#include <Bounce2.h>  //inculde the debounce librarie
#define buzzer 65
#define btwnote 750
//setup the debouncer
Bounce dbu1 = Bounce(); //Set and Initalise bounce for button 1
Bounce dbu2 = Bounce(); //Set and Initalise bounce for button 2
Bounce dbu3 = Bounce(); //Set and Initalise bounce for button 3
Bounce dbu4 = Bounce(); //Set and Initalise bounce for button 4
const int NOTE[] = { //table for note
  2637, 2093, 3520, 1318, 523
};


int NB_etape = 1;
int son[31]; //save the last note
int btn=0;
int compteur=0;
int push=0;
int win=-1;

void save() { //------------------------------------function dor saving the random notes
  if (compteur==0){
  for (int i =0;i<=31;i++){
    int valrandom = random(0,4);
    son[i] = valrandom; 
    Serial.print("Save ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(son[i]);
    compteur++;
  }
  }//-------------------------------------------------------------

}
//-------------------------------------------------Function to play  
void play(int etape){
  digitalWrite(son[etape]+2,HIGH);
  tone(buzzer,NOTE[son[etape]],500);
  digitalWrite(son[etape]+2,LOW);
}//---------------------------------------------------------------


void jinglesstart () { //-----------------------------------------------function for start's random jingles
  int q = random(8, 20);
  for (int i = 0; i <= q; i++) {
    int k = random(0, 3);
    int z = random(2, 6);
    digitalWrite(z, HIGH);
    tone(buzzer, NOTE[k], 50);
    delay(100);
    digitalWrite(z, LOW);
    delay(100);
  }
}//---------------------------------------------------------------------


void jinglesgameover () { //-------------------------------------------function for game over's jingles
  int q = random(4, 8);
  for (int i = 0; i <= q; i++) {
    digitalWrite(4, HIGH);
    tone(buzzer, NOTE[4], 50);
    delay(75);
    digitalWrite(4, LOW);
    delay(75);
  }
}//--------------------------------------------------------------------

void jingleswin () { //-------------------------------------------function for win's jingles
  for (int i = 0; i <= 25; i++) {
    digitalWrite(3, HIGH);
    tone(buzzer, NOTE[3], 50);
    delay(75);
    digitalWrite(3, LOW);
    delay(75);
  }
  
}//--------------------------------------------------------------------

void updatedbus(){
  dbu1.update();
  dbu2.update();
  dbu3.update();
  dbu4.update();
}


void jingles(int who) { //---------------------------------------------function with all jingles
  if (who == 0) {
    jinglesstart();
  }
  if (who == 1) {
    jinglesgameover();
  }
  if (who == 2) {
    jingleswin();
  }
}//-------------------------------------------------------------------



int testbuttons(){//----------------------------------------------function to test button
  int button =-1;

    delay(125);

  return button;
}//-------------------------------------------------------------------------------------

void setup() { 
  randomSeed(analogRead(0));
  Serial.begin(9600);
  dbu1.attach(A2, INPUT_PULLUP);
  dbu1.interval(25);
  dbu2.attach(A3, INPUT_PULLUP);
  dbu2.interval(10);
  dbu3.attach(A4, INPUT_PULLUP);
  dbu3.interval(10);
  dbu4.attach(A5, INPUT_PULLUP);
  dbu4.interval(10);
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }

}
void song() {
    for (int p = 0; p < NB_etape; p++) {
        Serial.print("entré p == ");
        Serial.println(p);
        
        if (son[p] == 0) {
              digitalWrite(2, HIGH);
              tone(buzzer, NOTE[0], 50);
              delay(300);
              digitalWrite(2, LOW);
              
            delay(btwnote);
        }
        if (son[p] == 1) {
              digitalWrite(3, HIGH);
              tone(buzzer, NOTE[1], 50);
              delay(300);
              digitalWrite(3, LOW);
              
            delay(btwnote);
        }
        if (son[p] == 2) {
              digitalWrite(4, HIGH);
              tone(buzzer, NOTE[2], 50);
              delay(300);
              digitalWrite(4, LOW);
             
            delay(btwnote);
        }
        if (son[p] == 3) {
              digitalWrite(5, HIGH);
              tone(buzzer, NOTE[3], 50);
              delay(300);
              digitalWrite(5, LOW);
              
            delay(btwnote);
        }

    }
}
void loop() {
   save();
  //update the buttons
  updatedbus();
  if(dbu1.rose()){
    delay(btwnote);
    jingles(0);
  while(1){  
        Serial.println("dans le while 1");
    bool win = true;
        song();
    for (int i = 0; i < NB_etape; i++) {
      Serial.println(NB_etape);
      while(push==-1){
        updatedbus();
          if(dbu1.rose()){ 
            push=0;
            btn++;
            digitalWrite(2, HIGH);
            delay(250);
            digitalWrite(2, LOW);
        Serial.println("dans le while pudh 0");
          }
          if(dbu2.rose()){
            push=1;
            btn++;
            digitalWrite(3, HIGH);
            delay(250);
            digitalWrite(3, LOW);
        Serial.println("dans le while pudh 1");
          }
          if(dbu3.rose()){
            push=2;
            btn++;
            digitalWrite(4, HIGH);
            delay(250);
            digitalWrite(4, LOW);
        Serial.println("dans le while pudh 2");
          }
          if(dbu4.rose()){
            push=3;
            btn++;
            digitalWrite(5, HIGH);
            delay(250);
            digitalWrite(5, LOW);
        Serial.println("dans le while pudh 3");
          }
        }
          if ((push !=son[i])&&(btn!=0)){
            Serial.print(son[i]);
        Serial.println("  PERDU----------------------------------");
              jingles(2);
              NB_etape=1;
              push=0;
              win=false;
              delay(btwnote);
              break;
              jingles(0);
            }else{}
            push=0;
            if(win==true){//----------------if win
              NB_etape++;
              delay(btwnote);
            }
            if(NB_etape == 31){
              NB_etape=1;
              break;
                
            }
      }
    }
  }
}
