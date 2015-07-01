#include <ICSC.h>
#include <Adafruit_NeoPixel.h>

#define PIN 9
#define PIXEL_COUNT 150
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel onBoards = Adafruit_NeoPixel(2, A1, NEO_GRB + NEO_KHZ800);

int station = 0;

bool pacerRunning = false;
int pacerPosition = 0;
int startPosition = 0   + (150 * station);
int endPosition   = 149 + (150 * station);

bool toggle = true;

void setup()
{
  strip.begin();
  onBoards.begin();
  ICSC.begin(station, 115200, &Serial, 2);
  ICSC.registerCommand('S', &stateChange);

  strip.show();

  onBoards.setPixelColor(0, 0, 10, 10);
  onBoards.setPixelColor(1, 0, 10, 10);
  onBoards.show();
}

void loop()
{
  if (pacerRunning) {
    setAllOff();

    if (startPosition < pacerPosition && pacerPosition < endPosition) {
      strip.setPixelColor(pacerPosition - (150 * station), 30, 0, 30);
    }

    strip.show();
  }
}

void setAllOff() {
  for (int i=0; i<PIXEL_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
}

void stateChange(unsigned char src, char command, unsigned char len, char *data) {
  if (toggle) {
    toggle = false;
    onBoards.setPixelColor(0, 0, 10, 10);
    onBoards.setPixelColor(1, 0, 10, 10);
  } else {
    toggle = true;
    onBoards.setPixelColor(0, 0, 0, 0);
    onBoards.setPixelColor(1, 0, 0, 0);
  }
  onBoards.show();
  pacerRunning = true;
  pacerPosition = atoi(data);
}
