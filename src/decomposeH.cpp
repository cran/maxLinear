#include<stdio.h>
#include <vector>
#include <list>
#include <iostream>
#include <time.h>

using std::vector; 
using std::list;

class hittingScenarios
{
	public:
	hittingScenarios(const list<vector<int> > mHGI, list<vector<int> > Jss);
	void show() const;
	void showMustHitGroupIndex() const;
	void showJs() const;
	void saveFile(const char * = "MHGI.txt", const char * = "HHJs.txt") const;
	private:
	// Js and mHGI are independent!
	list<vector<int> > mustHitGroupIndex;
	list<vector<int> > Js;
};


bool HIsNice(list<vector<int > > H);
list<vector<int> > solveNiceH(list<vector<int> > H,int p);
list<vector<int> > projectH1(const list<vector<int> > & H, int p);

list< vector<int> > getH(const vector< vector<int> > &);
void saveMatrix(const vector<vector<int> > & matrix, int n, int p);
void saveList(const list<vector<int> > & H, const char * name);
void saveListCompact(const list<vector<int> > & H, const char * name);
vector<vector<int> > readMatrix(int &n, int &p);
bool alreadyHit(const vector<int> & , const vector<int> & hits);

//vector< vector<int> > decomposeH(vector<vector<int> > H, vector<int> mustHitIndex, int p);
list<vector<int> > decomposeH(vector<vector<int> > H, vector<int> mustHitIndex, int p);

//vector< vector<int> > decomposeHv1(vector<vector<int> > matrix, int n, int p);
list<vector<int> > decomposeHv1(vector<vector<int> > matrix, int n, int p);

//vector< vector<int> > decomposeHComplete(vector<vector<int> > matrix, int n, int p);
list<vector<int> > decomposeHComplete(vector<vector<int> > matrix, int n, int p);

void getMustHitIndex(vector<int> &, vector< vector<int> > &, int &);
void getMustHitIndex(vector<int> &, list<vector<int> > &, int &);
void getMustHitIndexOld(vector<int> &, vector< vector<int> > &, int &);
void getMustHitIndexOld(vector<int> &, list<vector<int> > &, int &);
void getMustHitIndexTypeII(vector<vector<int> > &, vector<int> &, vector<int> &, int &);
void getMustHitIndexTypeII(list<vector<int> > &, vector<int> &, vector<int> &, int &);
int getMustHitIndexTypeIIv4(list<vector<int> > & H, vector<int> &mustHitIndex, int &mHIRank, bool reorder = false, bool optimizationTypeV = false);

void combine(vector<vector<int> > &Js, vector<vector<int> > newJs);
void combine(list<vector<int> > &Js, list<vector<int> > newJs);
bool areTwoSetsStrictlyIntersecting(const vector<int> & set1, const vector<int> & set2);
bool set1MinusSet2IsNonempty(const vector<int> & set1, const vector<int> & set2);
void reduceHBySingleHit(vector<vector<int> > &, int );
void reduceHBySingleHit(list<vector<int> > &, int );
vector< vector<int> > decomposeHR(vector<vector<int> > , vector<int> , int , int &);
list<vector<int> > decomposeHR(list<vector<int> > , vector<int> , int , int &, bool optimizationTypeIII = false);
void decomposeHR(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, bool optimizationTypeIII);

void decomposeHRv4(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, bool optimizationTypeIII, bool optimizationTypeIV, bool optimizationTypeV);
void decomposeHRv4Core(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, int nbDisjointLines, bool optimizationTypeIII, bool optimizationTypeIV);


void removeHighRankJs(vector<vector<int> > &, int);
void removeHighRankJs(list<vector<int> > &, int);
int getRank(const vector<int> &);

bool isValidCover(const vector<vector<int> > &, vector<int> );
bool isValidCover(const list<vector<int> > &, vector<int> );
bool isLineHit(const vector<int> &line, const vector<int> &mustHitIndex);
bool areTwoSetsSame(const vector<int> &, const vector<int> &);
bool areTwoSetsDisjoint(const vector<int> &, const vector<int> &);
bool isHDisjoint(const list<vector<int> > & H);
void solveDisjointH(const list<vector<int> > & H, const vector<int> & mustHitIndex, list<vector<int> > & Js);
vector<vector<int> > checkJs(vector<vector<int> > , vector<vector<int> > );
void checkJs(const list<vector<int> > &, list<vector<int> > &);

void getColumnHits(vector<vector<int> > & columnHits,const list<vector<int> > &H);
void getMHITypeII(const vector<vector<int> > & columnHits, vector<int> &mHITypeII);
int reorderH(list<vector<int> > &H, const vector<vector<int> > &columnHits, bool oTV);
void reorderHLine(vector<int>  & HLine, const vector<vector<int> > & columnHits);

bool lineIsDisjoint(const vector<int> &Hline, const vector<vector<int> >& columnHits);

void test();
void showJs(vector< vector<int> >);
void showH(vector< vector<int> > );
void showList(const list<vector<int> > &);
void showListCompact(const list<vector<int> > &);
void showSet(vector< int > );
void showSetCompact(vector< int >, const char * = NULL );

vector<vector<int> > listToVector(const list<vector<int> > &H);
list<vector<int> > vectorToList(const vector<vector<int> > &H);


list<vector<int> > getH(const vector<vector<int> > & matrix)
{
	list<vector<int> > H;
	for (int i = 0; i < (int)matrix.size(); i++)
	{
		vector<int> line;
		for (int j = 0; j<(int)matrix[i].size(); j++)
			if (matrix[i][j] == 1) line.push_back(j);
		H.push_back(line);
		//printf("H[%d].size() = %d\n",i, line.size());
		//for (int j = 0; j<H[i].size(); j++) printf("%d ",H[i][j]);
		//printf("\n");
		
	}
	return H;
}

vector<vector<int> > listToVector(const list<vector<int> > &H)
{
	vector<vector<int> > newH;
	for(list<vector<int> >::const_iterator iter = H.begin();iter!=H.end();iter++)
		newH.push_back(*iter);
	return newH;
}

list<vector<int> > vectorToList(const vector<vector<int> > &H)
{
	list<vector<int> > newH;
	for(vector<vector<int> >::const_iterator iter = H.begin();iter!=H.end();iter++)
		newH.push_back(*iter);
	return newH;
}


void saveMatrix(const vector<vector<int> > & matrix, int n, int p)
{
	FILE *fp = fopen("matrix1.txt","w");
	fprintf(fp, "%d %d ", n, p);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
		fprintf(fp, "%d ", matrix[i][j]);
	fclose(fp);
}

