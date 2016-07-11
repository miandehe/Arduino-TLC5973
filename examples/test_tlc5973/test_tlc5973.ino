#include <TLC5973.h>

byte LED = 8;
uint16_t N = 8;

TLC5973 strip=TLC5973(N, LED);

void setup() {
  Serial.begin(9600);
  strip.begin();
  for(int i=0; i<N; i++) strip.setPixelColor(i, 0, 0, 0);
  strip.show();
}
    
void loop() {
  for(int i=0; i<N; i++) 
    {
      strip.setPixelColor(i, 4095, 0, 0);
      strip.show();
      delay(100);
    }
  for(int i=N-1; i>=0; i--) 
    {
      strip.setPixelColor(i, 0, 4095, 0);
      strip.show();
      delay(100);
    }
  for(int i=0; i<N; i++) 
    {
      strip.setPixelColor(i, 0, 0, 4095);
      strip.show();
      delay(100);
    }
  for(int i=N-1; i>=0; i--) 
  {
    strip.setPixelColor(i, 4095, 4095, 4095);
    strip.show();
    delay(100);
  }
}
