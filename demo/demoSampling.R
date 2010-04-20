######################################################
## simulate from the discrete de Haan-Pereira model ## 
######################################################

library("maxLinear");

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
## plot

X11();
par( oma=c(3,3,3,3))
par(mfrow = c(2,2));
for (i in (1:2))
	for (j in (1:2))
    {
    par( mar=c(2,2,0,0))
    Z = rAF(alpha = alpha, sigma = para, n = p);                   ## generate a sample.
    X = maxLinear(A,Z);                                            ##
    X = matrix(X, nrow = disGridNb[1], ncol = disGridNb[2]);    
    image(disGridAxis$x, disGridAxis$y, X, col = topo.colors(100), ## plot
        xlab = "", ylab = "",
        xlim = c(disGridAxis$x[1],disGridAxis$x[disGridNb[1]]),
        ylim = c(disGridAxis$y[1],disGridAxis$y[disGridNb[2]]))

    contour(disGridAxis$x,disGridAxis$y, X, nlevel = 5,lwd = 2, 
        axes = FALSE, add = TRUE);
    }
par(mfrow = c(1,1));
mainExpr = "Sampling from the Smith model"
subExpr = substitute("Parameters:" * rho * "=" * rh * ","
                     * beta[1] * "=" * b1 * "," * beta[2] * "=" * b2,
                     list(rh = rho, b1 = beta1,b2 = beta2));
par(oma = c(1,3,0,3)); par(mar = c(5,0,2,0));
title(main = mainExpr, sub = subExpr, cex = 0.5,font = 1)