void saveList(const list<vector<int> > & H, const char * name)
{
	FILE *fp = fopen(name,"w");
	for (list<vector<int> >::const_iterator iter = H.begin(); iter != H.end(); iter++)
		for (int i = 0; i < (int)(*iter).size(); i++)
			fprintf(fp, "%d ", (*iter)[i]);
	fprintf(fp,"\n");
	fclose(fp);
}

void saveListCompact(const list<vector<int> > & H, const char * name)
{
	FILE *fp = fopen(name,"w");
	fprintf(fp, "%d ", (int)H.size());
	for (list<vector<int> >::const_iterator iter = H.begin(); iter != H.end(); iter++)
		for (int i = 0; i < (int)(*iter).size(); i++)
			if ((*iter)[i] == 1) fprintf(fp, "%d ", i+1);
	fprintf(fp,"\n");
	fclose(fp);
}

vector<vector<int> > readMatrix(int &n, int &p)
{
	FILE *fp = fopen("matrix.txt", "r");
	if (!fscanf(fp, "%d %d ",&n, &p)) printf("errors during reading matrix.txt.\n");
	vector<vector<int> > matrix;
	for (int i = 0; i < n; i++)
	{
	vector<int> line;
		for (int j = 0; j < p; j++)
		{
			int k;
		    if(!fscanf(fp, "%d ", &k)) printf("errors during reading matrix.txt.\n");
		    line.push_back(k);
		}
		matrix.push_back(line);
		//for (int j = 0; j < p; j++) printf("%d ", matrix[i][j]); printf("\n");
	}
	fclose(fp);
	return matrix;
}

bool alreadyHit(const vector<int> &h, const vector<int> &hits)
{
	for (int i = 0; i<(int)h.size(); i++)
	{
		if (h[i]>=(int)hits.size()) printf("error!!!!\n");
		if (hits[h[i]] == 1) return true;
    }
	return false;
}

bool isValidCover(const list<vector<int> > &H, vector<int> J)
{
	for(list<vector<int> >::const_iterator iter = H.begin();iter!=H.end();iter++)
	{
		bool notCovered = true;
		for (int j = 0;j<(int)(*iter).size();j++)
			if (J[(*iter)[j]] == 1) {notCovered = false; break;}
		if (notCovered) return false;
	}
	return true;
}

void checkJs(const list<vector<int> > & H, list<vector<int> > & Js)
{
	for(list<vector<int> >::const_iterator iter = Js.begin();iter!= Js.end();iter++)
		if (!isValidCover(H,*iter)) 
		{
			printf("invalid cover detected!\n");
			showList(H);
			showSetCompact(*iter);
			return;//exit(0);
		}
	
	if (Js.size() <= 1) return;
	for(list<vector<int> >::iterator iter1 = Js.begin(); iter1!=Js.end(); iter1++)
	{
		list<vector<int> >::iterator iter2 = iter1; iter2++;
		for(; iter2!=Js.end(); iter2++)
			if (areTwoSetsSame(*iter1,*iter2)) 
			{
				//printf("same Js detected!!\n"); 
				iter2 = Js.erase(iter2);iter2--; 
				//break;
			}
			//else printf("different Js!\n");
	}
}

bool areTwoSetsSame(const vector<int> & set1, const vector<int> & set2)
{
	if (set1.size() != set2.size()) return false;
	for (int i = 0;i<(int)set1.size();i++)
		if (set1[i]!=set2[i]) return false;
	return true;
}

bool areTwoSetsDisjoint(const vector<int> & set1, const vector<int> & set2)
{
	for (int i = 0;i<(int)set1.size();i++)
		for (int j = 0;j<(int)set2.size();j++)
			if (set1[i] == set2[j]) return false;
	return true;
}

bool isHDisjoint(const list<vector<int> > & H)
{
	for (list<vector<int> >::const_iterator iter = H.begin(); iter!=H.end(); iter++)
	{
		list<vector<int> >::const_iterator iter2 = iter; iter2++;
		for (; iter2!=H.end(); iter2++)
			if (!areTwoSetsDisjoint(*iter,*iter2)) return false;
	}
	return true;
}

void solveDisjointH(const list<vector<int> > & H, const vector<int> & mustHitIndex, list<vector<int> > & Js)
{
	//printf("solve disjoint H.\n"); showList(H);
	int n = H.size();
	if (n <= 0) return;
	vector<int> v(n,-1);
	
	long int totalN = 1;
	for(list<vector<int> >::const_iterator iter = H.begin(); iter != H.end(); iter++)
		totalN = totalN * (long int)(*iter).size();
	if (totalN > 100000) 
	{
		for(list<vector<int> >::const_iterator iter = H.begin(); iter != H.end(); iter++)
			printf("%d ",(int)(*iter).size());
		printf("Total size of H larger than %ld! Aborted.\n", totalN);
		FILE *fp = fopen("Js.txt","w"); fprintf(fp, "%ld ", totalN);fclose(fp);
		return; //exit(0);
	}
	
	int i = 0; list<vector<int> >::const_iterator iter = H.begin();
	vector<int> J = mustHitIndex;
	//printf("^");	showSetCompact(J);	showListCompact(H);
	while(true)
	{
		//printf("level %d(%d)\n", i,v[i]);
		v[i]++;
		if (v[i]>0) J[(*iter)[v[i]-1]] = 0;
		if (v[i] == (int)(*iter).size()) 
		{
			v[i] = -1;
			i--; if (i == -1) break;
			iter--; continue;
		}
		J[(*iter)[v[i]]] = 1;
		if (i == n-1) {Js.push_back(J); continue;}
		i++; iter++;
	}	
	//printf("v");
}


// update &mHI, &mHIRank and H
void getMustHitIndex(vector<int> &mustHitIndex, list<vector<int> > &H, int &mHIRank)
{
	bool anotherRound;
	do
	{
		anotherRound = false;
		for (list<vector<int> >::iterator iter = H.begin();iter !=H.end() ; iter++)
			if ((*iter).size() == 1) 
			{
				mustHitIndex[(*iter)[0]] = 1; mHIRank++;
				anotherRound = true;
				reduceHBySingleHit(H,(*iter)[0]);
				break;
			}
	}while(anotherRound == true);
	
	return;	
}

