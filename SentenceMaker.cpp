
#include "SentenceMaker.h"


void SentenceMaker::setup() {
  // no harware setup required - that kind og thing is up to the talker.
}

void SentenceMaker::loop() {
  if (message == NONE || state == STANDBY) return;
  if (state != BEGIN && talker.isTalking()) return;

  // the abels are a little confusing. each case gets called when the
  // talker has *finished* saying what the label indicates

  switch (state) {
    case STANDBY:
      // this never happens;
      break;

    case BEGIN:
      switch (message) {
        case NONE:
          // this never happens;
          break;
        case WELCOME:
          talker.sayWelcomePart1();
          break;
        case ADJUSTING:
          break;
        case SIGNOFF:
          talker.saySignoffPart1();
          break;
      }
      state = PART_1;
      break;

    case PART_1 :
      talker.sayNumber(temp_number, temp_pointFive);
      state = NUMBER;
      break;

    case NUMBER:
      switch (message) {
        case NONE:
          // this never happens;
          break;
        case WELCOME:
          talker.sayWelcomePart2();
          break;
        case ADJUSTING:
          break;
        case SIGNOFF:
          talker.saySignoffPart2();
      }
      state = PART_2;
      break;

    case PART_2:
      talker.done();
      state = STANDBY;
      break;
  }
}

void SentenceMaker::sayWelcomeMessage(float temp_C) {
  talker.cancel();
  message = WELCOME;
  roundTemp(temp_C);
  state = BEGIN;
}

void SentenceMaker::sayAdjustingMessage(float temp_C) {
  talker.cancel();
  message = ADJUSTING;
  roundTemp(temp_C);
  state = BEGIN;
}

void SentenceMaker::saySignoffMessage(float temp_C) {
  talker.cancel();
  message = SIGNOFF;
  roundTemp(temp_C);
  state = BEGIN;
}

void SentenceMaker::roundTemp(float temp) {
  int halfDegree = (int) (temp * 2 + .5);
  temp_number = halfDegree / 2;
  temp_pointFive = (halfDegree % 2) == 1;
}

void SentenceMaker::cancel() {
  talker.cancel();
  message = NONE;
  state = STANDBY;
}
