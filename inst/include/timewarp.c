#include "timewarp.h"

SEXP (*warp_year)(SEXP) = NULL;

void timewarp_init_api() {
  warp_year = (SEXP (*)(SEXP)) R_GetCCallable("timewarp", "warp_year");
}
