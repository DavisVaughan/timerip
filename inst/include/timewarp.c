#include "timewarp.h"

SEXP (*time_year)(SEXP) = NULL;

void timewarp_init_api() {
  time_year = (SEXP (*)(SEXP)) R_GetCCallable("timewarp", "time_year");
}
