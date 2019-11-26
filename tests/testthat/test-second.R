# ------------------------------------------------------------------------------
# Date

test_that("can extract the second from a Date", {
  x <- new_date(0)
  expect_identical(time_second(x), 0)
})

test_that("extracting seconds from a fractional Date ignores the fraction", {
  x <- new_date(0.5555) # technically 55 seconds
  expect_identical(time_second(x), 0)
})

test_that("can extract the second from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(time_second(x), 0)
})

test_that("can extract the second from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(time_second(x), 0)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = "Date")
  expect_error(time_second(x), "`Date` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = "Date")
  expect_identical(time_second(x), NA_real_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = "Date")
  expect_identical(time_second(x), NA_real_)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the second from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(1), tz = "UTC")
  expect_identical(time_second(x), 1)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the second from a POSIXct in UTC", {
  expect_identical(time_second(new_datetime_utc(1)), 1)
})

test_that("border times are handled correctly using their time zone", {
  x <- as.POSIXct("1969-12-31 19:00:01", tz = "America/New_York")
  y <- as.POSIXct("1970-01-01 00:00:01", tz = "UTC")

  expect_identical(time_second(x), 1)
  expect_identical(time_second(y), 1)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = c("POSIXct", "POSIXt"))
  expect_error(time_second(x), "`POSIXct` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = c("POSIXct", "POSIXt"))
  expect_identical(time_second(x), NA_real_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = c("POSIXct", "POSIXt"))
  expect_identical(time_second(x), NA_real_)
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(time_second(1), regexp = "Unknown object")
  expect_error(time_second("x"), regexp = "Unknown object")
})
