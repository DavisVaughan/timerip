#' Extract the year from a date or datetime
#' @export
warp_year <- function(x) {
  .Call(timewarp_year, x)
}
