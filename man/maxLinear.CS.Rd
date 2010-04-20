\name{maxLinear.CS}
\alias{maxLinear.zHat}
\alias{maxLinear.HD}
\alias{maxLinear.HS}
\alias{maxLinear.CS}
\title{
Conditional Sampling for Max-Linear Models.
}
\description{
Given the max-linear model \deqn{{\bf X} = A\odot {\bf Z}}{ X = A odot Z}
resampling \eqn{{\bf Z}}{Z} according to the conditional distribution \deqn{{\bf Z}|{\bf X = x}}{Z|X = x} for some observation \eqn{\bf x}{x}. See Details below.
}
\usage{
maxLinear.zHat(A, X)
maxLinear.HD(A, X, z, error = 10^(-15))
maxLinear.HS(H, z, alpha = 1, para = 1)
maxLinear.CS(HS, z, N, alpha = 1, para = 1)
}
\arguments{
  \item{A}{An \eqn{n\times p}{n times p} matrix with non-negative entries.}
  \item{X}{A vector of size n. An observation for the max-linear model \eqn{A\odot \bf Z}{A odot Z}.}
  \item{z}{Upper boundary of \eqn{\bf Z}{Z}'s for the max-linear model \eqn{A\odot \bf Z}{A odot Z}, with observation \eqn{\bf X}{X}.}
  \item{error}{Numerical error control.}
  \item{H}{An \eqn{n} by \eqn{p} zero-one matrix.}
  \item{HS}{The hitting matrix (with blocking structure) corresponding to \eqn{A} and \eqn{\bf X}{X}.}
  \item{para}{Parameters of \eqn{\bf Z}{Z}'s in the max-linear model. A vector of size \eqn{p}. By default equals 1.}
  \item{alpha}{\eqn{\alpha}{alpha}-Frechet.}
  \item{N}{Number of conditional samplings.}
}
\value{
The functions are realizations of \code{Algorithm II} in \cite{Wang and Stoev, 2010}.

\code{maxLinear.zHat(A,X)} returns a \eqn{p}-vector \eqn{\widehat {\bf z}}{zHat}, with \deqn{\widehat z_j = \min_{1\leq i\leq n}x_i/a_{i,j},}{zHat_j = min_{1\leq i\leq n}x_i/a_ij}which is the necessary upper bound of \eqn{Z_j}, given \eqn{\bf X}.

\code{maxLinear.HD(A,X,z)} returns an \eqn{n \times p}{n times p} matrix, corresponding to the hitting matrix \eqn{H} defined by
\deqn{h_{i,j} = 1 \mbox{ if } a_{i,j}\widehat z_j = x_i \mbox{ and } 0 \mbox{ otherwise.}}{h_{i,j} = 1 if a_{i,j}zHat_j = x_i and 0 otherwise.}
In practice, instead of checking \eqn{a_{i,j}\widehat z_j = x_i}{a_{i,j}zHat_j = x_i}, we set \eqn{h_{i,j} = 1} if \eqn{|a_{i,j}\widehat z_j - x_i| < }{|a_{i,j}zHat_j - x_i| < }\code{error}. 

\code{maxLinear.HS(H)} returns a class, saving the structure of \eqn{(I_s, J^{(s)}, \overline J^{(s)})_{1\leq s\leq r}} as well as the weights. See \cite{Wang and Stoev, 2010} for details.

\code{maxLinear.CS(HS, z, N, para, alpha , mode )} returns an \code{N} by \eqn{p} matrix. Each row is an independent sample \eqn{\bf Z}{Z} with the desired conditional distribution \eqn{\bf Z|X}{Z|X}.
}
\references{
Yizao Wang and Stilian Stoev, Conditonal Sampling for Max--Linear Random Fields. 2010.
}
\author{
Yizao Wang
}
\seealso{
\code{\link{grid.HP2d}}
}


\examples{
###########################
## a simple illustration ##
###########################

n = 10; p = 100; N = 100;
A = matrix(runif(n*p),nrow = n) * 5; ## randomly generate a max-linear model.
Z = rAF(n = p);                      ## generate p 1-Frechet random variables.
X = maxLinear(A,Z);                  ## generate one observation 
                                     ## for the max-linear model.


z = maxLinear.zHat(A,X);             ## get upper boundary for Z's
H = maxLinear.HD(A,X,z);             ## get hitting distribution HD
HS = maxLinear.HS(H,z,alpha,para);   ## get hitting scenarios HS

sampledZp = maxLinear.CS(HS, z, N);  ## generate N conditional samplings 
                                     ## based on the observation X, 
                                     ## w.r.t. the model A.

#########################################################
## Conditional Sampling from the de Haan-Pereira model ##
#########################################################									

#################
## preparation ##
#################
rho = -0.8; beta1 = 1.5; beta2 = 0.7;  ## parameters of de Haan-Pereira model
alpha = 1; para = 1; 
nA = 7;                                ## number of observations

## the range of HP grid and prediction grid
HPGrid_leftbottom = c(-4,-4); HPGridSize = c(8,8); HPGridNb = c(50,50); 
pred_leftbottom = c(-2,-2); predGridSize = c(4,4); predGridNb = c(50,50);

## observation locations
obsGrid = matrix(0,nrow = 2,ncol = nA);
obsGrid[1,] = 0.35 * predGridSize[1] * cos(2 * pi * seq(1,nA)/nA);
obsGrid[2,] = 0.35 * predGridSize[2] * sin(2 * pi * seq(1,nA)/nA);

## the range of domain of discretization of the HP model
HPGrid = grid.locations(HPGrid_leftbottom, HPGridSize, HPGridNb);
HPGridRegionSize = HPGridSize[1]*HPGridSize[2]/(HPGridNb[1]*HPGridNb[2]);
HPShift = 0.5*HPGridSize/HPGridNb;

## the range of prediction grid
predGridAxis = grid.axis(pred_leftbottom, predGridSize, predGridNb);
predGrid = grid.locations(pred_leftbottom, predGridSize, predGridNb);
predShift = 0.5*predGridSize/predGridNb;

## grid for HP model: Creating a uniform grid
A = grid.HP2d(rho,beta1,beta2,
              obsGrid+predShift,HPGrid+HPShift,HPGridRegionSize, alpha);
B = grid.HP2d(rho,beta1,beta2,
              predGrid+predShift,HPGrid+HPShift,HPGridRegionSize,alpha);


## fix abritrary observations			  
X = array(5,nA); 

##########################
## conditional sampling ##
##########################
z = maxLinear.zHat(A,X);               ## obtain zhat.
H = maxLinear.HD(A,X,z);               ## Obtain hitting matrix.
HS = maxLinear.HS(H,z,alpha,para);     ## Obtain hitting scenarios.

## conditional sampling
sampledZp = maxLinear.CS(HS, z, 1, alpha ,para);
Y = maxLinear(B,sampledZp); Y = matrix(Y, nrow = predGridNb[1]);

##########
## plot ##
##########
image(predGridAxis$x, predGridAxis$y, Y, col = topo.colors(100), ## plot
      xlab = "", ylab = "",
      xlim = c(predGridAxis$x[1],predGridAxis$x[predGridNb[1]]),
      ylim = c(predGridAxis$y[1],predGridAxis$y[predGridNb[2]]))
contour(predGridAxis$x,predGridAxis$y, Y, nlevel = 5,lwd = 2, 
        axes = FALSE, add = TRUE);
points(obsGrid[1,],obsGrid[2,],
       pch= 4, col = "red", cex = 2, lwd = 2, xlab = "", ylab = "");
text(obsGrid[1,], obsGrid[2,], 
     floor(X*100)/100, pos = 4, col = "red", xlab = "", ylab = "");
	 
mainExpr = "Conditional sampling from the de Haan-Pereira model"
subExpr = substitute("Parameters:" * rho * "=" * rh * ","
                     * beta[1] * "=" * b1 * "," * beta[2] * "=" * b2,
                     list(rh = rho, b1 = beta1,b2 = beta2));
title(main = mainExpr, sub = subExpr, cex = 0.5,font = 1)


}

\keyword{Conditional sampling for max-linear models}
