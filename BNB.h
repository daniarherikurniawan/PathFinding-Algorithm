#include <iostream>
#include <cstdlib>
#include <vector>
#include "Matrix.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ctime>
using namespace std;

vector<string> ArrayPath;
vector<int> ArrayCost;

class LiveNode {
public:
    int Node;
    Matrix M;
    int Cost;
    vector<int> Path;
    int index;
    int Level;
    LiveNode(int N, Matrix Mm, int Cs,
    	vector<int> P,int ind,int Level){
    	Node = N;
    	M = Mm;
    	Cost = Cs;
    	Path = P;
    	index = ind;
    	this->Level = Level;
    }
    bool operator < (const LiveNode& str) const
    {
        return (Cost < str.Cost);
    }
};

class BNB {
private:
	Matrix *M;
	int NumberOfLiveNode;
	int StartNode ;
	int CurrIndex;
	char* FileName;
	vector<LiveNode> myVec;
	int getSizeInputMatrix();
	void PushSonToQueue(int Node, Matrix M, 
	int Cost,vector<int> Path,int ind,int Lvl);
public:
	int Level;
	vector<int> Path;
	BNB(char* FileName);
	bool IsExistAnotherChoice();
	bool IsPathCompleted();
	bool IsPath(int Node);
	void setPathToArrayPath();
	void StartBranchNBound();
	void printStateMatrix();
	void BlockPrevPath();
	void printPath(vector<string> ArrayPath);
	void printCurrPath();
	void printQueue();
	void removeBadLiveNode(int MaxCost);
	void printNumberOfLiveNode();
	void readFile(); 
	void setStartNode(int start);
	void SearchNextNode(int Node);
	int PopQueue();
	int getCurrBobot();
	int PopQueueForNewPath();
};


//g++ Matrix.cpp BNB.cpp -o a