/**
   The sentence maker class has the job of breaking up numbers and messages into strings of words that
   can be spoken by a talker.
*/

#ifndef SENTENCEMAKER_H
#define SENTENCEMAKER_H

#include "Talker.h"

class SentenceMaker {
  private:
    Talker& talker;

  public:

    SentenceMaker(Talker& talkerAttach) : talker(talkerAttach) {}

    void setup();
    void loop();

    void sayWelcomeMessage(int temp_dC);
    void sayAdjustingMessage(int temp_dC);
    void saySignoffMessage(int temp_dC);
    void cancel();

  private:

    enum Message {
      NONE, WELCOME, ADJUSTING, SIGNOFF
    } message = NONE;

    enum State {
      STANDBY,
      BEGIN,
      PART_1,
      MINUS, TENS, UNITS, POINT, DECIMAL,
      PART_2
    } state = STANDBY;

    int temp_dC;
};

#endif
