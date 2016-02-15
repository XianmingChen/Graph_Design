#ifndef _GRAPHMATRIX_H
#define _GRAPHMATRIX_H

#include<iostream>
#include<limits>
#include<ctime>
#include<stack>
#include<queue>

using namespace std;

typedef char ElemType;
typedef int EdgeVal;

const int MaxSize=10;
const int MaxEdgeVal=9;

typedef struct MSTEdgeType
{
	int value;
	int StartV;
	int EndV;
}MSTEdgeType;

class GraphMatrix
{
public:
	GraphMatrix();
	GraphMatrix(int VertexSize);
	GraphMatrix(int VertexSize,bool isRandom);
	~GraphMatrix(){};

	void print();
	void insert(ElemType value);
	void RemoveVertex(int index);
	void SetEdge(int start,int end,int value);
	void RandSetEdge(int VerIndex);
	void RemoveEdge(int start,int end);
	int NumEdge();
	int NumVertex();
	int VertexEdge(int VerIndex);

	void DFSTravel();
	void DFS(int VerIndex,bool VertexVisted[]);
	void DFSTravelNR();
	void DFSNR(int VerIndex,bool VertexVisted[]);

	void BFSTravel();

	void Floyd();

	void MST_Kruskal();
	void MST_Prime();
private:
	ElemType Vertex[MaxSize];
	EdgeVal Edge[MaxSize][MaxSize];
	int VertexNum;
	int EdgeNum;
	void InitEdge();
	void InitVertex();
	void Initialize();
	void SetVerEdge(int size);
	void RandVerEdge(int size);
	
	int Kruskal_Find_Parent(int* parent,int index);
	int FindMinEdge(bool* mark,int* MarkVerList,int VerMarked,int& newVer);
};

#endif