#include "timewarp.h"
#include "utils.h"

#define TIMEWARP_YEAR_OFFSET 1900

// [[ register() ]]
SEXP posixct_warp_year(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_out = INTEGER(out);

  double* p_x = REAL(x);

  int needs_tz_reset = 0;
  char old_system_tz[1001] = "";
  bool utc = is_utc(x, &needs_tz_reset, old_system_tz);

  for(R_xlen_t i = 0; i < size; i++) {
    stm tm;
    stm* p_tm = &tm;

    double elt = p_x[i];

    bool valid;

    /* in theory localtime/gmtime always return a valid
     struct tm pointer, but Windows uses NULL for error
     conditions (like negative times). */
    if(R_FINITE(elt)) {
      p_tm = localtime0(&elt, !utc, &tm);
      valid = (p_tm != NULL);
    } else {
      valid = false;
    };

    if (!valid) {
      p_out[i] = NA_INTEGER;
      continue;
    }

    p_out[i] = p_tm->tm_year + TIMEWARP_YEAR_OFFSET;
  }

  if(needs_tz_reset) {
    reset_tz(old_system_tz);
  }

  UNPROTECT(1);
  return out;
}

SEXP warp_year(SEXP x) {
  switch (warp_class_type(x)) {
  case timewarp_class_posixct: return posixct_warp_year(x);
  default: Rf_errorcall(R_NilValue, "Not yet implemented");
  }
}

#undef TIMEWARP_YEAR_OFFSET
