grid.axis<-function(grid_leftbottom, gridSize, gridNumber)
{
	if (length(gridNumber) != 2 || length(gridSize) != 2) stop("parameters not matched. gridNumber and gridSize must be a vector of length 2.\n");
	gridX = (seq(1,gridNumber[1])-1)/gridNumber[1];
	gridX = gridX*gridSize[1] + grid_leftbottom[1];
	gridY = (seq(1,gridNumber[2])-1)/gridNumber[2];
	gridY = gridY*gridSize[2] + grid_leftbottom[2];
	return(list(x = gridX,y = gridY));
}

grid.locations <- function(grid_leftbottom, gridSize, gridNumber)
{
	if (length(gridNumber) != 2 || length(gridSize) != 2) stop("parameters not matched. gridNumber and gridSize must be a vector of length 2.\n");
	gridC = matrix(0,nrow = 2, ncol = gridNumber[1]*gridNumber[2]);
	if (!is.loaded("getGridC")) dyn.load(paste("maxLinear", .Platform$dynlib.ext, sep=""));
	if (!is.loaded("getGridC")) print("getGridC() cannot be loaded.");
	gridC = .C("getGridC",as.double(grid_leftbottom),as.double(gridSize), as.integer(gridNumber), cG = as.double(gridC), PACKAGE = "maxLinear")$cG;
	gridC = matrix(gridC, nrow = 2, byrow = FALSE);
	return(gridC);
}

######################################
## functions for grid/random fields ##
######################################

##
## t and grid are 2 by n matrices for grid points. 
## grids correspond to the 'discretization' of f

grid.HP2d<-function(rho, beta1, beta2, obs, HPgrid, HPgridSize,alpha)
{
	if (!is.loaded("HP2dC")) dyn.load(paste("maxLinear", .Platform$dynlib.ext, sep=""));
	if (!is.loaded("HP2dC")) {print("grid.HP2d() in the shared library cannot be loaded!");return();}
	nObs = dim(obs)[2];
	nHPgrid = dim(HPgrid)[2];
	A = rep(0,nObs*nHPgrid);
	AA = .C("HP2dC",as.double(rho),as.double(beta1),as.double(beta2),as.integer(nObs), as.double(obs),as.integer(nHPgrid),as.double(HPgrid), AA = A, PACKAGE = "maxLinear")$AA;
	AA = matrix(AA,nrow = nObs, ncol = nHPgrid, byrow = TRUE);
	AA = AA * HPgridSize^(1/alpha);
	return(AA);
}

