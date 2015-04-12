#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

typedef struct{
	int value;
	int cost;
} ElmtType;

class Matrix{
public:
	ElmtType** Elmt;
	int Bobot;
	Matrix(const Matrix& M);
	Matrix(int size);
	Matrix();
	~Matrix();
	Matrix& operator= (const Matrix&);
	void printMatrixValue();
	void printMatrixCost();
	void TurnValueIntoInfinity(int i, int j);
	bool IsCostValid(int row, int col);
	bool IsElmtValid(int row, int col);
	bool IsSonOf(int a, int Node);
	int getElmt(int i, int j);
	int getMinRowValue(int row);
	int ReducedCostMatrix();
	int getMinColValue(int col);int size;
}; 