// old version
void getMustHitIndexOld(vector<int> &mustHitIndex, list<vector<int> > &H, int &mHIRank)
{
	bool anotherRound = false;
	do
	{
		anotherRound = false;
		for (list<vector<int> >::iterator iH = H.begin(); iH != H.end() ; iH++)
		{
			if ((*iH).size() == 1) 
			{
				mustHitIndex[(*iH)[0]] = 1; mHIRank++;
				anotherRound = true;
				iH = H.erase(iH);iH--;
				continue;
			}
			
			for (int j = 0; j < (int)mustHitIndex.size(); j++)
			{
				if (isLineHit((*iH),mustHitIndex)) 
				{
					iH = H.erase(iH);iH--;
					break;
				}
			}
		}
	}while(anotherRound == true);
	
	return;	
}


bool isLineHit(const vector<int> &line, const vector<int> &mustHitIndex)
{
	for (int i = 0;i<(int)line.size();i++)
		if (mustHitIndex[line[i]] == 1) return true;
	return false;
}


// put unique TypeII MHI into &MHI, update &mHIRank, update and return H, 
// put nonunique TypeII MHI into &nonuniqueMHI
void getMustHitIndexTypeII(list<vector<int> > & H, vector<int> &mustHitIndex, vector<int> &nonuniqueMHI, int &mHIRank)
{
	vector<vector<int> > columnHits((int)mustHitIndex.size());
	int line = 0;
	for (list<vector<int> >::iterator iter = H.begin();iter!=H.end();iter++, line++)
        for (int j = 0;j<(int)(*iter).size();j++) 
			columnHits[(*iter)[j]].push_back(line);
	
	vector<int> mHITypeII;
	for (int j = 0;j<(int)columnHits.size();j++)
	{
		if ((int)columnHits[j].size()<=1) continue;
		bool isTypeII = true;
		for (int jj = 0;jj<(int)columnHits.size();jj++)
			{
			if ((int)columnHits[jj].size()<=1) continue;
			if (areTwoSetsStrictlyIntersecting(columnHits[j],columnHits[jj]))
				{isTypeII = false; break;}
			}
		if (isTypeII) mHITypeII.push_back(j);
	}
	//printf("TypeII indices:"); showSet(mHITypeII);
	// test uniqueness of the MHI(typeII). 
	// Uniqueness: the column-hits of a MHI(typeII) is not intersecting with any other MHI(typeII).	
	if ((int)mHITypeII.size() == 1) 
	{
		//printf("unique type-II index: %d\n", mHITypeII[0]);
		mustHitIndex[mHITypeII[0]] = 1; mHIRank++;
		reduceHBySingleHit(H,mHITypeII[0]);
		return;
	}
	if ((int)mHITypeII.size() > 1) printf("mHITypeII.size()>1.\n");
	for (int i1 = 0;i1<(int)mHITypeII.size()-1; i1++)
	{
		bool isUnique = true; 
		for (int i2 = i1 + 1; i2<(int)mHITypeII.size(); i2++)
		{
			if (areTwoSetsStrictlyIntersecting(columnHits[mHITypeII[i1]],columnHits[mHITypeII[i2]])) 
			{
				nonuniqueMHI.push_back(mHITypeII[i1]);
				nonuniqueMHI.push_back(mHITypeII[i2]);
				isUnique = false;
				break;
			}
		}
		if (isUnique) 
		{
			//printf("unique type-II index: %d\n", mHITypeII[i1]);
			mustHitIndex[mHITypeII[i1]] = 1; mHIRank++;
			reduceHBySingleHit(H,mHITypeII[i1]);
		}
	}
	return;
}

void getColumnHits(vector<vector<int> > & columnHits,const list<vector<int> > &H)
{
	int line = 0;
	for (list<vector<int> >::const_iterator iter = H.begin();iter!=H.end();iter++, line++)
        for (int j = 0;j<(int)(*iter).size();j++) 
			columnHits[(*iter)[j]].push_back(line);
}

void getMHITypeII(const vector<vector<int> > & columnHits, vector<int> &mHITypeII)
{
	//for (int i = 0;i<(int)columnHits.size();i++) showSet(columnHits[i]);
	for (int j = 0;j<(int)columnHits.size();j++)
	{
		if ((int)columnHits[j].size()<=1) continue;
		bool isTypeII = true;
		for (int jj = 0;jj<(int)columnHits.size();jj++)
			{
			if ((int)columnHits[jj].size()<=1) continue;
			if (areTwoSetsStrictlyIntersecting(columnHits[j],columnHits[jj]))
				{isTypeII = false; break;}
			}
		if (isTypeII) mHITypeII.push_back(j);
	}
}

int getMustHitIndexTypeIIv4(list<vector<int> > & H, vector<int> &mustHitIndex, int &mHIRank, bool reorder, bool optimizationTypeV)
{
	if (H.size() <= 1) return 0;
	vector<vector<int> > columnHits((int)mustHitIndex.size());
	getColumnHits(columnHits,H);
	//showList(H); printf("columnHits[1]:"); showSet(columnHits[1]);
	vector<int> mHITypeII;
	getMHITypeII(columnHits,mHITypeII);
	//printf("TypeII indices:"); showSet(mHITypeII);
	// test uniqueness of the MHI(typeII). 
	// Uniqueness: the column-hits of a MHI(typeII) is not intersecting with any other MHI(typeII).	
	if ((int)mHITypeII.size() == 1) 
	{
		//printf("unique type-II index: %d\n", mHITypeII[0]);
		mustHitIndex[mHITypeII[0]] = 1; mHIRank++;
		reduceHBySingleHit(H,mHITypeII[0]);
		return 0;
	}
	//printf("before reorder H.\n"); showList(H);
	int nbDisjointLines = 0;
	//if (reorder) printf("reorder!\n");
	if (reorder && H.size()>1)
	{
		//printf("<H.size() = %d, ",H.size()); printf("columnHits[1].size() = %d", columnHits[1].size()); showList(H);
		//showList(H);
		nbDisjointLines = reorderH(H,columnHits, optimizationTypeV);
		//showList(H); //printf("H.size() = %d>\n",H.size());
	}
	//printf("after reorder H.\n"); showList(H);
	return nbDisjointLines;
}


int reorderH(list<vector<int> > &H, const vector<vector<int> > &columnHits, bool oTV)
{
	printf("reorder H. "); if (oTV) printf("oTV."); printf("\n");
	//int c = 0, c1 = 0;
	if (H.size() <= 1) return H.size();
	vector<list<vector<int> >::iterator> iters;
	for(list<vector<int> >::iterator iter = H.begin();iter != H.end(); iter++)
	{
		//printf("c = %d(%d), c1 = %d\n",c,H.size(),c1);
		//showList(H);
		if (lineIsDisjoint(*iter,columnHits)) 
			iters.push_back(iter);
		else if (oTV)
			{reorderHLine(*iter,columnHits);}
	}
	for (int i = 0;i<(int)iters.size();i++)
	{
		H.push_back(*iters[i]);
		H.erase(iters[i]);
	}
	return (int)iters.size();
	
}

