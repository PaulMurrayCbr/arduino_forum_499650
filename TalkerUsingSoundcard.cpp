
/**
   THIS IS THE MAIN BIT NEEDING TO BE IMPLEMENTED.

   All of these methods are blank. Gear needs to be put in them to initialize the sound card
   and to acessthe various SD-card files containing the phrases to be spoken.
*/


#include <Arduino.h>
#include "TalkerUsingSoundcard.h"

void TalkerUsingSoundcard::setup() {}

void TalkerUsingSoundcard::loop() {}

void TalkerUsingSoundcard::cancel() {}

void TalkerUsingSoundcard::done() {}

boolean TalkerUsingSoundcard::isTalking() {
  return false;
}

void TalkerUsingSoundcard::sayWelcomePart1() {}
void TalkerUsingSoundcard::sayWelcomePart2() {}

void TalkerUsingSoundcard::saySignoffPart1() {}
void TalkerUsingSoundcard::saySignoffPart2() {}

void TalkerUsingSoundcard::sayMinus() {}
void TalkerUsingSoundcard::sayPoint() {}

void TalkerUsingSoundcard::sayZeroToNineteen(int n) {}
void TalkerUsingSoundcard::sayTwentyToNinety(int n) {}

