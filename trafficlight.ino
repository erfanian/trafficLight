#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);
int dataSize = 7;
char sentData[7];
int sentNumbers[7];
unsigned long time = millis();
unsigned long timeout = 1800000;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  while (not Serial.available()) {
    if(sentNumbers[0] == 1) {
      allOn();
    }else {
      if(sentNumbers[1] == 1) {
        allOff();
      }
      if(sentNumbers[2] == 1) {
        setRed(255);
      }
      if(sentNumbers[2] == 0) {
        setRed(0);
      }
      if(sentNumbers[3] == 1) {
        setYellow(255);
      }
      if(sentNumbers[3] == 0) {
        setYellow(0);
      }
      if(sentNumbers[4] == 1) {
        setGreen(255);
      }
      if(sentNumbers[4] == 0) {
        setGreen(0);
      }
      if(sentNumbers[5] == 1) {
        upAndDown();
      }
      if(sentNumbers[6] == 1) {
        allFade(0);
      }
    }
    
    int arraySize = 0;
    unsigned long time_difference = millis() - time;
    for(int i=0;i<dataSize;i++) {
      arraySize += sentNumbers[i];
    }
    if(arraySize == 0) {
      allBlink();
    }else if(time_difference > timeout) {
      for(int i=0;i<dataSize;i++) {
        sentData[i] = 0;
        sentNumbers[i] = 0;
      }
    }
  }

  while (Serial.available()) {
    Serial.readBytesUntil('\n', sentData, dataSize);
    Serial.println("Received: ");
    Serial.println(sentData);
    time = millis();
   
    for(int i=0;i<dataSize;i++) {
      sentNumbers[i] = sentData[i] - '0';
    }
  }

}


void setRed(uint8_t intensity) {
  strip.setPixelColor(2, strip.Color(intensity, 0, 0)); // Red
  strip.show();
}

void setYellow(uint8_t intensity) {
  strip.setPixelColor(1, strip.Color(intensity, intensity, 0)); // Yellow
  strip.show();
}

void setGreen(uint8_t intensity) {
  strip.setPixelColor(0, strip.Color(0, intensity, 0)); // Green
  strip.show();
}

void allOff() {
  setRed(0);
  setYellow(0);
  setGreen(0);
}

void allOn() {
  setRed(255);
  setYellow(255);
  setGreen(255);
}

void allBlink() {
  allOn();
  delay(1000);
  allOff();
  delay(1000);
}

void upAndDown() {
  allOff();
  setGreen(255);
  delay(500);
  allOff();
  setYellow(255);
  delay(500);
  allOff();
  setRed(255);
  delay(500);
  allOff();
  setYellow(255);
  delay(500);
}

void allFade(uint8_t intensity) {
  allOff();
  uint8_t start_intensity = intensity;
  uint8_t bit_switch = 1;
  for(intensity>=start_intensity; intensity += bit_switch;) {
    setRed(intensity);
    setYellow(intensity);
    setGreen(intensity);
    if (intensity == 255) bit_switch = -1;
    delay(10);
  }
}
