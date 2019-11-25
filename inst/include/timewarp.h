#ifndef TIMEWARP_H
#define TIMEWARP_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP (*warp_year)(SEXP);

void timewarp_init_api();

#endif
