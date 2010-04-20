\name{grid.HP2d}
\alias{grid.HP2d}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Generate de Haan-Pereira model.
}
\description{
Generate a discretized version of de Haan-Pereira model. See return values.
}
\usage{
grid.HP2d(rho, beta1, beta2, obs, HPgrid, HPgridSize, alpha)
}
\arguments{
  \item{rho}{
Parameter for the de Haan-Pereira model.
}
  \item{beta1}{
Parameter for the de Haan-Pereira model.
}
  \item{beta2}{
Parameter for the de Haan-Pereira model.
}
  \item{obs}{
A 2 by \eqn{n}{n} matrix representing the locations of n observations.
}
  \item{HPgrid}{
A 2 by \eqn{p}{p} matrix representing the grids in the discretized de Haan-Pereira model.
}
  \item{HPgridSize}{
The size of a single block region in the grid.
}
  \item{alpha}{
The \eqn{\alpha}{alpha}-Frechet index.
}
}

\value{
The value returned is a matrix \eqn{A}{A}. This corresponds to a discretized (and truncated) version of the de Haan-Pereira model:
\deqn{
Z(t_1,t_2) = \max_{j\geq 1}\frac{\phi(X_j-t_1,W_j - t_2)}{Y_j} \mbox{ for } (t_1,t_2)\in R^2
}{Z(t_1,t_2) = max_{j\geq 1}(\phi(X_j-t_1,W_j - t_2))/Y_j for (t_1,t_2)\in R^2}
with
\deqn{
  \phi(t_1,t_2) := \frac{\beta_1\beta_2}{2\pi\sqrt{1-\rho^2}}
  \exp\Big\{ - \frac1{2(1-\rho^2)}\left[\beta_1^2t_1^2 - 2\rho\beta_1\beta_2t_1t_2 + \beta_2^2t_2^2\right]\Big\}.
}{\phi(t_1,t_2) being the bivariate normal density (with parameter rho, beta_1 and beta_2).}
Here, \eqn{h^2} equals \code{HPgridSize}, and \eqn{(X_i,W_i,Y_i)_{i\geq 1}} are the points of a homogeneous Poisson point process on \eqn{R^2\times R_+}. 

To obtain a discretized version of the de Haan-Pereira model, we restrict to the region \eqn{[-M,M]^2} and consider a uniform 
grid of size \eqn{h = M/q,\ q\in N}:
\deqn{
 X(t_1,t_2) = \bigvee_{-q\le j_1,j_2\le q-1}h^{2/\alpha} \phi(t_1 - u_{j_1}, t_2 - u_{j_2})Z_{j_1,j_2},}
 where \eqn{Z_{j_1,j_2}} are i.i.d. \eqn{\alpha}{alpha}-Frechet random variables. 
 
 In practice, the locations of grid are saved in \code{gridHP}, a \eqn{2\times p}{2 times p} matrix. The observations are saved in \code{obs}, a \eqn{2\times n}{2 times n} matrix. Then, the return value \eqn{A} is an \eqn{n\times p}{n times p} matrix, with the \eqn{i}-th row, corresponding to the \eqn{i}-th observation, equal to
\deqn{
A_{i,j} = h^{2/\alpha}\phi(t^{obs}_i(1) - u_j(1), t^{obs}_i(2)-u_j(2)).
}
Here, \eqn{(t^{obs}_i(1),t^{obs}_i(2))} corresponds to the location of the \eqn{i}-th observation, and \eqn{(u_j(1),u_j(2))} corresponds to the location of the \eqn{j}-th point in the grid. Note that the points in grid, obtained from \code{grid.locations}, is in lexicographical order. See \code{\link{grid.locations}}.
}
\references{
Laurens de Haan and Teresa T. Pereira. Spatial Extremes: Models for the Stationary Case. The Annals of Statistics, 2006, Vol. 34, No. 1, 146--168.
}
\author{
Yizao Wang
}

\seealso{
\code{\link{grid.locations}}
%% ~~objects to See Also as \code{\link{help}}, ~~~
}
\examples{
## simulate from the discrete de Haan-Pereira model.

rho = -0.8; beta1 = 1.5; beta2 = 0.7;    ## parameters
alpha = 1; para = 1;

## HP grid
HPGrid_leftbottom = c(-4,-4); HPGridSize = c(8,8); HPGridNb = c(40,40); 
disGrid_leftbottom = c(-2,-2); disGridSize = c(4,4); disGridNb = c(80,80);

p = HPGridNb[1]*HPGridNb[2];  ## number of Z's

HPGrid = grid.locations(HPGrid_leftbottom, HPGridSize, HPGridNb);
HPGridRegionSize = HPGridSize[1]*HPGridSize[2]/(HPGridNb[1]*HPGridNb[2]);
HPShift = 0.5*HPGridSize/HPGridNb;

## display grid
disGridAxis = grid.axis(disGrid_leftbottom, disGridSize, disGridNb);
disGrid = grid.locations(disGrid_leftbottom, disGridSize, disGridNb);
disShift = 0.5*disGridSize/disGridNb;

## generate the discretized de Haan-Pereira model.
A = grid.HP2d(rho,beta1,beta2,
              disGrid+disShift,HPGrid+HPShift,HPGridRegionSize,alpha);

Z = rAF(alpha = alpha, sigma = para, n = p);                   ## generate a sample.
X = maxLinear(A,Z);                                            ##
X = matrix(X, nrow = disGridNb[1], ncol = disGridNb[2]);    

X11();
image(disGridAxis$x, disGridAxis$y, X, col = topo.colors(100), ## plot
      xlab = "", ylab = "",
      xlim = c(disGridAxis$x[1],disGridAxis$x[disGridNb[1]]),
      ylim = c(disGridAxis$y[1],disGridAxis$y[disGridNb[2]]))

contour(disGridAxis$x,disGridAxis$y, X, nlevel = 5,lwd = 2, 
        axes = FALSE, add = TRUE);

mainExpr = "Sampling from the de Haan-Pereira model"
subExpr = substitute("Parameters:" * rho * "=" * rh * ","
                     * beta[1] * "=" * b1 * "," * beta[2] * "=" * b2,
                     list(rh = rho, b1 = beta1,b2 = beta2));
title(main = mainExpr, sub = subExpr, cex = 0.5,font = 1)

}
\keyword{de Haan-Pereira model}
