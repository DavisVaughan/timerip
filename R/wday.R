#' Extract the day of the week from a date or datetime
#'
#' `rip_wday()` extracts the day of the week from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the day of the week from.
#'
#' @return An integer vector the same size as `x` containing the day of the
#'   week values. Monday corresponds to `1`, and Sunday is `7`.
#' @export
#' @examples
#' # Identical dates, but in different hours
#' x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(x), as.numeric(y))
#'
#' rip_wday(x)
#' rip_wday(y)
rip_wday <- function(x) {
  .Call(timerip_wday, x)
}
