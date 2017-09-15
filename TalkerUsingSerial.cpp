#include <Arduino.h>
#include "TalkerUsingSerial.h"

void TalkerUsingSerial::setup() {
  Serial.begin(9600);
  while (!Serial);
}

void TalkerUsingSerial::loop() {
  if (!saying || !pgm_read_byte_near(saying) || (millis() - saying_ms) < 100) return;

  Serial.print((char)pgm_read_byte_near(saying++));
  saying_ms = millis();
}

void TalkerUsingSerial::cancel() {}

boolean TalkerUsingSerial::isTalking() {
  return saying && pgm_read_byte_near(saying);
}

void TalkerUsingSerial::say(const  char * PROGMEM s) {
  saying = s;
}

void TalkerUsingSerial::sayWelcomePart1() {
  say(PSTR("Bing bong, it is "));
}

void TalkerUsingSerial::sayWelcomePart2() {
  say(PSTR(" degrees. To raise the temperature press the red button, to lower the temperature press the blue button."));
}

void TalkerUsingSerial::saySignoffPart1() {
  say(PSTR("The new setpoint is "));
}

void TalkerUsingSerial::saySignoffPart2() {
  say(PSTR(" degrees."));
}

void TalkerUsingSerial::sayMinus() {
  say(PSTR(" minus"));
}

void TalkerUsingSerial::sayPoint() {
  say(PSTR(" point"));
}

void TalkerUsingSerial::sayZeroToNineteen(int n) {
  switch (n) {
    case 0: say(PSTR(" zero")); break;
    case 1: say(PSTR(" one")); break;
    case 2: say(PSTR(" two")); break;
    case 3: say(PSTR(" three")); break;
    case 4: say(PSTR(" four")); break;
    case 5: say(PSTR(" five")); break;
    case 6: say(PSTR(" six")); break;
    case 7: say(PSTR(" seven")); break;
    case 8: say(PSTR(" eight")); break;
    case 9: say(PSTR(" nine")); break;
    case 10: say(PSTR(" ten")); break;
    case 11: say(PSTR(" eleven")); break;
    case 12: say(PSTR(" twelve")); break;
    case 13: say(PSTR(" thirteen")); break;
    case 14: say(PSTR(" fourteen")); break;
    case 15: say(PSTR(" fifteen")); break;
    case 16: say(PSTR(" sixteen")); break;
    case 17: say(PSTR(" seventeen")); break;
    case 18: say(PSTR(" eighteen")); break;
    case 19: say(PSTR(" nineteen")); break;
  }
}

void TalkerUsingSerial::sayTwentyToNinety(int n) {
  switch (n) {
    case 20: say(PSTR(" twenty")); break;
    case 30: say(PSTR(" thirty")); break;
    case 40: say(PSTR(" forty")); break;
    case 50: say(PSTR(" fifty")); break;
    case 60: say(PSTR(" sixty")); break;
    case 70: say(PSTR(" seventy")); break;
    case 80: say(PSTR(" eighty")); break;
    case 90: say(PSTR(" ninety")); break;
  }
}

