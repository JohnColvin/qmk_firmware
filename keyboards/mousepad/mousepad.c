#include "analog.c"
#include <math.h>
#include "mousepad.h"
#include "pincontrol.h"
#include "pointing_device.h"
#include "print.h"
#include "report.h"
#include "timer.h"

// TODO dead zone
// float deadZone = 10;

int maxCursorSpeed = 6;
int maxScrollSpeed = 5;

int precisionSpeed = 1;
int precisionThreshold = 95;

int minAxisValue = 0;
int maxAxisValue = 1023;

int hPolarity = -1;
int vPolarity = -1;
int xPolarity = 1;
int yPolarity = 1;

int scrollTimeout = 50;
int cursorTimeout = 10;

// int hPin = 11;
// int vPin = 9;
// int xPin = 2;
// int yPin = 3;

int hPin = A6;
int vPin = A7;
int xPin = A3;
int yPin = A2;

int hOrigin, vOrigin, xOrigin, yOrigin;

uint16_t lastCursor = 0;
uint16_t lastPrint = 0;
uint16_t lastScroll = 0;

int axisCoordinate(int pin, int origin) {
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

    float percent = (float)distanceFromOrigin / range;
    int coordinate = (int)(percent * 100);
    if (coordinate < 0) {
      return 0;
    }
    else if (coordinate > 100) {
      return 100 * direction;
    }
    else {
      return coordinate * direction;
    }
}

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
  int coordinate = axisCoordinate(pin, origin);

  if (coordinate == 0) {
    return 0;
  }
  else {
    int direction = (coordinate < 0) ? -1 : 1;
    if (abs(coordinate) < precisionThreshold) {
      return precisionSpeed * direction * polarity;
    }
    else {
      // TODO accelerate
      return maxCursorSpeed * direction * polarity;
    }
  }
}

void pointing_device_task(void){
  report_mouse_t report;
  report.h = 0;
  report.v = 0;
  report.x = 0;
  report.y = 0;
  report.buttons = 0;

  if (timer_elapsed(lastScroll) > scrollTimeout) {
    lastScroll = timer_read();
    report.h = axisToMouseComponent(hPin, hOrigin, maxScrollSpeed, hPolarity);
    report.v = axisToMouseComponent(vPin, vOrigin, maxScrollSpeed, vPolarity);
  }

  // TODO read as one vector
  if (timer_elapsed(lastCursor) > cursorTimeout) {
    lastCursor = timer_read();
    report.x = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
    report.y = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
  }

  if ((PINF&(1<<6)) == 0) {
    report.buttons |= MOUSE_BTN1;
  }

  if ((PINC&(1<<6)) == 0) {
    report.buttons |= MOUSE_BTN2;
  }

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  timer_init();
  hOrigin = analogRead(hPin);
  vOrigin = analogRead(vPin);
  xOrigin = analogRead(xPin);
  yOrigin = analogRead(yPin);
  DDRF  &= ~(1<<6);
  PORTF |=  (1<<6);
  DDRC  &= ~(1<<6);
  PORTC |=  (1<<6);
}
