#ifndef TIMEWARP_UTILS_H
#define TIMEWARP_UTILS_H

#include "timewarp.h"

// -----------------------------------------------------------------------------

#define TIMEWARP_YEAR_OFFSET 1900
#define TIMEWARP_SECONDS_IN_DAY 86400

// -----------------------------------------------------------------------------

enum timewarp_class_type {
  timewarp_class_date,
  timewarp_class_posixct,
  timewarp_class_posixlt,
  timewarp_class_unknown
};

enum timewarp_class_type time_class_type(SEXP x);

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
