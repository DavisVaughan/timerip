#' Extract the year from a date or datetime
#' @export
time_year <- function(x) {
  .Call(timewarp_year, x)
}
