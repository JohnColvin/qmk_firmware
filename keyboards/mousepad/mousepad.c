#include "analog.c"
#include "mousepad.h"
#include "pointing_device.h"
#include "report.h"

int hPin = 2;
int vPin = 3;
int xPin = 11;
int yPin = 9;

int cursorSensitivity = 50;
int scrollSensitivity = 200;

int hDirection = 1;
int vDirection = 1;
int xDirection = -1;
int yDirection = -1;

int hBaseline, vBaseline, xBaseline, yBaseline;

void pointing_device_task(void){
  report_mouse_t report;

  report.h = (hBaseline - analogRead(hPin)) / scrollSensitivity * hDirection;
  report.v = (vBaseline - analogRead(vPin)) / scrollSensitivity * vDirection;
  report.x = (xBaseline - analogRead(xPin)) / cursorSensitivity * xDirection;
  report.y = (yBaseline - analogRead(yPin)) / cursorSensitivity * yDirection;

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  hBaseline = analogRead(hPin);
  vBaseline = analogRead(vPin);
  xBaseline = analogRead(xPin);
  yBaseline = analogRead(yPin);
}
