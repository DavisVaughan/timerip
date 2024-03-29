#' Extract the year from a date or datetime
#'
#' `rip_year()` extracts the year from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the year from.
#'
#' @return An integer vector the same size as `x` containing the years.
#' @export
#' @examples
#' x <- as.Date("2019-01-01")
#' rip_year(x)
#'
#' # Identical dates, but in different years
#' a <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' b <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(a), as.numeric(b))
#'
#' rip_year(a)
#' rip_year(b)
rip_year <- function(x) {
  .Call(timerip_year, x)
}
