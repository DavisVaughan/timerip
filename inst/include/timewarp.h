#ifndef TIMERIP_H
#define TIMERIP_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP (*rip_year)(SEXP);
SEXP (*rip_month)(SEXP);
SEXP (*rip_second)(SEXP);
SEXP (*rip_minute)(SEXP);
SEXP (*rip_hour)(SEXP);
SEXP (*rip_mday)(SEXP);
SEXP (*rip_wday)(SEXP);
SEXP (*rip_yday)(SEXP);

void timerip_init_api();

#endif
