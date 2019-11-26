#' Extract the month from a date or datetime
#'
#' `time_month()` extracts the month from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the year from.
#'
#' @return An integer vector the same size as `x` containing the months. `1`
#'   aligns with January, and `12` is December.
#' @export
#' @examples
#' x <- as.Date("2019-01-01")
#' time_month(x)
#'
#' # Identical dates, but in different months
#' a <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' b <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(a), as.numeric(b))
#'
#' time_month(a)
#' time_month(b)
time_month <- function(x) {
  .Call(timewarp_month, x)
}
