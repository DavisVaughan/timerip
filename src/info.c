#include "timerip.h"
#include "utils.h"

// -----------------------------------------------------------------------------

static SEXP date_rip_info(SEXP x);
static SEXP posixct_rip_info(SEXP x);
static SEXP posixlt_rip_info(SEXP x);

// [[ register() ]]
SEXP rip_info(SEXP x) {
  switch (time_class_type(x)) {
  case timerip_class_date: return date_rip_info(x);
  case timerip_class_posixct: return posixct_rip_info(x);
  case timerip_class_posixlt: return posixlt_rip_info(x);
  default: Rf_errorcall(R_NilValue, "Unknown object with type, %s.", Rf_type2char(TYPEOF(x)));
  }
}

// -----------------------------------------------------------------------------

static void set_info_names(SEXP x) {
  SEXP names = PROTECT(Rf_allocVector(STRSXP, 8));

  SET_STRING_ELT(names, 0, strings_second);
  SET_STRING_ELT(names, 1, strings_minute);
  SET_STRING_ELT(names, 2, strings_hour);
  SET_STRING_ELT(names, 3, strings_mday);
  SET_STRING_ELT(names, 4, strings_month);
  SET_STRING_ELT(names, 5, strings_year);
  SET_STRING_ELT(names, 6, strings_wday);
  SET_STRING_ELT(names, 7, strings_yday);

  Rf_setAttrib(x, R_NamesSymbol, names);

  UNPROTECT(1);
}

// -----------------------------------------------------------------------------

#define DATE_RIP_INFO(CTYPE, CONST_DEREF) {                      \
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
      p_out_second[i] = NA_REAL;                                 \
      p_out_minute[i] = NA_INTEGER;                              \
      p_out_hour[i] = NA_INTEGER;                                \
      p_out_mday[i] = NA_INTEGER;                                \
      p_out_month[i] = NA_INTEGER;                               \
      p_out_year[i] = NA_INTEGER;                                \
      p_out_wday[i] = NA_INTEGER;                                \
      p_out_yday[i] = NA_INTEGER;                                \
      continue;                                                  \
    }                                                            \
                                                                 \
    p_out_second[i] = 0.0;                                       \
    p_out_minute[i] = 0;                                         \
    p_out_hour[i] = 0;                                           \
    p_out_mday[i] = p_tm->tm_mday;                               \
    p_out_month[i] = p_tm->tm_mon + 1;                           \
    p_out_year[i] = p_tm->tm_year + TIMERIP_YEAR_OFFSET;         \
    p_out_wday[i] = p_tm->tm_wday;                               \
    p_out_yday[i] = p_tm->tm_yday + 1;                           \
  }                                                              \
}

static SEXP date_rip_info(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out_second = PROTECT(Rf_allocVector(REALSXP, size));
  SEXP out_minute = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_hour = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_mday = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_month = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_year = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_wday = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_yday = PROTECT(Rf_allocVector(INTSXP, size));

  double* p_out_second = REAL(out_second);
  int* p_out_minute = INTEGER(out_minute);
  int* p_out_hour = INTEGER(out_hour);
  int* p_out_mday = INTEGER(out_mday);
  int* p_out_month = INTEGER(out_month);
  int* p_out_year = INTEGER(out_year);
  int* p_out_wday = INTEGER(out_wday);
  int* p_out_yday = INTEGER(out_yday);

  switch (TYPEOF(x)) {
  case INTSXP: DATE_RIP_INFO(int, INTEGER_RO); break;
  case REALSXP: DATE_RIP_INFO(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `Date` type %s.", Rf_type2char(TYPEOF(x)));
  }

  SEXP out = PROTECT(Rf_allocVector(VECSXP, 8));

  SET_VECTOR_ELT(out, 0, out_second);
  SET_VECTOR_ELT(out, 1, out_minute);
  SET_VECTOR_ELT(out, 2, out_hour);
  SET_VECTOR_ELT(out, 3, out_mday);
  SET_VECTOR_ELT(out, 4, out_month);
  SET_VECTOR_ELT(out, 5, out_year);
  SET_VECTOR_ELT(out, 6, out_wday);
  SET_VECTOR_ELT(out, 7, out_yday);

  set_info_names(out);

  UNPROTECT(9);
  return out;
}

#undef DATE_RIP_INFO

// -----------------------------------------------------------------------------

#define POSIXCT_RIP_INFO(CTYPE, CONST_DEREF) {                     \
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
      p_out_second[i] = NA_REAL;                                   \
      p_out_minute[i] = NA_INTEGER;                                \
      p_out_hour[i] = NA_INTEGER;                                  \
      p_out_mday[i] = NA_INTEGER;                                  \
      p_out_month[i] = NA_INTEGER;                                 \
      p_out_year[i] = NA_INTEGER;                                  \
      p_out_wday[i] = NA_INTEGER;                                  \
      p_out_yday[i] = NA_INTEGER;                                  \
      continue;                                                    \
    }                                                              \
                                                                   \
    p_out_second[i] = 0.0;                                         \
    p_out_minute[i] = 0;                                           \
    p_out_hour[i] = 0;                                             \
    p_out_mday[i] = p_tm->tm_mday;                                 \
    p_out_month[i] = p_tm->tm_mon + 1;                             \
    p_out_year[i] = p_tm->tm_year + TIMERIP_YEAR_OFFSET;           \
    p_out_wday[i] = p_tm->tm_wday;                                 \
    p_out_yday[i] = p_tm->tm_yday + 1;                             \
  }                                                                \
}

