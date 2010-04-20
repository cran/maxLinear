\name{grid.axis}
\alias{grid.axis}
\title{
Generate axis for rectangle grids.
}
\description{
Generate axis for arbitrary rectangle grids. 
}
\usage{
grid.axis(grid_leftbottom, gridSize, gridNumber)
}
\arguments{
  \item{grid_leftbottom}{
The left-bottom location of the grid.
}
  \item{gridSize}{
 The lengths of horizontal and the vertical ranges of the grid. Saved in a 2-vector.
}
  \item{gridNumber}{
The number of points in each horizontal line and vertical line of the grids. Saved in a 2-vector.
}
}

\value{
A list (say \code{axis}) of two vectors (\code{axis$x} and \code{axis$y}) is returned.
}
\author{
Yizao Wang
}
\seealso{
\code{\link{grid.locations}}
}


\examples{

## Generate a grid of size 40 by 40 with
## left-bottom location (-2,-2)
## right-top location (1.9,1.9)

T_leftbottom = c(-2,-2); TSize = c(4,4); gridNb = c(40,40);
grid = grid.axis(T_leftbottom, TSize, gridNb);
}
