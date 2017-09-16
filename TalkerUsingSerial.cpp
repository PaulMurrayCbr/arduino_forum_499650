#include <Arduino.h>
#include "TalkerUsingSerial.h"

void TalkerUsingSerial::setup() {
  Serial.begin(9600);
  while (!Serial);
}

void TalkerUsingSerial::loop() {
  if (!saying || !pgm_read_byte_near(saying) || (millis() - saying_ms) < 50) return;

  Serial.print((char)pgm_read_byte_near(saying++));
  saying_ms = millis();
}

void TalkerUsingSerial::cancel() {
  Serial.println();
}

void TalkerUsingSerial::done() {
  Serial.println();
}

boolean TalkerUsingSerial::isTalking() {
  return saying && pgm_read_byte_near(saying);
}

void TalkerUsingSerial::say(const char * PROGMEM s) {
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

const char s_10[] PROGMEM = "ten";
const char PROGMEM s_11[] = "eleven";
const char PROGMEM s_12[] = "twelve";
const char PROGMEM s_13[] = "thirteen";
const char PROGMEM s_14[] = "fourteen";
const char PROGMEM s_15[] = "fifteen";
const char PROGMEM s_16[] = "sixteen";
const char PROGMEM s_17[] = "seventeen";
const char PROGMEM s_18[] = "eighteen";
const char PROGMEM s_19[] = "nineteen";
const char PROGMEM s_20[] = "twenty";
const char PROGMEM s_21[] = "twenty one";
const char PROGMEM s_22[] = "twenty two";
const char PROGMEM s_23[] = "twenty three";
const char PROGMEM s_24[] = "twenty four";
const char PROGMEM s_25[] = "twenty five";
const char PROGMEM s_26[] = "twenty six";
const char PROGMEM s_27[] = "twenty seven";
const char PROGMEM s_28[] = "twenty eight";
const char PROGMEM s_29[] = "twenty nine";
const char PROGMEM s_30[] = "thirty";

const char PROGMEM s_105[] = "ten point five";
const char PROGMEM s_115[] = "eleven point five";
const char PROGMEM s_125[] = "twelve point five";
const char PROGMEM s_135[] = "thirteen point five";
const char PROGMEM s_145[] = "fourteen point five";
const char PROGMEM s_155[] = "fifteen point five";
const char PROGMEM s_165[] = "sixteen point five";
const char PROGMEM s_175[] = "seventeen point five";
const char PROGMEM s_185[] = "eighteen point five";
const char PROGMEM s_195[] = "nineteen point five";
const char PROGMEM s_205[] = "twenty point five";
const char PROGMEM s_215[] = "twenty one point five";
const char PROGMEM s_225[] = "twenty two point five";
const char PROGMEM s_235[] = "twenty three point five";
const char PROGMEM s_245[] = "twenty four point five";
const char PROGMEM s_255[] = "twenty five point five";
const char PROGMEM s_265[] = "twenty six point five";
const char PROGMEM s_275[] = "twenty seven point five";
const char PROGMEM s_285[] = "twenty eight point five";
const char PROGMEM s_295[] = "twenty nine point five";
const char PROGMEM s_305[] = "thirty point five";

static const char *saynumber[] = {
  NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  s_10,  s_11,  s_12,  s_13,  s_14,  s_15,  s_16,  s_17,  s_18,  s_19,
  s_20,  s_21,  s_22,  s_23,  s_24,  s_25,  s_26,  s_27,  s_28,  s_29,
  s_30
};

static const char * saynumberpointfive[] = {
  NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  s_105,  s_115,  s_125,  s_135,  s_145,  s_155,  s_165,  s_175,  s_185,  s_195,
  s_205,  s_215,  s_225,  s_235,  s_245,  s_255,  s_265,  s_275,  s_285,  s_295,
  s_305
};

void TalkerUsingSerial::sayNumber(int number, boolean pointFive) {
  say((pointFive ? saynumberpointfive : saynumber) [number]);
}


