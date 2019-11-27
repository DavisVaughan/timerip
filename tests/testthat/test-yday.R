# ------------------------------------------------------------------------------
# Date

test_that("can extract the yday from a Date", {
  x <- new_date(0)
  expect_identical(rip_yday(x), 1L)
})

test_that("can extract the yday from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(rip_yday(x), 1L)
})

test_that("can extract the yday from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(rip_yday(x), 1L)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = "Date")
  expect_error(rip_yday(x), "`Date` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = "Date")
  expect_identical(rip_yday(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = "Date")
  expect_identical(rip_yday(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the yday from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(0), tz = "UTC")
  expect_identical(rip_yday(x), 1L)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the yday from a POSIXct in UTC", {
  expect_identical(rip_yday(new_datetime_utc(0)), 1L)
})

test_that("border times are handled correctly using their time zone", {
  x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
  y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")

  expect_identical(rip_yday(x), 365L)
  expect_identical(rip_yday(y), 1L)
})

test_that("border times are handled correctly using system TZ", {
  x <- new_datetime(0, tzone = "")

  expect_identical(
    with_envvar(list(TZ = "UTC"), rip_yday(x)),
    1L
  )

  expect_identical(
    with_envvar(list(TZ = "America/New_York"), rip_yday(x)),
    365L
  )
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = c("POSIXct", "POSIXt"))
  expect_error(rip_yday(x), "`POSIXct` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = c("POSIXct", "POSIXt"))
  expect_identical(rip_yday(x), NA_integer_)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = c("POSIXct", "POSIXt"))
  expect_identical(rip_yday(x), NA_integer_)
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(rip_yday(1), regexp = "Unknown object")
  expect_error(rip_yday("x"), regexp = "Unknown object")
})
