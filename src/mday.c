#include "timerip.h"
#include "utils.h"

// -----------------------------------------------------------------------------

static SEXP date_rip_mday(SEXP x);
static SEXP posixct_rip_mday(SEXP x);
static SEXP posixlt_rip_mday(SEXP x);

// [[ register() ]]
SEXP rip_mday(SEXP x) {
  switch (time_class_type(x)) {
  case timerip_class_date: return date_rip_mday(x);
  case timerip_class_posixct: return posixct_rip_mday(x);
  case timerip_class_posixlt: return posixlt_rip_mday(x);
  default: Rf_errorcall(R_NilValue, "Unknown object with type, %s.", Rf_type2char(TYPEOF(x)));
  }
}

// -----------------------------------------------------------------------------

#define DATE_RIP_MDAY(CTYPE, CONST_DEREF) {                      \
  const CTYPE* p_x = CONST_DEREF(x);                             \
                                                                 \
  for(R_xlen_t i = 0; i < size; i++) {                           \
    stm tm;                                                      \
    stm* p_tm = &tm;                                             \
                                                                 \
    double elt = p_x[i] * TIMERIP_SECONDS_IN_DAY;                \
                                                                 \
    bool valid;                                                  \
                                                                 \
    if(R_FINITE(elt)) {                                          \
      p_tm = localtime0(&elt, false, &tm);                       \
      valid = (p_tm != NULL);                                    \
    } else {                                                     \
      valid = false;                                             \
    };                                                           \
                                                                 \
    if (!valid) {                                                \
      p_out[i] = NA_INTEGER;                                     \
      continue;                                                  \
    }                                                            \
                                                                 \
    p_out[i] = p_tm->tm_mday;                                    \
  }                                                              \
}

static SEXP date_rip_mday(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_out = INTEGER(out);

  switch (TYPEOF(x)) {
  case INTSXP: DATE_RIP_MDAY(int, INTEGER_RO); break;
  case REALSXP: DATE_RIP_MDAY(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `Date` type %s.", Rf_type2char(TYPEOF(x)));
  }

  UNPROTECT(1);
  return out;
}

#undef DATE_RIP_MDAY

// -----------------------------------------------------------------------------

#define POSIXCT_RIP_MDAY(CTYPE, CONST_DEREF) {                     \
  const CTYPE* p_x = CONST_DEREF(x);                               \
                                                                   \
  for(R_xlen_t i = 0; i < size; i++) {                             \
    stm tm;                                                        \
    stm* p_tm = &tm;                                               \
                                                                   \
    double elt = p_x[i];                                           \
                                                                   \
    bool valid;                                                    \
                                                                   \
    if(R_FINITE(elt)) {                                            \
      p_tm = localtime0(&elt, !utc, &tm);                          \
      valid = (p_tm != NULL);                                      \
    } else {                                                       \
      valid = false;                                               \
    };                                                             \
                                                                   \
    if (!valid) {                                                  \
      p_out[i] = NA_INTEGER;                                       \
      continue;                                                    \
    }                                                              \
                                                                   \
    p_out[i] = p_tm->tm_mday;                                      \
  }                                                                \
}

static SEXP posixct_rip_mday(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_out = INTEGER(out);

  const char* tz = tz_get(x);
  bool utc = tz_is_utc(tz);
  int needs_system_tz_set = tz_needs_system_env_set(tz, utc);
  char old_system_tz[1001] = "";

  if (needs_system_tz_set) {
    needs_system_tz_set = set_tz(tz, old_system_tz);
  }

  switch (TYPEOF(x)) {
  case INTSXP: POSIXCT_RIP_MDAY(int, INTEGER_RO); break;
  case REALSXP: POSIXCT_RIP_MDAY(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `POSIXct` type %s.", Rf_type2char(TYPEOF(x)));
  }

  if(needs_system_tz_set) {
    reset_tz(old_system_tz);
  }

  UNPROTECT(1);
  return out;
}

#undef POSIXCT_RIP_MDAY

// -----------------------------------------------------------------------------

// Rely on the warning in `?as.POSIXlt()` that the components of POSIXlt
// objects are always in the correct order
static SEXP posixlt_rip_mday(SEXP x) {
  int pos = 3;
  SEXP out = VECTOR_ELT(x, pos);

  if (TYPEOF(out) != INTSXP) {
    Rf_errorcall(R_NilValue, "Element %i of `x` must be an integer vector.", pos + 1);
  }

  return out;
}
