/**
   A Talker is a thing that knows how to say the fragments of sentences that are going to be required
   by this sketch.

   We have two implementations - a TalkerUsingSerial, which simulates what a soundcard does by
   spitting out text slowly to the serial output, and a TalkerUsingSoundcard, which is not written yet.
*/

#ifndef TALKER_H
#define TALKER_H

#include <Arduino.h>

class Talker {
  public:

    /**
        a talker has a setup and loop. setup gets invoked by the main sketch at setup time, loop
        gets invoked by the main sketch frequently
    */
    virtual void setup() = 0;
    virtual void loop() = 0;

    /**
       a talker can have its talking cut short.
    */

    virtual void cancel() = 0;

    /**
        SentenceMaker calls this at the end of the sentence. A talker might use that to - for instance
        - turn speakers off. 
        Really, it's here because we want our TalkerUSingSerial to put a line break at the end of
        a sentence. But, it still might be useful for putting a soundcard version to sleep.  
    */

    virtual void done() = 0;

    /**
       A talker takes a while to finish talking. SentenceMaker polls this function to find out
       if the current phrase has been finished. This seems to be how soundcard libraries work.
    */

    virtual boolean isTalking() = 0;

    virtual void sayWelcomePart1() = 0; // Bing bong, it is
    virtual void sayWelcomePart2() = 0; // degrees. To raise the temperature press the red button, to lower the temperature press the blue button

    virtual void saySignoffPart1() = 0; // The new set point is
    virtual void saySignoffPart2() = 0; // degrees.

    /** will say a number between 10 and 30 in increments of .5 degrees */
    virtual void sayNumber(int number, boolean pointFive) = 0; 

};

#endif

