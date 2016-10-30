#include <math.h>

const int NUM_ANIMATIONS = 4;

int   animation = 2;
long  startTime = 0;
float time      = 0;


void loopAnimation()
{
  time = (millis() - startTime) / 1000.0;
  
  switch ( animation )
  {
    case 0 : animBlink(); break;
    case 1 : animColourWheel(); break;
    case 2 : animBreathe(); break;
    case 3 : animKITT(); break;
  }
  
  if ( time > 1 && digitalRead(PIN_BUTTON) == HIGH )
  {
    animation = (animation + 1) % NUM_ANIMATIONS;
    startTime = millis();
  }
}


void animBlink()
{
  byte r,g,b;
  for ( int i = 0 ; i < NUM_LEDS ; i++ )
  {
    float frac = (float) i / NUM_LEDS;
    float v    = fmod((time + frac) * 250, 250) > 125 ? 100 : 0; 
    HSV_to_RGB(time * 5, 100, v, &r, &g, &b);
    leds.setPixelColor(i, leds.Color(r, g, b));
  }
  leds.show();
}


void animColourWheel()
{
  byte r,g,b;
  for ( int i = 0 ; i < NUM_LEDS ; i++ )
  {
    float frac = (float) i / NUM_LEDS;
    float h = (time * 50) + (frac * 360);
    HSV_to_RGB(h, 100, 100, &r, &g, &b);
    leds.setPixelColor(i, leds.Color(r, g, b));
  }
  leds.show();
}


void animBreathe()
{
  byte r,g,b;
  time = (millis() - startTime) / 1000.0;
  
  for ( int i = 0 ; i < NUM_LEDS ; i++ )
  {
    float frac = (float) i / NUM_LEDS;
    byte  s    = 50 + 50 * sin(time * 4 + frac * 2 * PI);
    byte  v    = 0 + 50 * -1 *sin(time * 4 + frac * 2 * PI);
    HSV_to_RGB(120, s, v, &r, &g, &b);
    leds.setPixelColor(i, leds.Color(r, g, b));
  }
  leds.show();
}


void animKITT()
{
  byte r,g,b;
  leds.clear();
  HSV_to_RGB(time * 5, 100, 100, &r, &g, &b);
  r = 255; g = 0; b =0 ;
  leds.setPixelColor((int) ((NUM_LEDS - 0.01) * (0.5 + 0.5 * sin(time * 5))), leds.Color(r, g, b));
  HSV_to_RGB(180 + time * 5, 100, 100, &r, &g, &b);
  r = 0 ; g = 255; b= 0;
  leds.setPixelColor((int) ((NUM_LEDS - 0.01) * (0.5 + 0.5 * cos(time * 5))), leds.Color(r, g, b));
  leds.show();
}



//
// Convert HSV values to RGB
// Source: https://gist.github.com/hdznrrd/656996
//
void HSV_to_RGB(float h, float s, float v, byte *r, byte *g, byte *b)
{
  h = fmod(h, 360.0);
  s = max(0.0, min(100.0, s)) / 100;
  
  if(s == 0) {
    // Achromatic (grey)
    *r = *g = *b = round(v*255);
    return;
  }

  v = max(0.0, min(100.0, v)) / 100;

  h /= 60; // sector 0 to 5
  int   i = floor(h);
  float f = h - i; // factorial part of h
  
  float p = v * (1 - s);
  float q = v * (1 - s * f);
  float t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      *r = round(255*v);
      *g = round(255*t);
      *b = round(255*p);
      break;
    case 1:
      *r = round(255*q);
      *g = round(255*v);
      *b = round(255*p);
      break;
    case 2:
      *r = round(255*p);
      *g = round(255*v);
      *b = round(255*t);
      break;
    case 3:
      *r = round(255*p);
      *g = round(255*q);
      *b = round(255*v);
      break;
    case 4:
      *r = round(255*t);
      *g = round(255*p);
      *b = round(255*v);
      break;
    default: // case 5:
      *r = round(255*v);
      *g = round(255*p);
      *b = round(255*q);
    }
}

