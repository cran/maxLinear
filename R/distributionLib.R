rAF<-function(alpha = 1,sigma = 1, n = 1)
{
	if (length(alpha) == 1 && n > 1) alpha = rep(alpha,n);
	if (length(sigma) == 1 && n > 1) sigma = rep(sigma,n);
	U = runif(n);
	Z = (-log(U)/(sigma^alpha))^(-1/alpha);
	return(Z)
}

rCAF<-function(alpha = 1,sigma = 1, n = 1, cc)
{
	##print(paste("ff",alpha, sigma, n, cc));
	##print(paste("length(alpha) = ", length(alpha)," length(sigma) = ", length(sigma)," n= ", n, " length(cc) = ", length(cc)));
	if (length(alpha) == 1 && n > 1) alpha = rep(alpha,n);
	if (length(sigma) == 1 && n > 1) sigma = rep(sigma,n);
	if (length(cc) == 1 && n > 1) cc = rep(cc,n);
	U = runif(n);
	Z = (-log(U)/(sigma^alpha) + 1/cc^alpha)^(-1/alpha);
	return(Z)
}



