#ifndef TIMEWARP_UTILS_H
#define TIMEWARP_UTILS_H

#include "timewarp.h"

void never_reached(const char* fn) __attribute__((noreturn));

enum timewarp_class_type {
  timewarp_class_date,
  timewarp_class_posixct,
  timewarp_class_posixlt,
  timewarp_class_unknown
};

enum timewarp_class_type warp_class_type(SEXP x);

int is_utc(SEXP x, int* needs_tz_reset, char* old_system_tz);

#endif
