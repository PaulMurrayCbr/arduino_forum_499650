#ifndef TALKER_USING_SOUNDCARD_H
#define TALKER_USING_SOUNDCARD_H

#include <Arduino.h>
#include "Talker.h"

class TalkerUsingSoundcard : public Talker {
  public:
    void setup();
    void loop();
    void cancel();
    void done();
    boolean isTalking();
    void sayWelcomePart1();
    void sayWelcomePart2();
    void saySignoffPart1();
    void saySignoffPart2();
    void sayMinus();
    void sayPoint();
    void sayZeroToNineteen(int n);
    void sayTwentyToNinety(int n);
};



#endif


