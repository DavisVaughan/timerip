
<!-- README.md is generated from README.Rmd. Please edit that file -->

# timewarp

<!-- badges: start -->

<!-- badges: end -->

The goal of timewarp is to be a fast extractor of individual date-time
components, such as year or month, from `Date` or `POSIXct` objects.

## Installation

You can install the released version of timewarp from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("timewarp")
```

## Example

The main goal is to be faster than `as.POSIXlt()`, which wastes memory
and time when you just want a single component.

``` r
x <- as.POSIXct("2019-01-01", tz = "EST")
x <- rep(x, 2e5)

bench::mark(
  warp_year(x),
  as.POSIXlt(x)$year + 1900L
)
```

``` r
#> # A tibble: 2 x 6
#>   expression                      min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>                 <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 warp_year(x)                 5.29ms   6.39ms     153.      2.3MB     2.07
#> 2 as.POSIXlt(x)$year + 1900L   12.5ms  15.55ms      63.7    9.92MB    20.3
```

## Notes

If you use RStudio, to match R Core syntax, I have set the `.Rproj` code
editing options to:

  - Uncheck “insert spaces for tabs”
  - Tab width: 8
