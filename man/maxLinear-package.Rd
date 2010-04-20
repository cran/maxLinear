\name{maxLinear-package}
\alias{maxLinear-package}
\alias{maxLinear}
\docType{package}
\title{
Conditional Sampling Tools for Max-Linear Models.
}
\description{
This package provides efficient computational tools for conditional samplings in max-linear models, which include a large class of max-linear random fields. 
}
\details{
\tabular{ll}{
Package: \tab maxLinear\cr
Type: \tab Package\cr
Version: \tab 1.0\cr
Date: \tab 2010-04-20\cr
License: \tab GPL>=2 \cr
LazyLoad: \tab yes\cr
}
}
\author{
Yizao Wang

Maintainer: Yizao Wang <yizwang@umich.edu>
}
\references{
Yizao Wang and Stilian Stoev, Conditional Samplings for Max--Stable Random Fields. Technical Report, Department of Statistics, University of Michigan. 2010
}
\examples{
n = 10; p = 100; N = 100;

## randomly generate a max-linear model.
A = matrix(runif(n*p),nrow = n) * 5; 

## generate p 1-Frechet random variables.
Z = rAF(n = p);                      

## generate one observation from the max-linear model.
X = maxLinear(A,Z);                  

## get upper boundary for Z's
z = maxLinear.zHat(A,X);     
            
## get hitting distribution HD			
H = maxLinear.HD(A,X,z);      
           
## get hitting scenarios HS		   
HS = maxLinear.HS(H,z,alpha,para);  

## generate N conditional samplings 
## based on the observation X, w.r.t. the model A.
sampledZp = maxLinear.CS(HS, z, N);  
}
