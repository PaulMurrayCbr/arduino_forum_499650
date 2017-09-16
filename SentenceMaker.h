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

    void sayWelcomeMessage(float temp_C);
    void sayAdjustingMessage(float temp_C);
    void saySignoffMessage(float temp_C);
    void cancel();

  private:

    enum Message {
      NONE, WELCOME, ADJUSTING, SIGNOFF
    } message = NONE;

    enum State {
      STANDBY,
      BEGIN,
      PART_1,
      NUMBER,
      PART_2
    } state = STANDBY;

    int temp_number;
    int temp_pointFive;

    void roundTemp(float temp_C);
};

#endif
