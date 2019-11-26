#' Extract the hour from a date or datetime
#'
#' `time_hour()` extracts the hour from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the hour from.
#'
#' @return An integer vector the same size as `x` containing the hours.
#' @export
#' @examples
#' # Identical dates, but in different hours
#' x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(x), as.numeric(y))
#'
#' time_hour(x)
#' time_hour(y)
time_hour <- function(x) {
  .Call(timewarp_hour, x)
}