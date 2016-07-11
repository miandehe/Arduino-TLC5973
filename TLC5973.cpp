#include "TLC5973.h"

#define NOP __asm__ __volatile__ ("nop\n\t")

TLC5973::TLC5973(uint16_t n, uint8_t p)
  {
    pin = p;
    numLEDs = n;
    updateLength();
  }

void TLC5973::updateLength() {
  if(pixels) free(pixels); // Free existing data (if any)
  numWords = numLEDs * 3;
  if((pixels = (uint16_t *)malloc(numWords)))
      memset(pixels, 0, numWords);
  else numLEDs = numWords = 0;
}

void TLC5973::begin(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  port    = portOutputRegister(digitalPinToPort(pin));
  pinMask = digitalPinToBitMask(pin);
}

// Set pixel color from separate R,G,B components:
void TLC5973::setPixelColor(uint16_t n, uint16_t r, uint16_t g, uint16_t b) {
  if(n < numLEDs) {
    uint16_t *p;
    p = &pixels[n * 3];    // 3 bytes per pixel
    p[2] = r;          // R,G,B always stored
    p[1] = g;
    p[0] = b;
  }
}


void TLC5973::pulse() 
  {
    *port|=pinMask;
    *port&=~pinMask;
  }
  
void TLC5973::writeZero(){
    pulse();
    NOP;
    NOP;
}

void TLC5973::writeNone(){
    NOP;
    NOP;
    NOP;
    NOP;
}

void TLC5973::writeOne(){
    pulse();
    pulse();
}

void TLC5973::waitGSLAT(uint8_t num){
  unsigned char i;
   for(i = 0; i < num; i++){
      writeNone();
  }
}

void TLC5973::writeWord(uint16_t word){
    unsigned char i;
    for(i = 0; i < 12; i++){
        if(word & 0x800)
            writeOne();
        else
            writeZero();
        word <<= 1;
    }
}

void TLC5973::show(){
   noInterrupts(); // Need 100% focus on instruction timing
   for(uint16_t i = 0; i < numWords; i=i+3){
      writeWord( 0x03AA);    
      writeWord( pixels[i] );
      writeWord( pixels[i+1] );
      writeWord( pixels[i+2] );
      waitGSLAT(4);
   }
   waitGSLAT(4);
   interrupts();
}

