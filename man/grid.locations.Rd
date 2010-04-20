\name{grid.locations}
\alias{grid.locations}
\title{
Generate locations for rectangle grids.
}
\description{
Generate locations for arbitrary rectangle grids. 
}
\usage{
grid.locations(grid_leftbottom, gridSize, gridNumber)
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
A 2 by \eqn{p}{p} matrix is returned with \eqn{p}{p} equals \code{gridNumber[1]} times \code{gridNumber[2]}. The grid locations are saved in the lexicographically increasing order. That is, in the order of 
\preformatted{
(1,1), (1,2), ... , (1,gridNumber[1]),
(2,1), (2,2), ... , (2,gridNumber[1]),
(3,1), ... 
       ...
(gridNumber[2],1), ... , (gridNumber[1],gridNumber[1]).
}
}
\author{
Yizao Wang
}
\seealso{
\code{\link{grid.axis}}
}


\examples{

## Generate a grid of size 40 by 40 with
## left-bottom location (-2,-2)
## right-top location (1.9,1.9)

T_leftbottom = c(-2,-2); TSize = c(4,4); gridNb = c(40,40);
grid = grid.locations(T_leftbottom, TSize, gridNb);
}