void reorderHLine(vector<int>  & HLine, const vector<vector<int> > & columnHits)
{
	for(int i = 0;i<(int)HLine.size()-1;i++)
		for(int j = i+1;j<(int)HLine.size();j++)
		{
			if (columnHits[HLine[i]].size() < columnHits[HLine[j]].size())
			{int tmp = HLine[i]; HLine[i]=HLine[j]; HLine[j] = tmp;}
		}
}
bool lineIsDisjoint(const vector<int> &Hline, const vector<vector<int> >& columnHits)
{
		for (int i = 0;i<(int)Hline.size();i++)
			if (columnHits[Hline[i]].size() > 1)
				return false;
		return true;
}

// strictly intersecting: Set1\setminus Set2, Set2\setminus Set1 Set1\cap Set2 are all nonempty.
bool areTwoSetsStrictlyIntersecting(const vector<int> & set1, const vector<int> & set2)
{
	if (areTwoSetsDisjoint(set1,set2)) return false;
	if (set1MinusSet2IsNonempty(set1,set2) & set1MinusSet2IsNonempty(set2,set1)) return true;
	return false;
}

bool set1MinusSet2IsNonempty(const vector<int> & set1, const vector<int> & set2)
{
	bool Set1MinusSet2IsNonempty = false;	
	for(int i = 0; i<(int)set1.size();i++)
	{
		bool iIsinSet2 = false;
		for(int j = 0; j<(int)set2.size();j++)
			if (set1[i] == set2[j]) {iIsinSet2 = true; break;}
		if (!iIsinSet2) {Set1MinusSet2IsNonempty = true;break;}
	}
	return Set1MinusSet2IsNonempty;
}


void reduceHBySingleHit(list<vector<int> > & H, int j)
{
	//showList(H); printf("single hit: %d\n",j);
	//printf("<<");
	for(list<vector<int> >::iterator iter = H.begin(); iter!=H.end(); iter++)
		for(int i = 0;i<(int)(*iter).size();i++)
			if ((*iter)[i] == j) {iter = H.erase(iter); iter--; break;}
	//printf(">>");
}

void showList(const list<vector<int> > & H)
{
	printf("====================================\n");
	for (list<vector<int> >::const_iterator iter = H.begin(); iter!=H.end(); iter++)
	{
		printf("[%d] ",(int)(*iter).size());
		for (int j = 0;j<(int)(*iter).size(); j++)
			printf("%d ",(*iter)[j]);
		printf("\n");
	}
	printf("====================================\n");
}

void showListCompact(const list<vector<int> > & H)
{
	printf("====================================\n");
	for (list<vector<int> >::const_iterator iter = H.begin(); iter!=H.end(); iter++)
	{
		for (int j = 0;j<(int)(*iter).size(); j++)
			if ((*iter)[j] == 1) printf("%d ",j);
		printf("\n");
	}
	printf("====================================\n");
}

void showSet(vector< int > set)
{
	for (int i = 0;i<(int)set.size();i++)
		printf("%d ",set[i]);
	printf("\n");
}

void showSetCompact(vector< int > set, const char * text)
{
	printf("%s ",text);
	for (int i = 0;i<(int)set.size();i++)
		if (set[i] == 1) printf("%d ",i);
	printf("\n");
}


void removeHighRankJs(list<vector<int> > & Js, int rank)
{
	//int counter = 0;
	for (list<vector<int> >::iterator iter = Js.begin(); iter!=Js.end();iter++)
	{
		//if (counter % 10000 == 0) printf("remove high rank Js checking: counter == %d\n", counter);	
		//int r = getRank(*iter); printf("rank = %d\n",r);
		if (getRank((*iter)) > rank) {iter = Js.erase(iter);iter--;}
		//counter++;
	}
}

int getRank(const vector<int> & set)
{
	int rank = 0;
	for (int i = 0;i<(int)set.size();i++)
		if (set[i] == 1) rank++;
	return rank;
}

