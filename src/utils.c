#include "utils.h"

inline void never_reached(const char* fn) {
  Rf_error("Internal error in `%s()`: Reached the unreachable.", fn);
}

static enum timewarp_class_type warp_class_type_impl(SEXP klass);

enum timewarp_class_type warp_class_type(SEXP x) {
  if (!OBJECT(x)) {
    return timewarp_class_unknown;
  }

  SEXP klass = PROTECT(Rf_getAttrib(x, R_ClassSymbol));
  enum timewarp_class_type type = warp_class_type_impl(klass);

  UNPROTECT(1);
  return type;
}

static enum timewarp_class_type warp_class_type_impl(SEXP klass) {
  int n = Rf_length(klass);
  SEXP const* p_klass = STRING_PTR(klass);

  p_klass += n - 2;
  SEXP butlast = *p_klass++;
  SEXP last = *p_klass++;

  if (last == Rf_mkChar("Date")) {
    return timewarp_class_date;
  }

  if (last == Rf_mkChar("POSIXt")) {
    if (butlast == Rf_mkChar("POSIXlt")) {
      return timewarp_class_posixlt;
    } else if (butlast == Rf_mkChar("POSIXct")) {
      return timewarp_class_posixct;
    }
  }

  return timewarp_class_unknown;
}

static const char* class_type_as_str(enum timewarp_class_type type) {
  switch (type) {
  case timewarp_class_date: return "date";
  case timewarp_class_posixct: return "posixct";
  case timewarp_class_posixlt: return "posixlt";
  case timewarp_class_unknown: return "unknown";
  }
  never_reached("class_type_as_str");
}

// [[ register() ]]
SEXP timewarp_class_type(SEXP x) {
  return Rf_mkString(class_type_as_str(warp_class_type(x)));
}

// -----------------------------------------------------------------------------

int is_utc(SEXP x, int* needs_tz_reset, char* old_system_tz) {
  int n_prot = 0;
  int utc = 0;

  const char* chr_tz;
  SEXP x_tzone = Rf_getAttrib(x, Rf_install("tzone"));

  if (x_tzone == R_NilValue) {
    chr_tz = "";
  } else {
    if (TYPEOF(x_tzone) != STRSXP || Rf_length(x_tzone) != 1) {
      Rf_errorcall(R_NilValue, "`tzone` attribute must be a string or `NULL`.");
    }

    chr_tz = CHAR(STRING_ELT(x_tzone, 0));
  }

  // Missing tzone
  if(strlen(chr_tz) == 0) {
    // Do a direct look up here as this does not otherwise work on Windows
    char *chr_system_tz = getenv("TZ");

    // If a system time zone is set, make a copy to prevent overwriting it
    // by accident and then assign it to `chr_tzone`
    if(chr_system_tz) {
      x_tzone = PROTECT_N(Rf_mkString(chr_system_tz), &n_prot);
      chr_tz = CHAR(STRING_ELT(x_tzone, 0));
    }
  }

  if(strcmp(chr_tz, "GMT") == 0 || strcmp(chr_tz, "UTC") == 0) {
    utc = 1;
  };

  if(!utc && strlen(chr_tz) > 0) {
    *needs_tz_reset = set_tz(chr_tz, old_system_tz);
  }
  else {
    // To get the system timezone recorded
    R_tzsetwall();
  }

  UNPROTECT(n_prot);
  return utc;
}
