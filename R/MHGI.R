
## read MHGI data
.readMHG<-function()
{
	scanMHGI = scan("MHGI.txt", quiet = TRUE);
	n = scanMHGI[1]; p = scanMHGI[2];
	MHGI = matrix(0,nrow = n, ncol = p);
	MHGINb = NULL;
	counter = 3;
	for (i in (1:n))
	{
		pp = scanMHGI[counter];##print(paste("pp = ",pp));
		MHGI[i,1:pp] = scanMHGI[(counter+1):(counter + pp)];
		counter = counter + pp + 1;
		MHGINb[i] = pp;
	}
	 return(list(groupIndex = MHGI, groupIndexNb = MHGINb));
}

.readHHJs<-function()
{
	tmpHHJs = scan("HHJs.txt", quiet = TRUE);
	n = tmpHHJs[1]; 
	if (n >100000) {print(paste("HHJs.size() = ",n)); stop("Too many hitting scenarios! Aborted.");}
	if (n > 0) 
	{
		HHJs = tmpHHJs[2:length(tmpHHJs)];
		HHJs = matrix(HHJs,nrow = n, byrow = TRUE);
	} else {HHJs = 0;}
	return (list(Js = HHJs, size = n));
}

.MHG.weights<-function(MHG,z, alpha = 1, para = 1)
{
	p = length(z);
	if (length(alpha) == 1) alpha = array(alpha,p);
	if (length(para) == 1) para = array(para,p);
	ww = MHG$groupIndex;
	for (i in (1:dim(MHG$groupIndex)[1]))
	{
		for (j in (1:MHG$groupIndexNb[i]))
			ww[i,j] = (para[MHG$groupIndex[i,j]]/z[MHG$groupIndex[i,j]])^alpha[MHG$groupIndex[i,j]];
		ww[i,] = ww[i,]/sum(ww[i,]);
	}
	ww = t(apply(ww,1,cumsum));
	if (dim(MHG$groupIndex)[2] == 1) ww = t(ww);
	
	return(ww);
}

## return the indices, not 0/1 lines.
.MHG.sampleHits<-function(N,groupIndex, weights)
{
	rank = dim(groupIndex)[1];
	sampledHits = matrix(0,nrow = N, ncol = rank);
	for (i in (1:N))
	{
		r = runif(n = rank);
		for (j in (1:rank))
			sampledHits[i,j] = groupIndex[j,min(which((weights[j,]>=r[j])))];
	}
	return(sampledHits);
}

## return values depend on the Js. (the indices or 0/1's?)
.HHJs.sampleHits<-function(N,Js,JWs)
{
	sampledHits = NULL;
	for (i in (1:N))
	{
		r = runif(1);
		##sampledHits = rbind(sampledHits,Js[min(JWs>=r)]);
		sampledHits[i] = Js[min(which(JWs>=r))];
	}
	## for debug: Js = HS$HHJs; JWs = HS$HHJs.weights;
	return(sampledHits);
}


.sampleHits<-function(N, MHGI, MHG.weights, HHJs, HHJs.weights, HHJs.size)
{
	sampledHits = .MHG.sampleHits(N, MHGI ,MHG.weights);
	if (HHJs.size > 0) 
	{
		HHJs.Hits = .HHJs.sampleHits(N, HHJs ,HHJs.weights);
		sampledHits = cbind(sampledHits, HHJs.Hits);
	}
	return(sampledHits);
}

maxLinear.HS<-function(H,z,alpha = 1, para = 1)
{
	p = length(z);
	cat(dim(H)[1],dim(H)[2],t(H), file = "matrix.txt");
	##dyn.load("decomposeH.dll");
	.C("tests", PACKAGE = "maxLinear");
	##dyn.unload("decomposeH.dll");
	MHG = .readMHG();
	HHJs = .readHHJs();
	
	MHG.weights = .MHG.weights(MHG,z);
	HHJs.weights = 0;
	if (HHJs$size > 0)
		HHJs.weights = .maxLinear.Js.weights(z,HHJs$Js,para,alpha);
		
	return(list(MHG.index = MHG$groupIndex, MHG.weights = MHG.weights, HHJs = HHJs$Js, HHJs.size = HHJs$size, HHJs.weights = HHJs.weights));
}

.maxLinear.Js.weights<-function(zHat,Js,para,alpha)
{
	mode = 0;
	p = length(zHat);
	infIndex = which(zHat == Inf);
	zHat[infIndex] = -1;
	if (length(para) == 1 & p > 1) para = rep(para,p);
	if (length(alpha) == 1 & p > 1) alpha = rep(alpha,p);
	nJs = dim(Js)[1]; rJs = dim(Js)[2];
	if (!is.loaded("getWeights")) dyn.load(paste("maxLinear", .Platform$dynlib.ext, sep=""));
	if (!is.loaded("getWeights")) {print("getWeights() in the shared library cannot be loaded!");return();}
	JWs = rep(0,nJs);
	JWs = .C("getWeights", PACKAGE = "maxLinear",as.integer(p),as.double(zHat),as.double(para), as.double(alpha), as.integer(nJs), as.integer(rJs), as.integer(t(Js)), as.integer(mode), ww = JWs)$ww;
	return(JWs);
}

maxLinear.CS<-function(HS,z,N,alpha = 1, para = 1)
{
	sampledHits = .sampleHits(N, HS$MHG.index, HS$MHG.weights, HS$HHJs, HS$HHJs.weights, HS$HHJs.size);
	##print(sampledHits);
        p = length(z);
	sampledZ = NULL;
	for (i in (1:N))
	{
		tmpZ = rCAF(n = p, alpha = alpha, sigma = para, cc = z);
		tmpZ[sampledHits[i,]] = z[sampledHits[i,]];
		sampledZ = rbind(sampledZ,tmpZ);
	}
	return(sampledZ);
}
