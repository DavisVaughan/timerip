#' Extract the day of the year from a date or datetime
#'
#' `time_mday()` extracts the day of the year from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the day of the year from.
#'
#' @return An integer vector the same size as `x` containing the day of the
#'   year values.
#' @export
#' @examples
#' # Identical dates, but in different days of the year
#' x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(x), as.numeric(y))
#'
#' time_yday(x)
#' time_yday(y)
time_yday <- function(x) {
  .Call(timerip_yday, x)
}
