#include"math.h"
#include"stdio.h"
#include"R.h"

void maxLinearInner(int *p, double *A, double *Z, double *X)
{
	*X = 0;
	int n = p[0];
	for (int i = 0;i<n;i++)
	{
		double x = A[i]*Z[i];
		if (x>*X) *X = x;
	}
}

void maxLinearInner2(int *p, int *nA, int *N, double *A, double *Z, double *X)
{
	int cX = 0;
	int cZ = 0;
	for (int m = 0;m<N[0];m++)
	{
		int c = 0;
		for (int i = 0;i<nA[0]; i++)
		{
			for (int j = 0;j<p[0]; j++)
			{
				double x = A[c]*Z[cZ + j];
				if (X[cX]<x) X[cX] = x;
				c++;
			}
			cX++;
		}
		cZ = cZ + p[0];
	}
}


void pickWeight(int *n, double *w, double *rW, int *m)
{
	int n0 = n[0];
	*m = 0;
	for(int i = 0;i<n0; i++)
		if (w[i]>*rW) {*m = i+1; break;}
	if (*m == 0) *m = n0;
}

void getWeights(int *p, double *zHat, double *para, double *alpha, int *nJs, int *rJs, int *Js, int *mode, double *w)
//getWs<-function(zz, CIs, para = 1, alpha = 1, mm = 0)
{
	double ww = 0;
	int counter = 0;
	for (int i = 0;i<nJs[0];i++)
	{
		w[i] = 1;

		for (int j = 0;j<rJs[0]; j++)
		{
			int jj = Js[counter]-1;
			if (zHat[jj] < 0) Rprintf("warning! zHat < 0!\n");
			switch(mode[0])
			{
				case 0:// alpha-Frechet
					//w[i] = w[i] * pow(para[jj],alpha[jj]) * pow(zHat[jj],-(1 + alpha[jj])) * zHat[jj]; break;
					w[i] = w[i] / zHat[jj]; break;
				case 1:// exponential
					w[i] = w[i] * para[jj] * exp(- para[jj] * zHat[jj])/(1-exp(- para[jj] * zHat[jj])) * zHat[jj]; break;
				case 2:// alpha-Pareto
					w[i] = w[i] * alpha[jj]/(pow(zHat[jj],alpha[jj]) - 1);break;
			}
			counter++;
		}
		ww = ww + w[i];
	}
// normalization
	w[0] = w[0]/ww;
	for (int i = 1;i<nJs[0];i++)
		{w[i] = w[i]/ww; w[i] = w[i] + w[i-1];}
}


double vectorProduct(const double * v1, const double * v2, int size)
{
	double p = 0;
	for(int i = 0;i<size;i++)
	{
		p = p + v1[i]*v2[i];
	}
	return p;
}

double vectorProduct2(const double v11, const double v12, const double v21, const double v22)
{
	return v11*v12 + v21*v22;
}

//
// obs and grid are 2 by n matrices for grid points. 
// grids correspond to the 'discretization' of f
void HP2dC(double *rho, double *beta1, double *beta2, int *nObs, double *obs, int *nGrid, double *grid, double *A)
{
	//sI: sigmaInverse, a 2*2 matrix
	double sI00 = 1;
	double sI11 = sI00;
	double sI01 = -rho[0];
	double sI10 = sI01;
    double pi = 3.14159265358979;
	double rho2 = rho[0]*rho[0];
	
	int counterObs = 0;
	int counterA = 0;
	for (int i = 0; i<nObs[0]; i++)
	{
		int counterGrid = 0;
		for (int j = 0;j<nGrid[0]; j++)
		{
			double v1 = (obs[counterObs] - grid[counterGrid])*beta1[0];
			double v2 = (obs[counterObs + 1] - grid[counterGrid+1])*beta2[0];
			double p1 = v1*sI00 + v2*sI10;
			double p2 = v1*sI10 + v2*sI11;
			double p = (v1*p1 + v2*p2)/(1-rho2);
			p = exp(-p/2)*beta1[0]*beta2[0]/(2*pi*sqrt(1-rho2));
			A[counterA] = p;
			counterA++;
			counterGrid = counterGrid+2;
		}
		counterObs = counterObs+2;
	}
}



void getGridC(double *T_leftbottom, double *TSize, int*gridNumber, double * contourGrid)
{
	int counter = 0;
	double d0 = (double)TSize[0]/(double)(gridNumber[0]);
	double d1 = (double)TSize[1]/(double)(gridNumber[1]);
	for (int i = 0;i<gridNumber[1];i++)
		for (int j = 0; j<gridNumber[0];j++)
		{
			contourGrid[counter] = d0*(double)j + T_leftbottom[0]; counter++;
			contourGrid[counter] = d1*(double)i + T_leftbottom[1]; counter++;
		}
}


void getMedianC(int *n, int *p,double *Y, double *median)
{
	int counter = 0;
	for (int i = 0;i<n[0];i++)
	{
		double tmp[p[0]];
		for (int j = 0;j<p[0];j++) {tmp[j] = Y[counter]; counter++;}
		for (int j = 0;j<p[0]-1;j++)
			for (int k = j+1;k<p[0];k++)
				if (tmp[j]>tmp[k]) {double tmpp = tmp[j]; tmp[j]=tmp[k];tmp[k] = tmpp;}
		if (p[0] % 2 == 0) median[i] = (tmp[p[0]/2-1] + tmp[p[0]/2])/2;
		else median[i] = tmp[p[0]/2];
	}
}

// marginal deviation probability
// the probability of the deviation from ledian larger than epsilon
// n: number of locations
// m: sample size

void getMDPC(int * n, int * m, double * sampledYp, double * medYp, double *epsilon, double * MDP)
{
	int counter = 0;
	for(int i = 0;i<n[0];i++)
	{
		int MDPcounter = 0;
		for (int j = 0;j<m[0];j++)
		{
			if (sampledYp[counter]-medYp[i] > epsilon[0] || sampledYp[counter]-medYp[i] < -epsilon[0]) MDPcounter++;
			counter++;
		}
		MDP[i] = (double)MDPcounter/(double)m[0];
	}
}



