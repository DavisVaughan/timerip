#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP warp_year(SEXP);
extern SEXP timewarp_class_type(SEXP x);

static const R_CallMethodDef CallEntries[] = {
  {"timewarp_year",       (DL_FUNC) &warp_year, 1},
  {"timewarp_class_type", (DL_FUNC) &timewarp_class_type, 1},
  {NULL, NULL, 0}
};

void R_init_timewarp(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
