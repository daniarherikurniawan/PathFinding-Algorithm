#include "Matrix.h"

using namespace std;

Matrix::Matrix(int size){
	Bobot = 0;
	this->size = size;
	Elmt = (ElmtType**) malloc(size*sizeof(ElmtType*));  
	for (int i = 0; i < size; i++)  
   		Elmt[i] = (ElmtType*) malloc(size*sizeof(ElmtType));  
}
bool Matrix::IsElmtValid(int row, int col){
	return Elmt[row][col].value != -99;
}
bool Matrix::IsCostValid(int row, int col){
	return Elmt[row][col].cost != -99;
}
void Matrix::printMatrixValue(){
	for(int i = 1 ; i <= ((size-1)*2 - 6)/2 ; i++)
		cout<<"    ";
	cout<<"=====>>>>> Value <<<<<====="<<endl;
	for(int a = 0; a < size; a++){
		for(int b = 0; b< size ; b++){
			cout<<Elmt[a][b].value<<"\t";
		}
		cout<<endl<<endl;	
	}
}
int Matrix::getElmt(int i, int j){
	return Elmt[i][j].value;
}

void Matrix::printMatrixCost(){
	for(int i = 1 ; i <= ((size-1)*2 - 6)/2 ; i++)
		cout<<"    ";
	cout<<"=====>>>>> Cost <<<<<====="<<endl;
	for(int a = 0; a < size; a++){
		for(int b = 0; b< size ; b++){
			cout<<Elmt[a][b].cost<<"\t";
		}
		cout<<endl<<endl;	
	}
}
Matrix::~Matrix(){
	for (int i = 0; i < size; i++){  
   		free(Elmt[i]);  
	}  
	free(Elmt);  
}
void Matrix::TurnValueIntoInfinity(int i, int j){
	for(int a = 0; a < size; a++){
		Elmt[i][a].value = -99;
		Elmt[a][j].value = -99;
	}
}
int Matrix::ReducedCostMatrix(){
	int ReduceCost = 0;
	//membuat setiap baris memiliki nilai 0
	for(int a = 0; a < size; a++){
		int MinRow = getMinRowValue(a);
		if(MinRow != 1000000000){
		ReduceCost += MinRow;
		for(int b = 0; b < size; b++){
			if(IsElmtValid(a,b)){
				Elmt[a][b].value -= MinRow;
			}
		}
		}
		if(MinRow<0){
		}
	}
	for(int col = 0; col < size; col++){
		int MinCol = getMinColValue(col);
		if(MinCol != 1000000000){
			ReduceCost += MinCol;
			for(int row = 0; row < size; row++){
				if(IsElmtValid(col,row)){
					Elmt[row][col].value -= MinCol;
				}
			}
		}

	}
	return ReduceCost;
} 


int Matrix::getMinRowValue(int row){
	int min = 1000000000;
	for(int a = 0; a <size ; a++){
		if(IsElmtValid(row,a) && min > Elmt[row][a].value){
			min = Elmt[row][a].value;
		}
	}

	return min;
}

int Matrix::getMinColValue(int col){
	int min = 1000000000;
	for(int a = 0; a <size ; a++){
		if(IsElmtValid(a,col) && min > Elmt[a][col].value){
			min = Elmt[a][col].value;
		}
	}
	return min;
}

bool Matrix::IsSonOf(int a, int Node){
	return a != Node && Elmt[Node][a].value!= -99;
}
Matrix::Matrix(){
	Bobot = 0;
}
Matrix& Matrix::operator= (const Matrix& M){
	size = M.size;
	Bobot = M.Bobot;
	Elmt = (ElmtType**) malloc(size*sizeof(ElmtType*));  
	for (int i = 0; i < size; i++)  
   		Elmt[i] = (ElmtType*) malloc(size*sizeof(ElmtType)); 

	for(int a = 0; a < size; a++){
		for(int b = 0; b < size; b++){
			Elmt[a][b].value = M.Elmt[a][b].value;
			Elmt[a][b].cost = M.Elmt[a][b].cost;
		}
	}
	return *this;
}

Matrix::Matrix(const Matrix& M){
	Bobot = M.Bobot;
	size = M.size;
	Elmt = (ElmtType**) malloc(size*sizeof(ElmtType*));  
	for (int i = 0; i < size; i++)  
   		Elmt[i] = (ElmtType*) malloc(size*sizeof(ElmtType)); 

	for(int a = 0; a < size; a++){
		for(int b = 0; b < size; b++){
			Elmt[a][b].value = M.Elmt[a][b].value;
			Elmt[a][b].cost = M.Elmt[a][b].cost;
		}
	}
}