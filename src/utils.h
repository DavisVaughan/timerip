#ifndef TIMERIP_UTILS_H
#define TIMERIP_UTILS_H

#include "timerip.h"

// -----------------------------------------------------------------------------

#define TIMERIP_YEAR_OFFSET 1900
#define TIMERIP_SECONDS_IN_DAY 86400

// -----------------------------------------------------------------------------

enum timerip_class_type {
  timerip_class_date,
  timerip_class_posixct,
  timerip_class_posixlt,
  timerip_class_unknown
};

enum timerip_class_type time_class_type(SEXP x);

// -----------------------------------------------------------------------------

const char* tz_get(SEXP x);
bool tz_is_utc(const char* tz);
int tz_needs_system_env_set(const char* tz, bool utc);

// -----------------------------------------------------------------------------

void never_reached(const char* fn) __attribute__((noreturn));

SEXP r_maybe_duplicate(SEXP x);

// -----------------------------------------------------------------------------

extern SEXP strings_posixlt;
extern SEXP strings_posixct;
extern SEXP strings_posixt;
extern SEXP strings_date;

#endif
