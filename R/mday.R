#' Extract the day of the month from a date or datetime
#'
#' `time_mday()` extracts the day of the month from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the day of the month from.
#'
#' @return An integer vector the same size as `x` containing the day of the
#'   month values.
#' @export
#' @examples
#' # Identical dates, but in different hours
#' x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(x), as.numeric(y))
#'
#' time_mday(x)
#' time_mday(y)
time_mday <- function(x) {
  .Call(timerip_mday, x)
}
