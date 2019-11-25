#ifndef TIMEWARP_H
#define TIMEWARP_H

// "datetime.h" comes before the R_NO_REMAP
#include "datetime.h"

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <stdbool.h>

#define PROTECT_N(x, n) (++*n, PROTECT(x))

#endif
