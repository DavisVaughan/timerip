# nocov start
.onLoad <- function(libname, pkgname) {
  .Call(timewarp_init_library, asNamespace("timewarp"))
}
# nocov end
