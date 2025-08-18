#include "time_format.h"

String formatTimeHM(unsigned long unixTime, int timezoneOffset) {
  unixTime += timezoneOffset;
  int hours = (unixTime % 86400) / 3600;
  int minutes = (unixTime % 3600) / 60;
  char buf[6];
  sprintf(buf, "%02d:%02d", hours, minutes);
  return String(buf);
}
