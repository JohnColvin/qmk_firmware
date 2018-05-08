#include "analog.c"
#include "mousepad.h"
#include "pincontrol.h"
#include "pointing_device.h"
#include "print.h"
#include "report.h"
#include "timer.h"

int hPin = 2;
int vPin = 3;
int xPin = 11;
int yPin = 9;

// int hPin = PF4;
// int vPin = PF5;
// int xPin = PD7;
// int yPin = PD4;

int cursorSensitivity = 50;
int scrollSensitivity = 200;

int hDirection = 1;
int vDirection = 1;
int xDirection = -1;
int yDirection = -1;

int hBaseline, vBaseline, xBaseline, yBaseline;

uint16_t lastPrint = 0;

void pointing_device_task(void){
  report_mouse_t report;

  report.h = (hBaseline - analogRead(hPin)) / scrollSensitivity * hDirection;
  report.v = (vBaseline - analogRead(vPin)) / scrollSensitivity * vDirection;
  report.x = (xBaseline - analogRead(xPin)) / cursorSensitivity * xDirection;
  report.y = (yBaseline - analogRead(yPin)) / cursorSensitivity * yDirection;

  if (timer_elapsed(lastPrint) > 1000)
  for (int i = 0; i < 20; i++) {
    pinMode(i, 1);
    if (digitalRead(i)) {
      print_dec(i);
      println();
      lastPrint = timer_read();
    }
  }

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  timer_init();
  hBaseline = analogRead(hPin);
  vBaseline = analogRead(vPin);
  xBaseline = analogRead(xPin);
  yBaseline = analogRead(yPin);
}