static SEXP posixct_rip_info(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out_second = PROTECT(Rf_allocVector(REALSXP, size));
  SEXP out_minute = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_hour = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_mday = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_month = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_year = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_wday = PROTECT(Rf_allocVector(INTSXP, size));
  SEXP out_yday = PROTECT(Rf_allocVector(INTSXP, size));

  double* p_out_second = REAL(out_second);
  int* p_out_minute = INTEGER(out_minute);
  int* p_out_hour = INTEGER(out_hour);
  int* p_out_mday = INTEGER(out_mday);
  int* p_out_month = INTEGER(out_month);
  int* p_out_year = INTEGER(out_year);
  int* p_out_wday = INTEGER(out_wday);
  int* p_out_yday = INTEGER(out_yday);

  const char* tz = tz_get(x);
  bool utc = tz_is_utc(tz);
  int needs_system_tz_set = tz_needs_system_env_set(tz, utc);
  char old_system_tz[1001] = "";

  if (needs_system_tz_set) {
    needs_system_tz_set = set_tz(tz, old_system_tz);
  }

  switch (TYPEOF(x)) {
  case INTSXP: POSIXCT_RIP_INFO(int, INTEGER_RO); break;
  case REALSXP: POSIXCT_RIP_INFO(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `POSIXct` type %s.", Rf_type2char(TYPEOF(x)));
  }

  if(needs_system_tz_set) {
    reset_tz(old_system_tz);
  }

  SEXP out = PROTECT(Rf_allocVector(VECSXP, 8));

  SET_VECTOR_ELT(out, 0, out_second);
  SET_VECTOR_ELT(out, 1, out_minute);
  SET_VECTOR_ELT(out, 2, out_hour);
  SET_VECTOR_ELT(out, 3, out_mday);
  SET_VECTOR_ELT(out, 4, out_month);
  SET_VECTOR_ELT(out, 5, out_year);
  SET_VECTOR_ELT(out, 6, out_wday);
  SET_VECTOR_ELT(out, 7, out_yday);

  set_info_names(out);

  UNPROTECT(9);
  return out;
}

#undef POSIXCT_RIP_INFO

// -----------------------------------------------------------------------------

// Rely on the warning in `?as.POSIXlt()` that the components of POSIXlt
// objects are always in the correct order
static SEXP posixlt_rip_info(SEXP x) {
  if (TYPEOF(x) != VECSXP) {
    Rf_errorcall(R_NilValue, "Corrupt POSIXlt object. Must be a list.");
  }

  if (Rf_length(x) < 8) {
    Rf_errorcall(R_NilValue, "Corrupt POSIXlt object. Length must be at least 8.");
  }

  SEXP out_second = VECTOR_ELT(x, 0);
  SEXP out_minute = VECTOR_ELT(x, 1);
  SEXP out_hour = VECTOR_ELT(x, 2);
  SEXP out_mday = VECTOR_ELT(x, 3);
  SEXP out_month = VECTOR_ELT(x, 4);
  SEXP out_year = VECTOR_ELT(x, 5);
  SEXP out_wday = VECTOR_ELT(x, 6);
  SEXP out_yday = VECTOR_ELT(x, 7);

  if (TYPEOF(out_second) != REALSXP) {
    Rf_errorcall(R_NilValue, "Element 1 of `x` must be a double vector.");
  }

  for (int i = 1; i < 8; ++i) {
    if (TYPEOF(VECTOR_ELT(x, i)) != INTSXP) {
      Rf_errorcall(R_NilValue, "Element %i of `x` must be an integer vector.", i + 1);
    }
  }

  out_month = PROTECT(r_maybe_duplicate(out_month));
  out_year = PROTECT(r_maybe_duplicate(out_year));
  out_yday = PROTECT(r_maybe_duplicate(out_yday));

  int* p_out_month = INTEGER(out_month);
  int* p_out_year = INTEGER(out_year);
  int* p_out_yday = INTEGER(out_yday);

  R_xlen_t size = Rf_xlength(out_month);

  for (R_xlen_t i = 0; i < size; ++i) {
    p_out_month[i]++;
    p_out_year[i] += TIMERIP_YEAR_OFFSET;
    p_out_yday[i]++;
  }

  SEXP out = PROTECT(Rf_allocVector(VECSXP, 8));

  SET_VECTOR_ELT(out, 0, out_second);
  SET_VECTOR_ELT(out, 1, out_minute);
  SET_VECTOR_ELT(out, 2, out_hour);
  SET_VECTOR_ELT(out, 3, out_mday);
  SET_VECTOR_ELT(out, 4, out_month);
  SET_VECTOR_ELT(out, 5, out_year);
  SET_VECTOR_ELT(out, 6, out_wday);
  SET_VECTOR_ELT(out, 7, out_yday);

  set_info_names(out);

  UNPROTECT(4);
  return out;
}

