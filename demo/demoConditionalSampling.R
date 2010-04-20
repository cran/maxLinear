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

X11();
par( oma=c(3,3,3,3))
par(mfrow = c(2,2));


for (i in (1:2))
	for (j in (1:2))
    {
    par( mar=c(2,2,0,0))
    sampledZp = maxLinear.CS(HS, z, 1, alpha ,para);                 ## conditional sampling
    Y = maxLinear(B,sampledZp); Y = matrix(Y, nrow = predGridNb[1]); ##
    image(predGridAxis$x, predGridAxis$y, Y, col = topo.colors(100),   ## plot
        xlab = "", ylab = "",
        xlim = c(predGridAxis$x[1],predGridAxis$x[predGridNb[1]]),
        ylim = c(predGridAxis$y[1],predGridAxis$y[predGridNb[2]]))

    contour(predGridAxis$x,predGridAxis$y, Y, nlevel = 5,lwd = 2, 
        axes = FALSE, add = TRUE);
    points(obsGrid[1,],obsGrid[2,],
           pch= 4, col = "red", cex = 2, lwd = 2, xlab = "", ylab = "");
    text(obsGrid[1,], obsGrid[2,], 
         floor(X*100)/100, pos = 4, col = "red", xlab = "", ylab = "");
		}

mainExpr = "Conditional sampling from the Smith model"
subExpr = substitute("Parameters:" * rho * "=" * rh * ","
                     * beta[1] * "=" * b1 * "," * beta[2] * "=" * b2,
                     list(rh = rho, b1 = beta1,b2 = beta2));
					 
par(mfrow = c(1,1));par(oma = c(1,3,0,3)); par(mar = c(5,0,2,0));
title(main = mainExpr, sub = subExpr, cex = 0.5,font = 1)
