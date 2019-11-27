#include "timerip.h"

SEXP (*rip_year)(SEXP) = NULL;

void timerip_init_api() {
  rip_year = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_year");
}
