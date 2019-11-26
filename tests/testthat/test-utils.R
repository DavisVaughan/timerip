test_that("can get the class of a Date", {
  x <- as.Date("2019-01-01")
  expect_equal(time_class_type(x), "date")
})

test_that("can get the class of a POSIXct", {
  x <- as.POSIXct("2019-01-01", "UTC")
  expect_equal(time_class_type(x), "posixct")
})

test_that("can get the class of a POSIXlt", {
  x <- as.POSIXlt("2019-01-01", "UTC")
  expect_equal(time_class_type(x), "posixlt")
})

test_that("can get the class of a non-date type", {
  expect_equal(time_class_type(1), "unknown")
  expect_equal(time_class_type(factor("x")), "unknown")
})

test_that("Treats date / posixct subclasses as their superclass", {
  x <- structure(1L, class = c("subclass_date", "Date"))
  expect_equal(time_class_type(x), "date")

  x <- structure(1L, class = c("subclass_date", "POSIXct", "POSIXt"))
  expect_equal(time_class_type(x), "posixct")
})
