#ifndef TALKER_USING_SERIAL_H
#define TALKER_USING_SERIAL

#include <Arduino.h>
#include "Talker.h"

class TalkerUsingSerial : public Talker {
  public:
    void setup();
    void loop();
    void cancel();
    boolean isTalking();
    void sayWelcomePart1();
    void sayWelcomePart2();
    void saySignoffPart1();
    void saySignoffPart2();
    void sayMinus();
    void sayPoint();
    void sayZeroToNineteen(int n);
    void sayTwentyToNinety(int n);

  private:
    void say(const char  * PROGMEM s);
    const char  * PROGMEM saying;
    uint32_t saying_ms;
};


#endif


