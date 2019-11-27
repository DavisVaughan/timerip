#include "timerip.h"

SEXP (*rip_year)(SEXP) = NULL;
SEXP (*rip_month)(SEXP) = NULL;
SEXP (*rip_second)(SEXP) = NULL;
SEXP (*rip_minute)(SEXP) = NULL;
SEXP (*rip_hour)(SEXP) = NULL;
SEXP (*rip_mday)(SEXP) = NULL;
SEXP (*rip_wday)(SEXP) = NULL;
SEXP (*rip_yday)(SEXP) = NULL;
SEXP (*rip_info)(SEXP) = NULL;

void timerip_init_api() {
  rip_year = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_year");
  rip_month = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_month");
  rip_second = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_second");
  rip_minute = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_minute");
  rip_hour = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_hour");
  rip_mday = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_mday");
  rip_wday = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_wday");
  rip_yday = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_yday");
  rip_info = (SEXP (*)(SEXP)) R_GetCCallable("timerip", "rip_info");
}
