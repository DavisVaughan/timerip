#include "timewarp.h"
#include "utils.h"

#define TIMEWARP_YEAR_OFFSET 1900
#define TIMEWARP_SECONDS_IN_DAY 86400

#define DATE_TIME_YEAR(CTYPE, CONST_DEREF) {                   \
  const CTYPE* p_x = CONST_DEREF(x);                           \
                                                               \
  for(R_xlen_t i = 0; i < size; i++) {                         \
    stm tm;                                                    \
    stm* p_tm = &tm;                                           \
                                                               \
    double elt = p_x[i] * TIMEWARP_SECONDS_IN_DAY;             \
                                                               \
    bool valid;                                                \
                                                               \
    if(R_FINITE(elt)) {                                        \
      p_tm = localtime0(&elt, false, &tm);                     \
      valid = (p_tm != NULL);                                  \
    } else {                                                   \
      valid = false;                                           \
    };                                                         \
                                                               \
    if (!valid) {                                              \
      p_out[i] = NA_INTEGER;                                   \
      continue;                                                \
    }                                                          \
                                                               \
    p_out[i] = p_tm->tm_year + TIMEWARP_YEAR_OFFSET;           \
  }                                                            \
}

static SEXP date_time_year(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_out = INTEGER(out);

  switch (TYPEOF(x)) {
  case INTSXP: DATE_TIME_YEAR(int, INTEGER_RO); break;
  case REALSXP: DATE_TIME_YEAR(double, REAL_RO); break;
  default: Rf_errorcall(R_NilValue, "Unknown `Date` type %s.", Rf_type2char(TYPEOF(x)));
  }

  UNPROTECT(1);
  return out;
}

static SEXP posixct_time_year(SEXP x) {
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

// Rely on the warning in `?as.POSIXlt()` that the components of POSIXlt
// objects are always in the correct order
static SEXP posixlt_time_year(SEXP x) {
  SEXP out = VECTOR_ELT(x, 5);

  if (TYPEOF(out) != INTSXP) {
    Rf_errorcall(R_NilValue, "The 6th element of `x` must be an integer vector.");
  }

  out = PROTECT(r_maybe_duplicate(out));
  int* p_out = INTEGER(out);

  R_xlen_t size = Rf_xlength(out);

  for (R_xlen_t i = 0; i < size; ++i, ++p_out) {
    *p_out += TIMEWARP_YEAR_OFFSET;
  }

  UNPROTECT(1);
  return out;
}

// [[ register() ]]
SEXP time_year(SEXP x) {
  switch (time_class_type(x)) {
  case timewarp_class_date: return date_time_year(x);
  case timewarp_class_posixct: return posixct_time_year(x);
  case timewarp_class_posixlt: return posixlt_time_year(x);
  default: Rf_errorcall(R_NilValue, "Unknown object with type, %s.", Rf_type2char(TYPEOF(x)));
  }
}

#undef TIMEWARP_YEAR_OFFSET
#undef TIMEWARP_SECONDS_IN_DAY

// -----------------------------------------------------------------------------

// This approach is based on `D2POSIXlt()`, but is much slower than going through
// `localtime0()`

// static const int days_in_month[12] =
//   {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//
// #define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)
// #define days_in_year(year) (isleap(year) ? 366 : 365)
//
// static SEXP date_warp_year2(SEXP x) {
//   R_xlen_t size = Rf_xlength(x);
//
//   SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
//   int* p_out = INTEGER(out);
//
//   // Think about INTEGER() dates
//   double* p_x = REAL(x);
//
//   for (R_xlen_t i = 0; i < size; ++i) {
//     int day = (int) p_x[i];
//     int year = 1970;
//
//     if (day >= 0) {
//       int n_days_in_year = days_in_year(year);
//
//       while(day >= n_days_in_year) {
//         day -= n_days_in_year;
//         ++year;
//         n_days_in_year = days_in_year(year);
//       }
//     } else {
//       while(day < 0) {
//         --year;
//         day += days_in_year(year);
//       }
//     }
//
//     p_out[i] = year;
//   }
//
//   UNPROTECT(1);
//   return out;
// }
