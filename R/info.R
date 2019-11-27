#' Extract all info from a date or datetime
#'
#' `rip_info()` extracts all information from a date or datetime object.
#'
#' @param x `<Date / POSIXct / POSIXlt>`
#'
#'   The vector to extract the information from.
#'
#' @return A named list of size `8` containing the information about `x`.
#' @export
#' @examples
#' x <- as.Date("2019-01-01")
#' rip_info(x)
#'
#' # Identical dates, but in different years
#' a <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
#' b <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")
#'
#' identical(as.numeric(a), as.numeric(b))
#'
#' rip_info(a)
#' rip_info(b)
rip_info <- function(x) {
  .Call(timerip_info, x)
}
