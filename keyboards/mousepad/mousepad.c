#include "analog.c"
#include "mousepad.h"
#include "pincontrol.h"
#include "pointing_device.h"
#include "print.h"
#include "report.h"
#include "timer.h"

float deadZone = 0.1;

int maxCursorSpeed = 10;
int maxScrollSpeed = 10;

int minAxisValue = 0;
int maxAxisValue = 1023;

int hPolarity = -1;
int vPolarity = -1;
int xPolarity = 1;
int yPolarity = 1;

int scrollTimeout = 50;

// int hPin = 11;
// int vPin = 9;
// int xPin = 2;
// int yPin = 3;

int hPin = A6;
int vPin = A7;
int xPin = A3;
int yPin = A2;

int hOrigin, vOrigin, xOrigin, yOrigin;

uint16_t lastPrint = 0;
uint16_t lastScroll = 0;

float axisPercentage(int pin, int origin) {
    int direction;
    int distanceFromOrigin;
    int range;

    int position = analogRead(pin);

    if (origin == position) {
      return 0;
    }
    else if (origin > position) {
      distanceFromOrigin = origin - position;
      range = origin - minAxisValue;
      direction = -1;
    }
    else {
      distanceFromOrigin = position - origin;
      range = maxAxisValue - origin;
      direction = 1;
    }
    range = range * (1 - deadZone);

    float axisPercent = ((float)distanceFromOrigin / range);
    if (axisPercent < deadZone) {
      return 0;
    }
    else {
      return (axisPercent - deadZone) * direction;
    }
}

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
  return (int)(axisPercentage(pin, origin) * maxSpeed * polarity);
}

void pointing_device_task(void){
  report_mouse_t report;

  // if (timer_elapsed(lastPrint) > 1000) {
  //   lastPrint = timer_read();
  //   print_dec(analogRead(xPin));
  //   println();
  //   print_dec(analogRead(yPin));
  //   println();
  //   println("----------");
  // }

  if (timer_elapsed(lastScroll) > scrollTimeout) {
    lastScroll = timer_read();
    report.h = axisToMouseComponent(hPin, hOrigin, maxScrollSpeed, hPolarity);
    report.v = axisToMouseComponent(vPin, vOrigin, maxScrollSpeed, vPolarity);
  }
  else {
    report.h = 0;
    report.v = 0;
  }
  report.x = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
  report.y = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  timer_init();
  hOrigin = analogRead(hPin);
  vOrigin = analogRead(vPin);
  xOrigin = analogRead(xPin);
  yOrigin = analogRead(yPin);
}
