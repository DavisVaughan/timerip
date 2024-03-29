% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/yday.R
\name{rip_yday}
\alias{rip_yday}
\title{Extract the day of the year from a date or datetime}
\usage{
rip_yday(x)
}
\arguments{
\item{x}{\verb{<Date / POSIXct / POSIXlt>}

The vector to extract the day of the year from.}
}
\value{
An integer vector the same size as \code{x} containing the day of the
year values.
}
\description{
\code{rip_yday()} extracts the day of the year from a date or datetime object.
}
\examples{
# Identical dates, but in different days of the year
x <- as.POSIXct("1969-12-31 19:00:00", tz = "America/New_York")
y <- as.POSIXct("1970-01-01 00:00:00", tz = "UTC")

identical(as.numeric(x), as.numeric(y))

rip_yday(x)
rip_yday(y)
}
