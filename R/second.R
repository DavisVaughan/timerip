#' Extract the seconds from a date or datetime
#'
#' `rip_second()` extracts the seconds from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the seconds from.
#'
#' @return A double vector the same size as `x` containing the seconds.
#' @export
#' @examples
#' x <- as.POSIXct("2019-01-01 00:00:05", "UTC")
#' rip_second(x)
rip_second <- function(x) {
  .Call(timerip_second, x)
}
