#####################################
## calculate the boundary values z's
## A: n * p
## X: N * n
## z: N * p
#####################################

maxLinear.zHat<-function(A,X)
{
	n = dim(A)[1]; p = dim(A)[2];
	z = NULL;
	for (i in (1:p))
		z[i] = min(X/A[,i]);
	return(z)
}

maxLinear.HD<-function(A,X,z, error = 10^(-15))
{
	h = A
	n = dim(A)[1]
	p = dim(A)[2]
	tmpInfIndex = which(z == Inf);
	for (i in (1:n))
	{
		h[i,] = (abs(A[i,] * z - X[i]) <= error);
		h[i,tmpInfIndex] = 0;
	}
	if (sum(h!=0) == 0)
	{
		print("strange maxLinear.HD return (no hits detected). set hits for all Zp's.\n Check A, X and z.\n")
		print(A)
		print(X)
		print(z)	
		h[i,] = rep(1:p)
	}
	return (h)
}

#####################################################################
## get Zps from A and X
## nSim: number of simulations 
##
## X is a vector, output Zp is nSim*n, 
## each row Zp[i,] corresponding to one conditional sampling
#####################################################################

maxLinear<-function(A,Z)
{
	if (is.vector(Z)) Z = t(as.matrix(Z,nrow = 1));
	N = dim(Z)[1];
	nA = dim(A)[1]; p = dim(A)[2]; 
	if (!is.loaded("maxLinearInner2")) dyn.load(paste("maxLinear", .Platform$dynlib.ext, sep=""), PACKAGE = "maxLinear");
	if (!is.loaded("maxLinearInner2")) {print("maxLinearInner2() in the shared library cannot be loaded!");return();}
	AA = as.vector(t(A));
	ZZ = as.vector(t(Z));
	XXX = array(0,N*nA); XXX = as.vector(XXX);
	XXX = .C("maxLinearInner2", PACKAGE = "maxLinear", as.integer(p), as.integer(nA), as.integer(N), as.double(AA), as.double(ZZ), xx = as.double(XXX))$xx;
	XXX = matrix(XXX, nrow = N, ncol = nA, byrow = TRUE);
	return(XXX);
}

.medianC<-function(Y)
{
	if (is.vector(Y)) Y = matrix(Y,nrow = 1);
	if (!is.loaded("getMedianC")) dyn.load(paste("maxLinear", .Platform$dynlib.ext, sep=""));
	if (!is.loaded("getMedianC")) print("getMedianC() cannot be loaded.");
	n = dim(Y)[2];
	p = dim(Y)[1];
	Ymed = array(0,n);
	Ymed = .C("getMedianC", PACKAGE = "maxLinear" ,as.integer(n),as.integer(p),as.double(Y),med = as.double(Ymed))$med;
	return(Ymed);
}

.First.lib <- function(lib, pkg)
{
	library.dynam("maxLinear", pkg, lib)
	##library.dynam("decomposeH", pkg, lib)
}



