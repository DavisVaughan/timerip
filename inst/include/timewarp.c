#include "timerip.h"

SEXP (*time_year)(SEXP) = NULL;

void timerip_init_api() {
  time_year = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "time_year");
}
