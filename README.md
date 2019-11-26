
<!-- README.md is generated from README.Rmd. Please edit that file -->

# timewarp

<!-- badges: start -->

[![R build
status](https://github.com/DavisVaughan/timewarp/workflows/R-CMD-check/badge.svg)](https://github.com/DavisVaughan/timewarp)
[![Travis build
status](https://travis-ci.org/DavisVaughan/timewarp.svg?branch=master)](https://travis-ci.org/DavisVaughan/timewarp)
[![Codecov test
coverage](https://codecov.io/gh/DavisVaughan/timewarp/branch/master/graph/badge.svg)](https://codecov.io/gh/DavisVaughan/timewarp?branch=master)
<!-- badges: end -->

The goal of timewarp is to be a fast extractor of individual date-time
components, such as year or month, from `Date` or `POSIXct` objects.

## Installation

You can install the dev version from GitHub with:

``` r
devtools::install_github("DavisVaughan/timewarp")
```

## Example

The main goal is to be faster than `as.POSIXlt()`, which wastes memory
and time when you just want a single component.

``` r
x <- as.POSIXct("2019-01-01", tz = "EST")
x <- rep(x, 2e5)

bench::mark(
  time_year(x),
  as.POSIXlt(x)$year + 1900L
)
```

``` r
#> # A tibble: 2 x 6
#>   expression                      min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>                 <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 time_year(x)                 5.29ms   6.39ms     153.      2.3MB     2.07
#> 2 as.POSIXlt(x)$year + 1900L   12.5ms  15.55ms      63.7    9.92MB    20.3
```

Extraction for `Date`s is faster too.

``` r
y <- as.Date(x)

bench::mark(
  time_year(y),
  as.POSIXlt(y)$year + 1900L
)
```

``` r
#> # A tibble: 2 x 6
#>   expression                      min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>                 <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 time_year(y)                 4.92ms   5.83ms     162.    790.7KB     2.08
#> 2 as.POSIXlt(y)$year + 1900L  17.82ms  19.45ms      50.9    9.16MB    12.7
```
