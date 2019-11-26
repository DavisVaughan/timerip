#include <R.h>
#include <Rinternals.h>

// Pulled straight from `src/main/util.c`
// This is always used when `USE_INTERNAL_MKTIME` is defined rather than the one
// in `src/extra/tzone/registryTZ.c` which is used for Windows otherwise
// https://github.com/wch/r-source/blob/e1fdc8473d9dae7f012b02c07600f699a585438f/src/main/util.c#L1045

const char *getTZinfo(void) {
  static char def_tz[PATH_MAX+1] = "";
  if (def_tz[0]) return def_tz;

  // call Sys.timezone()
  SEXP expr = PROTECT(install("Sys.timezone"));
  SEXP call = PROTECT(lang1(expr));
  SEXP ans = PROTECT(eval(call, R_GlobalEnv));
  if(TYPEOF(ans) == STRSXP && LENGTH(ans) == 1) {
    SEXP el = STRING_ELT(ans, 0);
    if (el != NA_STRING) {
      strcpy(def_tz, CHAR(el));
      // printf("tz is %s\n", CHAR(el));
      UNPROTECT(3);
      return def_tz;
    }
  }
  UNPROTECT(3);
  warning("system timezone name is unknown: set environment variable TZ");
  strcpy(def_tz, "unknown");  // code will then use TZDEFAULT, which is "UTC"
  return def_tz;
}
