#ifndef TIMERIP_H
#define TIMERIP_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP (*rip_year)(SEXP);

void timerip_init_api();

#endif
