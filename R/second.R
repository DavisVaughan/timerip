#' Extract the seconds from a date or datetime
#'
#' `time_second()` extracts the seconds from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the seconds from.
#'
#' @return A double vector the same size as `x` containing the seconds.
#' @export
#' @examples
#' x <- as.POSIXct("2019-01-01 00:00:05", "UTC")
#' time_second(x)
time_second <- function(x) {
  .Call(timewarp_second, x)
}
