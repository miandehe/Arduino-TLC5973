#include "Arduino.h"

class TLC5973{
 public:
    TLC5973(uint16_t n,uint8_t p);
    void setPixelColor(uint16_t n, uint16_t r, uint16_t g, uint16_t b);
    void show();
    void begin();
    
 private:
    void updateLength();
    void pulse(); 
    void writeZero();
    void writeNone();
    void writeOne();
    void waitGSLAT(uint8_t num);
    void writeWord(uint16_t word);
    
    uint16_t
      numLEDs,       // Number of RGB LEDs in strip
      numWords,      // Size of 'pixels' buffer below (3 or 4 bytes/pixel)
      *pixels;        // Holds LED color values (3 or 4 bytes each)
      
    uint8_t pin;     

    volatile uint8_t
        *port;         // Output PORT register
    uint8_t
       pinMask;
    
};
