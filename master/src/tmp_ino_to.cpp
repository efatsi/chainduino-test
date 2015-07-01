#include <Arduino.h>
#include <ICSC.h>


void setup();

void loop();
#line 3 "master.ino"
int station = 5;

int stationCount = 2;
int pacerPosition = 0;

void setup()
{
ICSC.begin(station, 115200, &Serial, 2);
}

void loop()
{
for (int i = 0; i < stationCount * 150; i++) {
ICSC.broadcast('S', 5, (char*)pacerPosition);
pacerPosition += 1;

delay(200);
}
}