#include "utils.h"

// -----------------------------------------------------------------------------

enum timerip_class_type time_class_type(SEXP x);
static enum timerip_class_type time_class_type_impl(SEXP klass);
static const char* class_type_as_str(enum timerip_class_type type);

// [[ register() ]]
SEXP timerip_class_type(SEXP x) {
  return Rf_mkString(class_type_as_str(time_class_type(x)));
}

enum timerip_class_type time_class_type(SEXP x) {
  if (!OBJECT(x)) {
    return timerip_class_unknown;
  }

  SEXP klass = PROTECT(Rf_getAttrib(x, R_ClassSymbol));
  enum timerip_class_type type = time_class_type_impl(klass);

  UNPROTECT(1);
  return type;
}

static enum timerip_class_type time_class_type_impl(SEXP klass) {
  int n = Rf_length(klass);
  SEXP const* p_klass = STRING_PTR(klass);

  p_klass += n - 2;
  SEXP butlast = *p_klass++;
  SEXP last = *p_klass++;

  if (last == strings_date) {
    return timerip_class_date;
  }

  if (last == strings_posixt) {
    if (butlast == strings_posixlt) {
      return timerip_class_posixlt;
    } else if (butlast == strings_posixct) {
      return timerip_class_posixct;
    }
  }

  return timerip_class_unknown;
}

static const char* class_type_as_str(enum timerip_class_type type) {
  switch (type) {
  case timerip_class_date: return "date";
  case timerip_class_posixct: return "posixct";
  case timerip_class_posixlt: return "posixlt";
  case timerip_class_unknown: return "unknown";
  }
  never_reached("class_type_as_str");
}

// -----------------------------------------------------------------------------

inline void never_reached(const char* fn) {
  Rf_error("Internal error in `%s()`: Reached the unreachable.", fn);
}

SEXP r_maybe_duplicate(SEXP x) {
  if (MAYBE_REFERENCED(x)) {
    return Rf_shallow_duplicate(x);
  } else {
    return x;
  }
}

// -----------------------------------------------------------------------------

// - Do a direct look up here as this does not otherwise work on Windows
// - If a system time zone is set, make a copy to prevent overwriting it,
static const char* tz_system_get() {
  const char* tz = getenv("TZ");

  // NULL pointer if TZ is not set
  if (!tz) {
    return "";
  }

  return tz;
}

const char* tz_get(SEXP x) {
  SEXP x_tzone = Rf_getAttrib(x, Rf_install("tzone"));

  if (x_tzone == R_NilValue) {
    return tz_system_get();
  }

  if (TYPEOF(x_tzone) != STRSXP || Rf_length(x_tzone) != 1) {
    Rf_errorcall(R_NilValue, "`tzone` attribute must be a string or `NULL`.");
  }

  const char* tz = CHAR(STRING_ELT(x_tzone, 0));

  if (strlen(tz) == 0) {
    return tz_system_get();
  }

  return tz;
}

bool tz_is_utc(const char* tz) {
  return strcmp(tz, "GMT") == 0 || strcmp(tz, "UTC") == 0;
}

int tz_needs_system_env_set(const char* tz, bool utc) {
  return !utc && strlen(tz) > 0;
}

// -----------------------------------------------------------------------------

SEXP strings = NULL;

SEXP strings_posixlt = NULL;
SEXP strings_posixct = NULL;
SEXP strings_posixt = NULL;
SEXP strings_date = NULL;

SEXP strings_second = NULL;
SEXP strings_minute = NULL;
SEXP strings_hour = NULL;
SEXP strings_mday = NULL;
SEXP strings_month = NULL;
SEXP strings_year = NULL;
SEXP strings_wday = NULL;
SEXP strings_yday = NULL;

// -----------------------------------------------------------------------------

void timerip_init_utils(SEXP ns) {
  // Holds the CHARSXP objects because they can be garbage collected
  strings = Rf_allocVector(STRSXP, 12);
  R_PreserveObject(strings);

  strings_posixlt = Rf_mkChar("POSIXlt");
  SET_STRING_ELT(strings, 0, strings_posixlt);

  strings_posixct = Rf_mkChar("POSIXct");
  SET_STRING_ELT(strings, 1, strings_posixct);

  strings_posixt = Rf_mkChar("POSIXt");
  SET_STRING_ELT(strings, 2, strings_posixt);

  strings_date = Rf_mkChar("Date");
  SET_STRING_ELT(strings, 3, strings_date);

  strings_second = Rf_mkChar("second");
  SET_STRING_ELT(strings, 4, strings_second);

  strings_minute = Rf_mkChar("minute");
  SET_STRING_ELT(strings, 5, strings_minute);

  strings_hour = Rf_mkChar("hour");
  SET_STRING_ELT(strings, 6, strings_hour);

  strings_mday = Rf_mkChar("mday");
  SET_STRING_ELT(strings, 7, strings_mday);

  strings_month = Rf_mkChar("month");
  SET_STRING_ELT(strings, 8, strings_month);

  strings_year = Rf_mkChar("year");
  SET_STRING_ELT(strings, 9, strings_year);

  strings_wday = Rf_mkChar("wday");
  SET_STRING_ELT(strings, 10, strings_wday);

  strings_yday = Rf_mkChar("yday");
  SET_STRING_ELT(strings, 11, strings_yday);
}
