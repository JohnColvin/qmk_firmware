#include "mousepad.h"
#include "pointing_device.h"
#include "report.h"

void pointing_device_task(void){
  report_mouse_t currentReport = {};

  pointing_device_set_report(currentReport);

  pointing_device_send();
}

void matrix_init_kb(void) {}
