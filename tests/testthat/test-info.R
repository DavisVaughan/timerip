# ------------------------------------------------------------------------------
# Date

test_that("info is structurally sound from a Date", {
  x <- rip_info(new_date(0))

  expect_is(x, "list")

  expect_named(
    x,
    c("second", "minute", "hour", "mday", "month", "year", "wday", "yday")
  )

  expect_is(x[[1]], "numeric")
  expect_is(x[[2]], "integer")
  expect_is(x[[3]], "integer")
  expect_is(x[[4]], "integer")
  expect_is(x[[5]], "integer")
  expect_is(x[[6]], "integer")
  expect_is(x[[7]], "integer")
  expect_is(x[[8]], "integer")
})

test_that("can extract the info from a Date", {
  x <- new_date(0)
  expect_identical(rip_info(x)$year, 1970L)
})

test_that("can extract the info from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(rip_info(x)$year, 1970L)
})

test_that("can extract the info from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(rip_info(x)$year, 1970L)
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = "Date")
  expect_error(rip_info(x), "`Date` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = "Date")

  expect <- c(list(NA_real_), rep_len(list(NA_integer_), 7))
  names(expect) <- c("second", "minute", "hour", "mday", "month", "year", "wday", "yday")

  expect_identical(rip_info(x), expect)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = "Date")

  expect <- c(list(NA_real_), rep_len(list(NA_integer_), 7))
  names(expect) <- c("second", "minute", "hour", "mday", "month", "year", "wday", "yday")

  expect_identical(rip_info(x), expect)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the info from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(0), tz = "UTC")
  expect_identical(rip_info(x)$year, 1970L)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the info from a POSIXct in UTC", {
  expect_identical(rip_info(new_datetime_utc(0))$year, 1970L)
})

test_that("border times are handled correctly using their time zone", {
  x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
  y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")

  expect_identical(rip_info(x)$year, 1969L)
  expect_identical(rip_info(y)$year, 1970L)
})

test_that("border times are handled correctly using system TZ", {
  x <- new_datetime(0, tzone = "")

  expect_identical(
    with_envvar(list(TZ = "UTC"), rip_info(x)$year),
    1970L
  )

  expect_identical(
    with_envvar(list(TZ = "America/New_York"), rip_info(x)$year),
    1969L
  )
})

test_that("bad date types are handled correctly", {
  x <- structure("x", class = c("POSIXct", "POSIXt"))
  expect_error(rip_info(x), "`POSIXct` type character")
})

test_that("Inf dates are handled correctly", {
  x <- structure(Inf, class = c("POSIXct", "POSIXt"))

  expect <- c(list(NA_real_), rep_len(list(NA_integer_), 7))
  names(expect) <- c("second", "minute", "hour", "mday", "month", "year", "wday", "yday")

  expect_identical(rip_info(x), expect)
})

test_that("NaN dates are handled correctly", {
  x <- structure(NaN, class = c("POSIXct", "POSIXt"))

  expect <- c(list(NA_real_), rep_len(list(NA_integer_), 7))
  names(expect) <- c("second", "minute", "hour", "mday", "month", "year", "wday", "yday")

  expect_identical(rip_info(x), expect)
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(rip_info(1), regexp = "Unknown object")
  expect_error(rip_info("x"), regexp = "Unknown object")
})
