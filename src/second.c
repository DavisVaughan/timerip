#include "timerip.h"
#include "utils.h"

// -----------------------------------------------------------------------------

static SEXP date_time_second(SEXP x);
static SEXP posixct_time_second(SEXP x);
static SEXP posixlt_time_second(SEXP x);

// [[ register() ]]
SEXP time_second(SEXP x) {
  switch (time_class_type(x)) {
  case timerip_class_date: return date_time_second(x);
  case timerip_class_posixct: return posixct_time_second(x);
  case timerip_class_posixlt: return posixlt_time_second(x);
  default: Rf_errorcall(R_NilValue, "Unknown object with type, %s.", Rf_type2char(TYPEOF(x)));
  }
}

// -----------------------------------------------------------------------------

// After conversation with Hadley, assume that a Date should not be allowed to
// have fractional pieces, like seconds. Always return 0 or NA.

#define DATE_TIME_SECOND(CTYPE, CONST_DEREF) {                   \
  const CTYPE* p_x = CONST_DEREF(x);                             \
                                                                 \
  for(R_xlen_t i = 0; i < size; i++) {                           \
    p_out[i] = R_FINITE(p_x[i]) ? 0 : NA_REAL;                   \
  }                                                              \
}

static SEXP date_time_second(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(REALSXP, size));
  double* p_out = REAL(out);

  switch (TYPEOF(x)) {
  case INTSXP: DATE_TIME_SECOND(int, INTEGER_RO); break;
  case REALSXP: DATE_TIME_SECOND(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `Date` type %s.", Rf_type2char(TYPEOF(x)));
  }

  UNPROTECT(1);
  return out;
}

#undef DATE_TIME_SECOND

// -----------------------------------------------------------------------------

#define POSIXCT_TIME_SECOND(CTYPE, CONST_DEREF) {    \
  const CTYPE* p_x = CONST_DEREF(x);                 \
                                                     \
  for(R_xlen_t i = 0; i < size; i++) {               \
    stm tm;                                          \
    stm* p_tm = &tm;                                 \
                                                     \
    double elt = p_x[i];                             \
                                                     \
    bool valid;                                      \
                                                     \
    if(R_FINITE(elt)) {                              \
      p_tm = localtime0(&elt, !utc, &tm);            \
      valid = (p_tm != NULL);                        \
    } else {                                         \
      valid = false;                                 \
    };                                               \
                                                     \
    if (!valid) {                                    \
      p_out[i] = NA_REAL;                            \
      continue;                                      \
    }                                                \
                                                     \
    p_out[i] = p_tm->tm_sec;                         \
  }                                                  \
}

static SEXP posixct_time_second(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(REALSXP, size));
  double* p_out = REAL(out);

  const char* tz = tz_get(x);
  bool utc = tz_is_utc(tz);
  int needs_system_tz_set = tz_needs_system_env_set(tz, utc);
  char old_system_tz[1001] = "";

  if (needs_system_tz_set) {
    needs_system_tz_set = set_tz(tz, old_system_tz);
  }

  switch (TYPEOF(x)) {
  case INTSXP: POSIXCT_TIME_SECOND(int, INTEGER_RO); break;
  case REALSXP: POSIXCT_TIME_SECOND(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `POSIXct` type %s.", Rf_type2char(TYPEOF(x)));
  }

  if(needs_system_tz_set) {
    reset_tz(old_system_tz);
  }

  UNPROTECT(1);
  return out;
}

#undef POSIXCT_TIME_SECOND

// -----------------------------------------------------------------------------

// Rely on the warning in `?as.POSIXlt()` that the components of POSIXlt
// objects are always in the correct order
static SEXP posixlt_time_second(SEXP x) {
  int pos = 0;
  SEXP out = VECTOR_ELT(x, pos);

  if (TYPEOF(out) != REALSXP) {
    Rf_errorcall(R_NilValue, "Element %i of `x` must be a double vector.", pos + 1);
  }

  return out;
}

