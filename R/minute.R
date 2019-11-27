#' Extract the minutes from a date or datetime
#'
#' `rip_minute()` extracts the minutes from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the minutes from.
#'
#' @return An integer vector the same size as `x` containing the minutes.
#' @export
#' @examples
#' x <- as.POSIXct("1969-12-31 19:05:00", tz = "America/New_York")
#' rip_minute(x)
rip_minute <- function(x) {
  .Call(timerip_minute, x)
}
