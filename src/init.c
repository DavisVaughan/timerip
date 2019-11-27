#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP time_year(SEXP);
extern SEXP time_month(SEXP x);
extern SEXP time_second(SEXP x);
extern SEXP time_minute(SEXP x);
extern SEXP time_hour(SEXP x);
extern SEXP time_mday(SEXP x);
extern SEXP time_wday(SEXP x);
extern SEXP time_yday(SEXP x);
extern SEXP timerip_class_type(SEXP x);

// Defined below
SEXP timerip_init_library(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"timerip_year",         (DL_FUNC) &time_year, 1},
  {"timerip_month",        (DL_FUNC) &time_month, 1},
  {"timerip_second",       (DL_FUNC) &time_second, 1},
  {"timerip_minute",       (DL_FUNC) &time_minute, 1},
  {"timerip_hour",         (DL_FUNC) &time_hour, 1},
  {"timerip_mday",         (DL_FUNC) &time_mday, 1},
  {"timerip_wday",         (DL_FUNC) &time_wday, 1},
  {"timerip_yday",         (DL_FUNC) &time_yday, 1},
  {"timerip_class_type",   (DL_FUNC) &timerip_class_type, 1},
  {"timerip_init_library", (DL_FUNC) &timerip_init_library, 1},
  {NULL, NULL, 0}
};

void R_init_timerip(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  R_RegisterCCallable("timerip", "time_year", (DL_FUNC) &time_year);
}

void timerip_init_utils(SEXP ns);

SEXP timerip_init_library(SEXP ns) {
  timerip_init_utils(ns);
  return R_NilValue;
}
