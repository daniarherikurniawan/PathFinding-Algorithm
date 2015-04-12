#include "BNB.h"

BNB::BNB(char* FileName){
	NumberOfLiveNode = 0;
	this->FileName = FileName;
	StartNode = 0;
	Level = 0;
}
void BNB::setStartNode(int start){
	StartNode = start;
}
int BNB::getSizeInputMatrix(){
	int size = 0, temp; string line;
	ifstream myfile (FileName);
	getline (myfile,line);
	istringstream is( line );
	while( is >> temp ) {
         size++;
    }
	myfile.close();
	return size;
}
void BNB::readFile(){
	int sizeMatrix = getSizeInputMatrix();
	M = new Matrix(sizeMatrix);
	ifstream file(FileName);
	for (unsigned int i = 0; i < sizeMatrix; i++) 
    	for (unsigned int j = 0; j < sizeMatrix; j++) {
        	file >> M->Elmt[i][j].value;
        	M->Elmt[i][j].cost = -99;
        }
    file.close();
}


void BNB::PushSonToQueue(int Node, Matrix M, int Cost,
	vector<int> Path,int ind,int Lvl){
	LiveNode *LN = new LiveNode(Node, M, Cost,Path,ind,Lvl);
	myVec.push_back(*LN);
	sort(myVec.begin(), myVec.end());
}
void BNB::printQueue(){
	if(Path.size() != M->size + 1)
		cout<<"Current index is "<<CurrIndex<<endl;
	else cout<<"Current index is a leaf"<<endl;
	for (int i=0; i<myVec.size();i++)
    	cout <<"   Index "<<myVec[i].index <<"'s cost : "<< myVec[i].Cost << "  "<<myVec[i].Level<<endl;
	printNumberOfLiveNode();
}

bool BNB::IsPath(int Node){
	return (find(Path.begin(), Path.end(), Node) != Path.end());
}
int BNB::PopQueueForNewPath(){
	int CurrNode = myVec[0].Node;
	*M = (myVec[0].M);
	M->Bobot = myVec[0].Cost;
	Path = myVec[0].Path;
	CurrIndex = myVec[0].index;
	myVec.erase(myVec.begin());
	return CurrNode;
}
int BNB::PopQueue(){
	int CurrNode = myVec[0].Node;
	*M = (myVec[0].M);
	M->Bobot = myVec[0].Cost;
	CurrIndex = myVec[0].index;
	
	if(myVec[0].Level == Level){
		Level += 1;
		Path.push_back(myVec[0].Node); // menambah path
	}else {
		Level = myVec[0].Level;
		Path = myVec[0].Path;
	}
	//cout<<myVec[0].Node<<endl;
	myVec.erase(myVec.begin());
	//M->printMatrixValue();
	//printCurrPath();
	//int x; cin >> x;
	return CurrNode;
}
void BNB::printCurrPath(){
	for (int i=0; i<Path.size();i++){
    	cout <<Path[i]<<"  ";
	}cout<<endl;
}
void BNB::printPath(vector<string> ArrayPath){
	for (int i=0; i<ArrayPath.size();i++){
    	cout <<"Path "<<i+1<<"  : "<<ArrayPath[i]<<endl;
		cout <<"   Cost : "<<ArrayCost[i]<<endl;
	}
}
void BNB::printStateMatrix(){
	M->printMatrixValue();
	//M->printMatrixCost();
}
void BNB::printNumberOfLiveNode(){
	cout<<"There are "<<myVec.size()<<" livenode"<<endl;
}
bool BNB::IsPathCompleted(){
	return Path.size() >= M->size ;
}
int BNB::getCurrBobot(){
	return M->Bobot;
}
bool BNB::IsExistAnotherChoice(){
	return myVec[0].Cost <= M->Bobot;
}
void BNB::BlockPrevPath(){
	for(int a = 0 ; a < ArrayPath.size(); a++){
		string word; vector<int> value;
	    stringstream stream(ArrayPath[a]);	
    	while( getline(stream, word, '-') ){
        	value.push_back(atoi(word.c_str()));
        }
        for(int i = 0 ; i < value.size() - 1; i++){
        	M->Elmt[value[i]][value[i+1]].value = -99;
        	M->Elmt[value[i+1]][value[i]].value = -99;
        }
	}
}
void BNB::setPathToArrayPath(){
	ostringstream oss;
	copy(Path.begin(), Path.end()-1,
    ostream_iterator<int>(oss, " - "));
	oss << Path.back();
    ArrayPath.push_back(oss.str());
    ArrayCost.push_back(getCurrBobot());
}
void BNB::removeBadLiveNode(int MaxCost){
	bool stop = false;
	while(!myVec.empty() && !stop){
		if(myVec[0].Cost > MaxCost)
			myVec.erase(myVec.begin());
		else
			stop = true;
	}
}

void BNB::SearchNextNode(int Node){
	for(int a = 0; a < M->size ; a++){
		if(M->IsSonOf(a,Node) && !IsPath(a)){
		Matrix MTemp;
		MTemp = *M; 
		if(M->IsSonOf(a,Node)){
			M->Elmt[Node][a].cost = MTemp.ReducedCostMatrix();
			M->Elmt[Node][a].cost +=  MTemp.getElmt(Node,a);
		}	
			MTemp.TurnValueIntoInfinity(Node,a);
			MTemp.Elmt[a][Node].value = -99;
			
			int ExtraCost = MTemp.ReducedCostMatrix();

			M->Elmt[Node][a].cost += (ExtraCost + M->Bobot);
		

			NumberOfLiveNode++;
			PushSonToQueue(a, MTemp, M->Elmt[Node][a].cost,
				Path,NumberOfLiveNode,Level);

		}
		
	}
}
void BNB::StartBranchNBound(){
	int StartNode = 0;
	int CurrNode = StartNode;
	NumberOfLiveNode++;
	PushSonToQueue(StartNode, *M, 0, Path,NumberOfLiveNode,Level);
	CurrNode = PopQueue();
	while(!IsPathCompleted() || IsExistAnotherChoice()){
		SearchNextNode(CurrNode);
		printQueue();cout<<endl;
		CurrNode = PopQueue();
		if(IsPathCompleted()){
			M->TurnValueIntoInfinity(StartNode,0);
			NumberOfLiveNode++;
			PushSonToQueue(0, *M, M->Bobot, Path,NumberOfLiveNode,Level);
			CurrNode = PopQueue();
			setPathToArrayPath();
			removeBadLiveNode(M->Bobot);
			if(IsExistAnotherChoice()){
				int y; //cout<<"ada pilihan path lain"; cin >> y; 
				CurrNode = PopQueueForNewPath();
				cout<<M->Bobot<<"  "<<Path.size()<<endl;
				cin>>y;
				BlockPrevPath();
			}
		} 
	}
}

int main(){
	int before = clock();
	char FileName[] ="input.txt"; 
	BNB myBNB(FileName);
	myBNB.readFile();
	myBNB.printStateMatrix();

	myBNB.StartBranchNBound();

	myBNB.printStateMatrix();
	myBNB.printQueue();
	myBNB.printPath(ArrayPath);

	int after = clock();
	cout<<"Runtime : "<<after-before<<" ms"<<endl;
	return 0;
}