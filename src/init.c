#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP rip_year(SEXP);
extern SEXP rip_month(SEXP x);
extern SEXP rip_second(SEXP x);
extern SEXP rip_minute(SEXP x);
extern SEXP rip_hour(SEXP x);
extern SEXP rip_mday(SEXP x);
extern SEXP rip_wday(SEXP x);
extern SEXP rip_yday(SEXP x);
extern SEXP timerip_class_type(SEXP x);

// Defined below
SEXP timerip_init_library(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"timerip_year",         (DL_FUNC) &rip_year, 1},
  {"timerip_month",        (DL_FUNC) &rip_month, 1},
  {"timerip_second",       (DL_FUNC) &rip_second, 1},
  {"timerip_minute",       (DL_FUNC) &rip_minute, 1},
  {"timerip_hour",         (DL_FUNC) &rip_hour, 1},
  {"timerip_mday",         (DL_FUNC) &rip_mday, 1},
  {"timerip_wday",         (DL_FUNC) &rip_wday, 1},
  {"timerip_yday",         (DL_FUNC) &rip_yday, 1},
  {"timerip_class_type",   (DL_FUNC) &timerip_class_type, 1},
  {"timerip_init_library", (DL_FUNC) &timerip_init_library, 1},
  {NULL, NULL, 0}
};

void R_init_timerip(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  R_RegisterCCallable("timerip", "rip_year", (DL_FUNC) &rip_year);
  R_RegisterCCallable("timerip", "rip_month", (DL_FUNC) &rip_month);
  R_RegisterCCallable("timerip", "rip_second", (DL_FUNC) &rip_second);
  R_RegisterCCallable("timerip", "rip_minute", (DL_FUNC) &rip_minute);
  R_RegisterCCallable("timerip", "rip_hour", (DL_FUNC) &rip_hour);
  R_RegisterCCallable("timerip", "rip_mday", (DL_FUNC) &rip_mday);
  R_RegisterCCallable("timerip", "rip_wday", (DL_FUNC) &rip_wday);
  R_RegisterCCallable("timerip", "rip_yday", (DL_FUNC) &rip_yday);
}

void timerip_init_utils(SEXP ns);

SEXP timerip_init_library(SEXP ns) {
  timerip_init_utils(ns);
  return R_NilValue;
}
