/*
 * buttons all go to ground and use pull_up as input
 * They go from pin 2 to 12
 */

#include <EEPROM.h>
#include <Keyboard.h>

#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5
#define btn5 6
#define btn6 7
#define numberButton 6
#define pinMin 2
#define pinMax 7

int strokes[numberButton][9];

void setup() {
  for (int i = 2; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  Serial1.begin(9600);
  Keyboard.begin();
  
  int iterations = 0;
  int h = 0, k = 0;
  delay(1000);
  while (iterations < numberButton) {
    int addr = (9 * sizeof(int) * h) + (k * sizeof(int));
    int tmpget;
    EEPROM.get(addr, tmpget);
    strokes[h][k] = tmpget;
    if (k == 8) {
      k = 0;
      ++h;
      ++iterations;
    } else {
      ++k;
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
        EEPROM.put(((btnnumber - 1) * (9 * sizeof(int))) + i, tmp);
        strokes[btnnumber - 1][j] = tmp;
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
        EEPROM.get(((tmp2 - 1) * (9 * sizeof(int))) + i, eepromRead);
        Serial.println(eepromRead);
        //Serial.print(" ");
      }
      //Serial.println("/");
      Serial.read();
    }
  }

  if (digitalRead(btn1) == LOW) {
    const int n = 0;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  } else if (digitalRead(btn2) == LOW) {
    const int n = 1;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  } else if (digitalRead(btn3) == LOW) {
    const int n = 2;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  } else if (digitalRead(btn4) == LOW) {
    const int n = 3;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  } else if (digitalRead(btn5) == LOW) {
    const int n = 4;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  } else if (digitalRead(btn6) == LOW) {
    const int n = 5;
    Keyboard.write(strokes[n][0]);
    delay(strokes[n][1]);
    Keyboard.write(strokes[n][2]);
    delay(strokes[n][3]);
    Keyboard.write(strokes[n][4]);
    delay(strokes[n][5]);
    Keyboard.write(strokes[n][6]);
    delay(strokes[n][7]);
    Keyboard.write(strokes[n][8]);
  }
}
