#include <Adafruit_NeoPixel.h>

/*
  # Moisture sensor code
  #
  # Connect the sensor to an A pin(Analog 0/1 on the Arduino board

  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water
*/

int moisturePin = A0;
int soilMoisture = 0;

int UVPin = A2; //Output from the UV sensor

//float uvLowThreshold = ;
//float uvHighThreshold = ;

int mThresholdHigh = 700;
int mThresholdLow  = 250;

const int PIN_DATA   = 6;  // data pin
const int PIN_BUTTON = 3;  // button pin
const int NUM_LEDS   = 35; // number of LEDs

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_DATA, NEO_GRB + NEO_KHZ800);
//bool oldState = HIGH;  from buttoncycle example sketch
//int showType = 0;


void setup() {

  Serial.begin(9600);
  pinMode(moisturePin, INPUT);
  pinMode(UVPin, INPUT);
  pinMode(PIN_BUTTON, INPUT);
  leds.begin();           // initialise the NeoPixel library
  leds.setBrightness(40); // set global brightness fairly low
  leds.show();


}


void loop() {

  int uvLevel = averageAnalogRead(UVPin);

  float outputVoltage = 5.0 * uvLevel / 1024;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);

  //set analog read from A0 pin to soilMoisture variable
  soilMoisture = analogRead(moisturePin);
  Serial.print("Moisture Sensor Value:");
  Serial.println(soilMoisture);

//  Serial.print("UVAnalogOutput: ");
//  Serial.print(uvLevel);
//
//  Serial.print(" OutputVoltage: ");
//  Serial.print(outputVoltage);
//
//  Serial.print(" UV Intensity: ");
//  Serial.print(uvIntensity);
//  Serial.print(" mW/cm^2 ");
//  Serial.print("Red: ");
//  Serial.println();

  delay(100);
  
  



  //loopBlink();
  //loopAnimation();


  // If soil moisture is less than the lower threshold activate the breathe animation
  // ,if above the high threshold active the blink animation
  if (soilMoisture < mThresholdLow) {
    animBreathe();
  }
  else if (soilMoisture > mThresholdHigh) {
    animColourWheel();
  }

}


// takes the average reading on the given pin and returns that average.
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for (int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return (runningValue);

}

// Map function in Arudino but for floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loopBlink()
{
  // prepare colours (does not actually change the LED colours yet)
  leds.setPixelColor(0, leds.Color(255, 0, 0)); // first  LED red
  leds.setPixelColor(1, leds.Color(0, 255, 0)); // second LED green
  leds.setPixelColor(2, leds.Color(0, 0, 255)); // third  LED blue
  leds.show(); // send the updated pixel colours to the LEDs
  delay(1000);

  // and a bit darker
  leds.setPixelColor(0, leds.Color(100, 0, 0)); // first  LED red
  leds.setPixelColor(1, leds.Color(0, 100, 0)); // second LED green
  leds.setPixelColor(2, leds.Color(0, 0, 100)); // third  LED blue
  leds.show(); // send the updated pixel colours to the LEDs
  delay(1000);

}
