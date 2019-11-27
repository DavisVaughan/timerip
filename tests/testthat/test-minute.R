# ------------------------------------------------------------------------------
# Date

test_that("can extract the minute from a Date", {
  x <- new_date(0)
  expect_identical(rip_minute(x), 0L)
})

test_that("extracting minutes from a fractional Date ignores the fraction", {
  x <- new_date(0.5555) # technically 19 minutes
  expect_identical(rip_minute(x), 0L)
})

test_that("can extract the minute from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(rip_minute(x), 0L)
})

test_that("can extract the minute from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(rip_minute(x), 0L)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = "Date")
  expect_error(rip_minute(x), "`Date` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = "Date")
  expect_identical(rip_minute(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = "Date")
  expect_identical(rip_minute(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the minute from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(5000), tz = "UTC")
  expect_identical(rip_minute(x), 23L)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the minute from a POSIXct in UTC", {
  expect_identical(rip_minute(new_datetime_utc(5000)), 23L)
})

test_that("20 minute DST gaps are handled correctly", {
  x <- as.POSIXct("1920-08-31 23:59:59", tz = "Africa/Accra")
  y <- as.POSIXct("1920-09-01 00:20:00", tz = "Africa/Accra")

  expect_identical(rip_minute(x), 59L)
  expect_identical(rip_minute(y), 20L)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = c("POSIXct", "POSIXt"))
  expect_error(rip_minute(x), "`POSIXct` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = c("POSIXct", "POSIXt"))
  expect_identical(rip_minute(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = c("POSIXct", "POSIXt"))
  expect_identical(rip_minute(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(rip_minute(1), regexp = "Unknown object")
  expect_error(rip_minute("x"), regexp = "Unknown object")
})
