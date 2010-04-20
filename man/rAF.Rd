\name{rAF}
\alias{rAF}
\alias{rCAF}
\title{
Generate Random Variables from the alpha-Frechet Distribution.
}
\description{
Generate random variables from the \eqn{\alpha}{alpha}-Frechet distribution
\deqn{P(Z\leq z) = \exp\{-\sigma^\alpha z^{-\alpha}\}}{P(Z<=z) = exp(-sigma^alpha z^(-alpha))}
and the conditional \eqn{\alpha}{alpha}-Frechet distribution
\deqn{P(Z\leq z|Z\leq c) = \exp\{-\sigma^\alpha (z^{-\alpha}-c^{-\alpha})\}\,,\forall 0< z\leq c\,.}{P(Z<=z|Z<=c).}
}
\usage{
rAF(alpha = 1, sigma = 1, n = 1)
rCAF(alpha = 1, sigma = 1, n = 1,cc)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{alpha}{
Parameter in the \eqn{\alpha}{alpha}-Frechet distribution.
}
  \item{sigma}{
Parameter in the \eqn{\alpha}{alpha}-Frechet distribution.
}
  \item{cc}{
Parameter in the conditional \eqn{\alpha}{alpha}-Frechet distribution.  
}
  \item{n}{
Number of independent copies to return.
}
}
\value{
Return \eqn{n} independent samples from the required \eqn{\alpha}{alpha}-Frechet distribution.
}
\author{
Yizao Wang
}

\seealso{
\code{\link{maxLinear.CS}}
}
