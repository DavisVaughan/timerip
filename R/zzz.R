# nocov start
.onLoad <- function(libname, pkgname) {
  .Call(timerip_init_library, asNamespace("timerip"))
}
# nocov end
