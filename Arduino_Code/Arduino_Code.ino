/*
 * buttons all go to ground and use pull_up as input
 * They go from pin 2 to 12
 */

#include <EEPROM.h>

#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5
#define btn5 6
#define btn6 7
//#define btn7 8
//#define btn8 9
//#define btn9 10
//#define btn10 11
//#define btn11 12
#define numberButton 6
#define pinMin 2
#define pinMax 7

int strokes[numberButton][9];

//struct key {
//  int binding1;
//  int delay1;
//  int binding2;
//  int delay2;
//  int binding3;
//  int delay3;
//  int binding4;
//  int delay4;
//  int binding5;
//};
//
//struct board {
//  key k1;
//  key k2;
//  key k3;
//  key k4;
//  key k5;  
//  key k6;
//};

void setup() {
  for (int i = 2; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  Serial.begin(9600);
  //Keyboard.begin();

  int h = 0;
  for (int i = 0; i <= numberButton; i++) {
    for (int j = 0; j < 9 * sizeof(int); j += sizeof(int)) {
      int tmpget;
      EEPROM.get(j, tmpget);
      strokes[i][h] = tmpget;
      h++;
    }
  }

  Serial.println("Finished Setup");
}

/*
 * The Serial data will be a sequence of ints, going into an array with the following order:
 * {Button PIN, KEY, delay, KEY, delay, KEY, delay, KEY, delay, KEY}
 * 
 * MAX 5 keys combos
 * 
 */

void loop() {
  if (Serial.available() > 0) {
    int tmp1 = Serial.read();
    delay(100);
    int btnnumber = char(tmp1) - '0';
    String debugString = "Button Number: ";
    Serial.println(debugString + btnnumber);
    if (btnnumber > 0 && btnnumber <= pinMax) {
      int keySeries[9];
      for (int i = 0, j = 0; i < 9 * sizeof(int); i += sizeof(int)) {
        int tmp = Serial.read();
        delay(100);
        keySeries[j] = tmp;
        Serial.print(keySeries[j]);
        Serial.print(" ");
        EEPROM.put((btnnumber * 9 ) - 9 + i, tmp);
        strokes[btnnumber][j] = tmp;
        j++;
      }
      Serial.println();
      Serial.read();
    } else if (btnnumber == 48) { //Debug: read the EEPROM row. Format {`, button}
      Serial.println("Reading EEPROM:");
      int tmp2 = Serial.read();
      delay(100);
      tmp2 = char(tmp2) - '0';
      for (int i = 0; i < 9 * sizeof(int); i += sizeof(int)) {
        int eepromRead;
        EEPROM.get((tmp2 * 9) - 9 + i, eepromRead);
        Serial.print(eepromRead);
        Serial.print(" ");
      }
      Serial.println("/");
      Serial.read();
    }
  }

}