// decompose H recursively
void decomposeHR(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, bool optimizationTypeIII)
{
	getMustHitIndex(mustHitIndex, H, mHIRank);
	//showSet(mustHitIndex); showList(H);
	if (mHIRank > rank) return;

	vector<int> nonuniqueMHI;
	//showList(H);showSet(mustHitIndex);
	getMustHitIndexTypeII(H,mustHitIndex,nonuniqueMHI, mHIRank);
	//printf("after get MHI-II, H and mHI\n");showList(H);showSet(mustHitIndex);
	if (mHIRank > rank) return;
	
	if (nonuniqueMHI.size() == 0)
	{
		if (H.size() == 0) {Js.push_back(mustHitIndex); rank = mHIRank; return;}

		// simplification type-III
		if (optimizationTypeIII && isHDisjoint(H)) 
		{
			//printf("rank = %d, mHIrank = %d, H.size() = %d\n", rank, mHIRank, H.size()); printf("solve disjoint H.\n");
			//showSetCompact(mustHitIndex); showList(H);
			if (mHIRank + (int)H.size() > rank) return;
			rank = mHIRank + H.size();
			solveDisjointH(H,mustHitIndex,Js); 
			return ;
		}

		for (int i = 0; i<(int)H.front().size();i++)
		{
			list<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = tmpH.front()[i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			decomposeHR(tmpH,tmpMHI,Js,mHIRank+1,rank,optimizationTypeIII);
		}
		return;
	}
	else
	{
		//list<vector<int> > Js;
		for (int i = 0; i<(int)nonuniqueMHI.size(); i++)
		{
			list<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = nonuniqueMHI[i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			decomposeHR(tmpH,tmpMHI,Js,mHIRank+1,rank,optimizationTypeIII);
		}
		return;
	}
}

// decompose H recursively
void decomposeHRv4(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, bool optimizationTypeIII, bool optimizationTypeIV, bool optimizationTypeV)
{
	getMustHitIndex(mustHitIndex, H, mHIRank);
	//printf("***\n");showSet(mustHitIndex); showList(H);
	if (H.size() == 0) {Js.push_back(mustHitIndex); rank = mHIRank; return;}
	if (mHIRank > rank) {printf("WARNING!");return;}

	//showList(H);showSet(mustHitIndex);printf("H.size() = %d\n",H.size());
	int nbDisjointLines = getMustHitIndexTypeIIv4(H,mustHitIndex, mHIRank,true, optimizationTypeV);	
	//showSetCompact(mustHitIndex,"MHI");
	if (H.size() == 0) {Js.push_back(mustHitIndex); rank = mHIRank; return;}
	//printf("after TypeIIv4\n");//showList(H);//showSet(mustHitIndex);//printf("Number of disjoint lines = %d\n", nbDisjointLines);//printf("mHIRank = %d, rank = %d\n", mHIRank, rank);//showSet(mustHitIndex);
	
	decomposeHRv4Core(H,mustHitIndex,Js,mHIRank,rank,nbDisjointLines,optimizationTypeIII,optimizationTypeIV);
	return;
}

void decomposeHRv4Core(list<vector<int> > &H, vector<int> mustHitIndex, list<vector<int> > & Js, int mHIRank, int &rank, int nbDisjointLines, bool optimizationTypeIII, bool optimizationTypeIV)
{
	if (H.size() == 0) {printf("warning!\n");return;}
	if (mHIRank >= rank) return;
	//showList(H);showSet(mustHitIndex);printf("H.size() = %d\n",H.size());
			
	getMustHitIndexTypeIIv4(H,mustHitIndex,mHIRank);
	//showSetCompact(mustHitIndex,"MHI");printf("H.size() = %d, rank = %d, mHIRank = %d\n", H.size(), rank, mHIRank);
	if (H.size() == 0) 
		{Js.push_back(mustHitIndex); rank = mHIRank;return;}
	//printf("Js.size() = %d\n",Js.size());
	// simplification type-III
	//if (optimizationTypeIII && nbDisjointLines >= (int)H.size())
	if ((optimizationTypeIII && isHDisjoint(H)) || (optimizationTypeIV && nbDisjointLines+1 >= (int)H.size()))
	{
		//if (optimizationTypeIII) printf("o3 H.size() = %d, nbDisjointLines = %d\n", H.size(), nbDisjointLines);
		//if (optimizationTypeIV) printf("o4 H.size() = %d\n",H.size());
		//printf("rank = %d, mHIrank = %d, H.size() = %d\n", rank, mHIRank, H.size()); printf("solve disjoint H.\n");
		//showSetCompact(mustHitIndex); showList(H);
		//printf("<>");
		if (mHIRank + (int)H.size() > rank) return;
		rank = mHIRank + H.size();
		solveDisjointH(H,mustHitIndex,Js); 
		//printf(">");
		return ;
	}
	//showList(H); printf("$$$ H.size() = %d\n",H.size());
	for (int i = 0; i<(int)H.front().size(); i++)
	{
		list<vector<int> > tmpH = H;
		vector<int> tmpMHI = mustHitIndex;
		//printf("H.front().size() = %d, i = %d\n",H.front().size(),i); showList(H);
		int hit = H.front()[i]; 
		//printf("??");	printf("hit = %d\n",hit);
		if (hit == -1) {showList(H); printf("WRONG! hit == -1!\n"); return;//exit(0);
		}
		tmpMHI[hit] = 1;
		//showList(tmpH);
		reduceHBySingleHit(tmpH,hit); 
		//showList(H);
		if (tmpH.size() == 0) 
		{
			if (mHIRank < rank)
				{Js.push_back(tmpMHI); rank = mHIRank + 1;}	//printf("%d ",rank);}
			continue;
		}
		int tmpMHIRank = mHIRank + 1;
		//printf("]");
		decomposeHRv4Core(tmpH,tmpMHI,Js,tmpMHIRank,rank, nbDisjointLines,optimizationTypeIII, optimizationTypeIV);
	}
	return;

}



list<vector<int> > decomposeHR(list<vector<int> > H, vector<int> mustHitIndex, int mHIRank, int &rank, bool optimizationTypeIII)
{
	printf("!!!\n");
	getMustHitIndex(mustHitIndex, H, mHIRank);
	//showSet(mustHitIndex); showList(H);
	if (mHIRank > rank) return list<vector<int> >(0);

	vector<int> nonuniqueMHI;
	//showList(H);showSet(mustHitIndex);
	getMustHitIndexTypeII(H,mustHitIndex,nonuniqueMHI, mHIRank);
	//printf("after get MHI-II, H and mHI\n");showList(H);showSet(mustHitIndex);
	//return H;
	if (mHIRank > rank) return list<vector<int> >(0);
	
	if (nonuniqueMHI.size() == 0)
	{
		list<vector<int> > Js;

		if (H.size() == 0) {Js.push_back(mustHitIndex); rank = mHIRank; return Js;}

		// simplification type-III
		if (optimizationTypeIII && isHDisjoint(H)) {printf("!!!!!");solveDisjointH(H,mustHitIndex,Js); return Js;}

		for (int i = 0; i<(int)H.front().size();i++)
		{
			list<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = tmpH.front()[i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			combine(Js,decomposeHR(tmpH,tmpMHI,mHIRank+1,rank,optimizationTypeIII));
		}
		return Js;
	}
	else
	{
		printf("There are nonunique must-hit-indices.\n");
		list<vector<int> > Js;
		for (int i = 0; i<(int)nonuniqueMHI.size(); i++)
		{
			list<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = nonuniqueMHI[i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			combine(Js,decomposeHR(tmpH,tmpMHI,mHIRank+1,rank,optimizationTypeIII));
		}
		return Js;
	}
}


void combine(list<vector<int> > &Js, list<vector<int> > newJs)
{
	for (list<vector<int> >::iterator iter = newJs.begin();iter!=newJs.end();iter++)
		Js.push_back((*iter));
}





// slow. every time construct a list<vector<int> >. Obsolete.
list<vector<int> > decomposeH(vector<vector<int> > H, vector<int> mustHitIndex, int p)
{
	int n = H.size();
	vector<int> v(n,-1);
	vector<int> hits = mustHitIndex;
    //for (vector<int>::iterator iter = mustHitIndex.begin(); iter != mustHitIndex.end(); iter++)         hits[*iter] = 1;
	list<vector<int> > Js;
	int q = 0;
	int counter = 0;
	int rank = p;int currentRank = 0; for (int i = 0; i<(int)hits.size(); i++) if (hits[i]==1) currentRank++;
	while(true)
	{
		counter ++; //if (counter > 200) break;
		//printf("(%d) q = %d, v[q] = %2d H[q].size() = %d n = %d currentRank/rank = %d/%d\n",counter, q,v[q],(int)H[q].size(),n, currentRank,rank);
		//for (int i = 0; i<hits.size(); i++) printf("%d ", hits[i]); printf("\n");
		if (q == n) //find one cover set!!
			{
				Js.push_back(hits); 
				if (currentRank<rank) rank = currentRank;
				q--; if (q == -1) break; 
                if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
				v[q]++; continue;
			}
		if ((v[q]<-1) || (v[q]>(int)H[q].size())) printf("error!! v[q] = %d, H[q].size() = %d\n", v[q], H[q].size());
		if (v[q]>(int)H[q].size()) printf("error 1!! v[q] = %d, H[q].size() = %d\n", v[q], H[q].size());
		if (v[q]<-1) printf("error 2!! v[q] = %d, H[q].size() = %d\n", v[q], H[q].size());
		if (v[q] == (int)H[q].size())  //v[q] exceeds the range.
			{
				v[q] = -1; q--; if (q == -1) break; 
				if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
				v[q]++; continue;
			}
		if (v[q] == -1) // arrive at q from q-1
			if (alreadyHit(H[q],hits)) {q++;continue;} //printf("already hit!\n"); 
				else v[q]++;//{printf("not hit yet!\n");}
		//printf("v[q] = %d, H[q].size() = %d\n", v[q], H[q].size());
		if (hits[H[q][v[q]]] == 1) //arrive at q from q+1, v[q]>=0 in this case, but hits not updated for q yet.
			{v[q]++; continue;}
		if (currentRank == rank) 
		{
			v[q] = -1; q--; if (q == -1) break;
			if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
			v[q]++; continue;
		}
		hits[H[q][v[q]]] = 1; currentRank++; 
		q++;
	}
	//printf("Js.size() = %d, rank = %d\n", Js.size(),rank);
	for (list<vector<int> >::iterator iter = Js.begin(); iter!=Js.end(); iter++) 
	{
		int tmpRank = 0; for (int i = 0; i<(int)(*iter).size(); i++) if((*iter)[i] == 1) tmpRank++;
		if (tmpRank>rank) {iter = Js.erase(iter);iter--;}
	}
	printf("counter = %d\n", counter);
	return Js;
}

// decomposeH version 1, use rank to speed up. but no order adjustment.
list<vector<int> > decomposeHv1(vector<vector<int> > matrix, int n, int p)
{
	vector<int> v(n,-1);
	vector<int> hits(p,0);
	vector<vector<int> > H = listToVector(getH(matrix));
	list<vector<int> > Js;
	int q = 0;
	int counter = 0;
	int rank = p;int currentRank = 0;
	while(true)
	{
		counter ++; //if (counter > 200) break;
		//printf("(%d) q = %d, v[q] = %2d n = %d currentRank/rank = %d/%d ||",counter, q,v[q],n, currentRank,rank);
		//for (int i = 0; i<hits.size(); i++) printf("%d ", hits[i]); printf("\n");
		if (q == n) //find one cover set!!
			{
				Js.push_back(hits); 
				if (currentRank<rank) rank = currentRank;
				q--; if (q == -1) break; 
                if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
				v[q]++; continue;
			}
		if (v[q] == (int)H[q].size())  //v[q] exceeds the range.
			{
				v[q] = -1; q--; if (q == -1) break; 
				if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
				v[q]++; continue;
			}
		if (v[q] == -1) // arrive at q from q-1
			if (alreadyHit(H[q],hits)) {q++;continue;} 
				else v[q]++; 
		if (hits[H[q][v[q]]] == 1) //arrive at q from q+1, v[q]>=0 in this case, but hits not updated for q yet.
			{v[q]++; continue;}
		if (currentRank == rank) 
		{
			v[q] = -1; q--; if (q == -1) break;
			if (v[q]>=0) {hits[H[q][v[q]]] = 0; currentRank--;}
			v[q]++; continue;
		}
		hits[H[q][v[q]]] = 1; currentRank++; 
		q++;
	}
	
	for (list<vector<int> >::iterator iter = Js.begin(); iter!=Js.end(); iter++) 
	{
		int tmpRank = 0; for (int i = 0; i<(int)(*iter).size(); i++) if((*iter)[i] == 1) tmpRank++;
		if (tmpRank>rank) {iter = Js.erase(iter);iter--;}
	}
	printf("counter = %d\n", counter);
	return Js;
}


// decompose H to have Js for ALL ranks.
list<vector<int> > decomposeHComplete(vector<vector<int> > matrix, int n, int p)
{
	vector<int> v(n,-1);
	vector<int> hits(p,0);
	vector<vector<int> > H = listToVector(getH(matrix));
	list<vector<int> > Js;
	int q = 0;
	int counter = 0;
	while(true)
	{
		counter ++; //if (counter > 200) break;
		//printf("(%d) q = %d, v[q] = %2d n = %d ",counter, q,v[q],n);
		//for (int i = 0; i<hits.size(); i++) printf("%d ", hits[i]); printf("\n");
		if (q == n) //find one cover set!!
			{
                 Js.push_back(hits); q--; if (q == -1) break; 
                 if (v[q]>=0) hits[H[q][v[q]]] = 0; 
				 v[q]++; continue;
			}
		if (v[q] == (int)H[q].size())  //v[q] exceeds the range.
			{
				v[q] = -1; q--; if (q == -1) break; 
				if (v[q]>=0) hits[H[q][v[q]]] = 0;
				v[q]++; continue;
			}
		if (v[q] == -1) // arrive at q from q-1
			if (alreadyHit(H[q],hits)) {q++;continue;} 
				else v[q]++; 
		if (hits[H[q][v[q]]] == 1) //arrive at q from q+1, v[q]>=0 in this case, but hits not updated for q yet.
			{v[q]++; continue;}
		hits[H[q][v[q]]] = 1;
		q++;
	}
	return Js;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool isValidCover(const vector<vector<int> > &H, vector<int> J)
{
	for(int i = 0;i<(int)H.size();i++)
	{
		bool notCovered = true;
		for (int j = 0;j<(int)H[i].size();j++)
			if (J[H[i][j]] == 1) {notCovered = false; break;}
		if (notCovered) return false;
	}
	return true;
}

vector<vector<int> > checkJs(vector<vector<int> > H, vector<vector<int> > Js)
{
	for(int i = 0;i<(int)Js.size();i++)
		if (!isValidCover(H,Js[i])) printf("invalid cover detected!\n");
	
	if (Js.size() <= 1) return Js;
	for(vector<vector<int> >::iterator iter1 = Js.begin(); iter1+1<Js.end(); iter1++)
	{
		vector<vector<int> >::iterator iter2 = iter1; iter2++;
		for(; iter2!=Js.end(); iter2++)
			if (areTwoSetsSame(*iter1,*iter2)) 
			{
				//printf("same Js detected!!\n"); 
				Js.erase(iter2); iter2--; 
				//break;
			}
			//else printf("different Js!\n");
	}
	return Js;
}



// update &mHI, &mHIRank and H
void getMustHitIndex(vector<int> &mustHitIndex, vector<vector<int> > &H, int &mHIRank)
{
	bool anotherRound;
	do
	{
		anotherRound = false;
		for (int i = 0; i<(int)H.size() ; i++)
			if (H[i].size() == 1) 
			{
				mustHitIndex[H[i][0]] = 1; mHIRank++;
				anotherRound = true;
				reduceHBySingleHit(H,H[i][0]);
				break;
			}
	}while(anotherRound == true);
	
	return;	
}

// old version
void getMustHitIndexOld(vector<int> &mustHitIndex, vector<vector<int> > &H, int &mHIRank)
{
	bool anotherRound = false;
	do
	{
		anotherRound = false;
		for (vector<vector<int> >::iterator iH = H.begin(); iH != H.end() ; iH++)
		{
			if ((*iH).size() == 1) 
			{
				mustHitIndex[(*iH)[0]] = 1; mHIRank++;
				anotherRound = true;
				H.erase(iH); iH--;
				continue;
			}
			
			for (int j = 0; j < (int)mustHitIndex.size(); j++)
			{
				if (isLineHit((*iH),mustHitIndex)) 
				{
					H.erase(iH); iH--;
					break;
				}
			}
		}
	}while(anotherRound == true);
	
	return;	
}




// put unique TypeII MHI into &MHI, update &mHIRank, update and return H, 
// put nonunique TypeII MHI into &nonuniqueMHI
void getMustHitIndexTypeII(vector<vector<int> > & H, vector<int> &mustHitIndex, vector<int> &nonuniqueMHI, int &mHIRank)
{
	vector<vector<int> > columnHits((int)mustHitIndex.size());
	for (int i=0;i<(int)H.size();i++)
		for (int j = 0;j<(int)H[i].size();j++) 
			columnHits[H[i][j]].push_back(i);
	
	vector<int> mHITypeII;
	for (int j = 0;j<(int)columnHits.size();j++)
	{
		if ((int)columnHits[j].size()<=1) continue;
		bool isTypeII = true;
		for (int jj = 0;jj<(int)columnHits.size();jj++)
			{
			if ((int)columnHits[jj].size()<=1) continue;
			if (areTwoSetsStrictlyIntersecting(columnHits[j],columnHits[jj]))
				{isTypeII = false; break;}
			}
		if (isTypeII) mHITypeII.push_back(j);
	}
	
	//printf("TypeII indices:"); showSet(mHITypeII);


	
	// test uniqueness of the MHI(typeII). 
	// Uniqueness: the column-hits of a MHI(typeII) is not intersecting with any other MHI(typeII).	
	if ((int)mHITypeII.size() == 1) 
	{
		//printf("unique type-II index: %d\n", mHITypeII[0]);
		mustHitIndex[mHITypeII[0]] = 1; mHIRank++;
		reduceHBySingleHit(H,mHITypeII[0]);
		return;
	}
	for (int i1 = 0;i1<(int)mHITypeII.size()-1; i1++)
	{
		bool isUnique = true; 
		for (int i2 = i1 + 1; i2<(int)mHITypeII.size(); i2++)
		{
			if (areTwoSetsStrictlyIntersecting(columnHits[mHITypeII[i1]],columnHits[mHITypeII[i2]])) 
			{
				nonuniqueMHI.push_back(mHITypeII[i1]);
				nonuniqueMHI.push_back(mHITypeII[i2]);
				isUnique = false;
				break;
			}
		}
		if (isUnique) 
		{
			//printf("unique type-II index: %d\n", mHITypeII[i1]);
			mustHitIndex[mHITypeII[i1]] = 1; mHIRank++;
			reduceHBySingleHit(H,mHITypeII[i1]);
		}
	}
	return;
}

// strictly intersecting: Set1\setminus Set2 and Set2\setminus Set1 are both nonempty.

void reduceHBySingleHit(vector<vector<int> > & H, int j)
{
	for(vector<vector<int> >::iterator iter = H.begin(); iter!=H.end(); iter++)
		for(int i = 0;i<(int)(*iter).size();i++)
			if ((*iter)[i] == j) {H.erase(iter); iter--; break;}
}

void showH(vector< vector<int> > H)
{
	for (int i = 0; i<(int)H.size();i++)
	{
		for (int j = 0;j<(int)H[i].size(); j++)
			printf("%d ",H[i][j]);
		printf("\n");
	}
}

void removeHighRankJs(vector<vector<int> > & Js, int rank)
{
	for (vector<vector<int> >::iterator iter = Js.begin(); iter!=Js.end();iter++)
	{
		//int r = getRank(*iter); printf("rank = %d\n",r);
		if (getRank((*iter)) > rank) {Js.erase(iter); iter--;}
	}
}


// decompose H recursively
vector< vector<int> > decomposeHR(vector<vector<int> > H, vector<int> mustHitIndex, int mHIRank, int &rank)
{
	getMustHitIndex(mustHitIndex, H, mHIRank);
	if (mHIRank > rank) return vector<vector<int> >(0);

	vector<int> nonuniqueMHI;
	//showH(H);showSet(mustHitIndex);
	getMustHitIndexTypeII(H,mustHitIndex,nonuniqueMHI, mHIRank);
	//showH(H);showSet(mustHitIndex);
	if (mHIRank > rank) return vector<vector<int> >(0);
	
	if (nonuniqueMHI.size() == 0)
	{
		vector<vector<int> > Js;
		if (H.size() == 0) {Js.push_back(mustHitIndex); rank = mHIRank; return Js;}

		for (int i = 0; i<(int)H[0].size();i++)
		{
			vector<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = tmpH[0][i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			combine(Js,decomposeHR(tmpH,tmpMHI,mHIRank+1,rank));
		}
		return Js;
	}
	else
	{
		vector<vector<int> > Js;
		for (int i = 0; i<(int)nonuniqueMHI.size(); i++)
		{
			vector<vector<int> > tmpH = H;
			vector<int> tmpMHI = mustHitIndex;
			int hit = nonuniqueMHI[i]; tmpMHI[hit] = 1;
			reduceHBySingleHit(tmpH,hit);
			combine(Js,decomposeHR(tmpH,tmpMHI,mHIRank+1,rank));
		}
		return Js;
	}
}

void combine(vector<vector<int> > &Js, vector<vector<int> > newJs)
{
	for (int i = 0;i < (int)newJs.size(); i++)
		Js.push_back(newJs[i]);
}


void showJs(vector< vector< int > > Js)
{
	for (int i = 0; i<(int)Js.size(); i++)
	{
		for (int j = 0; j<(int)Js[i].size(); j++)
			printf("%d",Js[i][j]);
		printf("\n");
	}
}

bool HIsNice(list<vector<int > > H)
{
	
	for (list<vector<int> >::iterator iter1 = H.begin();iter1 != H.end(); iter1++)
	{
		list<vector<int> >::iterator iter2 = iter1; iter2++;
		for (;iter2!=H.end(); iter2++)
		{
			if (areTwoSetsDisjoint((*iter1),(*iter2))) continue;
			if (areTwoSetsSame((*iter1),(*iter2)))
			{
				iter2 = H.erase(iter2); iter2--; continue;
			}
			return false;
		}
	}
	return true;
}

list<vector<int> > projectH1(const list<vector<int> > & H, int p)
{
	vector<vector<int> > columnHits(p); getColumnHits(columnHits,H);
	list<vector<int> > projH;
	
	for (list<vector<int> >::const_iterator iter = H.begin(); iter!= H.end(); iter++)
	{
		if ((int)(*iter).size() == 0) {printf("Warning! H has an all-zero line in projectH2().\n"); continue;}
		vector<int> largestColumnHitIndex(1,(*iter)[0]);
		for (int j = 1;j<(int)(*iter).size();j++)
		{
			if (columnHits[(*iter)[j]].size() == columnHits[largestColumnHitIndex[0]].size()) 
				largestColumnHitIndex.push_back((*iter)[j]);
			else if (columnHits[(*iter)[j]].size() > columnHits[largestColumnHitIndex[0]].size()) 
				largestColumnHitIndex = vector<int>(1,(*iter)[j]);
		}	
		projH.push_back(largestColumnHitIndex);
	}
	
	for (list<vector<int> >::iterator iter1 = projH.begin(); iter1!= projH.end(); iter1++)
	{
		list<vector<int> >::iterator iter2 = iter1; iter2++;
		for (; iter2!= projH.end(); iter2++)
			if (areTwoSetsSame(*iter1, *iter2)) 
				{iter2 = projH.erase(iter2); iter2--;}
	}
	return projH;
}


list<vector<int> > solveNiceH(list<vector<int> > H, int p)
{
	if (!HIsNice(H)) {printf("Warning! The H passed to solveNiceH is not nice!\n");}
	
	vector<int> tmp(p,0);
	list<vector<int> > mustHitGroupIndex;
	for (list<vector<int> >::const_iterator iter = H.begin(); iter != H.end(); iter++)
	{
		if ((int)(*iter).size() == 0) continue;
		if (tmp[(*iter)[0]] == 1) continue;
		mustHitGroupIndex.push_back(*iter);
		for (int i = 0;i<(int)(*iter).size();i++) tmp[(*iter)[i]] = 1;
	}
	
	return mustHitGroupIndex;
}

hittingScenarios solveH2(list<vector<int> > H, int p)
{
	//list<vector<int> > projH = projectH1(H,p);
	list<vector<int> > projH = projectH1(H,p);
	vector<vector<int> > columnHits(p); getColumnHits(columnHits,projH);
	//printf("projH\n");showList(projH);
	//printf("columnHits\n"); 
	//for(int i = 0;i<(int)columnHits.size();i++) 
	//	{printf("[%d]",i);showSet(columnHits[i]);}
		
	
	list<vector<int> > mustHitGroupIndex, HH;
	for (list<vector<int> >::iterator iter = projH.begin(); iter != projH.end(); iter++)
	{
		bool isMHGI = true;
		for (int i = 0;i<(int)(*iter).size();i++)
			if ((int)columnHits[(*iter)[i]].size() > 1) {isMHGI = false; break;}
		if (isMHGI) 
			mustHitGroupIndex.push_back(*iter);
		else
			HH.push_back(*iter);
	}
	//printf("mHGI");showList(mustHitGroupIndex);
	//printf("HH");showList(HH);
	list<vector<int> > Js;
	if ((int)HH.size() > 0) 
	{
		decomposeHRv4(HH,vector<int>(p),Js,0,p, true,true,true); 
		removeHighRankJs(Js,p); 
		checkJs(HH,Js);
	}
	
	return hittingScenarios(mustHitGroupIndex,Js);
}

hittingScenarios::hittingScenarios(const list<vector<int> > mHGI, list<vector<int> > Jss)
{
	mustHitGroupIndex = mHGI;
	Js = Jss;
}

void hittingScenarios::show() const
{
	showMustHitGroupIndex();
	showJs();
}
void hittingScenarios::showMustHitGroupIndex() const
{
	printf("%d Must-hit groups with sizes: ", mustHitGroupIndex.size());
	for(list<vector<int > >::const_iterator iter = mustHitGroupIndex.begin(); iter!=mustHitGroupIndex.end();iter++)
	printf("%d ", (int)(*iter).size()); printf("\n");
	//showList(mustHitGroupIndex);
}
void hittingScenarios::showJs() const
{
	printf("Js.size() = %d\n", (int)Js.size());
	showList(Js);
}
void hittingScenarios::saveFile(const char * strMGHI, const char * strJs) const
{
	FILE *fp = fopen(strMGHI,"w");
	int p = 0;
	for (list<vector<int> >::const_iterator iter = mustHitGroupIndex.begin();iter!=mustHitGroupIndex.end(); iter++)
		if ((int)(*iter).size()> p) p = (int)(*iter).size();
	
	fprintf(fp, "%d %d ", (int)mustHitGroupIndex.size(),p);
	
	for (list<vector<int> >::const_iterator iter = mustHitGroupIndex.begin(); iter != mustHitGroupIndex.end(); iter++)
	{	
		fprintf(fp, "%d ", (int)(*iter).size());
		for (int i = 0; i < (int)(*iter).size(); i++) fprintf(fp, "%d ", (*iter)[i]+1);
	}
	fprintf(fp,"\n");
	fclose(fp);
	
	saveListCompact(Js,strJs);
	
}



extern "C" {
void tests()
{
	int n = 0,p = 0;
	vector<vector<int> > matrix;
	
	clock_t clockStart, clockEnd;
	clockStart = clock();	
	matrix = readMatrix(n,p);
	printf("%d,%d\n",n,p);
	saveMatrix(matrix,n,p);
	list<vector<int> > H = getH(matrix);
	
	//showList(H);
	hittingScenarios HSs = solveH2(H,p);
	HSs.show();
	HSs.saveFile();
	clockEnd = clock();
	double elapsed = ((double) (clockEnd - clockStart)) / CLOCKS_PER_SEC;
	printf("time = %f\n",elapsed);
}
}


