# ------------------------------------------------------------------------------
# Date

test_that("can extract the hour from a Date", {
  x <- new_date(0)
  expect_identical(time_hour(x), 0L)
})

test_that("extracting hours from a fractional Date ignores the fraction", {
  x <- new_date(0.5555) # technically 8 hours
  expect_identical(time_hour(x), 0L)
})

test_that("can extract the hour from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(time_hour(x), 0L)
})

test_that("can extract the hour from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(time_hour(x), 0L)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = "Date")
  expect_error(time_hour(x), "`Date` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = "Date")
  expect_identical(time_hour(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = "Date")
  expect_identical(time_hour(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the hour from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(5000), tz = "UTC")
  expect_identical(time_hour(x), 1L)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the hour from a POSIXct in UTC", {
  expect_identical(time_hour(new_datetime_utc(5000)), 1L)
})

test_that("border times are handled correctly using their time zone", {
  x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
  y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")

  expect_identical(time_hour(x), 19L)
  expect_identical(time_hour(y), 0L)
})

test_that("border times are handled correctly using system TZ", {
  x <- new_datetime(0, tzone = "")

  expect_identical(
    with_envvar(list(TZ = "UTC"), time_hour(x)),
    0L
  )

  expect_identical(
    with_envvar(list(TZ = "America/New_York"), time_hour(x)),
    19L
  )
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = c("POSIXct", "POSIXt"))
  expect_error(time_hour(x), "`POSIXct` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = c("POSIXct", "POSIXt"))
  expect_identical(time_hour(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = c("POSIXct", "POSIXt"))
  expect_identical(time_hour(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(time_hour(1), regexp = "Unknown object")
  expect_error(time_hour("x"), regexp = "Unknown object")
})
