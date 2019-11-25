# ------------------------------------------------------------------------------
# Date

test_that("can extract the year from a Date", {
  x <- new_date(0)
  expect_identical(time_year(x), 1970L)
})

test_that("can extract the year from an integer Date", {
  x <- structure(0L, class = "Date")
  expect_identical(time_year(x), 1970L)
})

test_that("can extract the year from a Date subclass", {
  x <- structure(0, class = c("foo_date", "Date"))
  expect_identical(time_year(x), 1970L)
})

# ------------------------------------------------------------------------------
# POSIXlt

test_that("can extract the year from a POSIXlt", {
  x <- as.POSIXlt(new_datetime_utc(0), tz = "UTC")
  expect_identical(time_year(x), 1970L)
})

# ------------------------------------------------------------------------------
# POSIXct

test_that("can extract the year from a POSIXct in UTC", {
  expect_identical(time_year(new_datetime_utc(0)), 1970L)
})

test_that("border times are handled correctly using their time zone", {
  x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
  y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")

  expect_identical(time_year(x), 1969L)
  expect_identical(time_year(y), 1970L)
})

test_that("border times are handled correctly using system TZ", {
  x <- new_datetime(0, tzone = "")

  expect_identical(
    with_envvar(list(TZ = "UTC"), time_year(x)),
    1970L
  )

  expect_identical(
    with_envvar(list(TZ = "America/New_York"), time_year(x)),
    1969L
  )
})

# ------------------------------------------------------------------------------
# Misc

test_that("error if not a recognized date type", {
  expect_error(time_year(1), regexp = "Unknown object")
  expect_error(time_year("x"), regexp = "Unknown object")
})
