#ifndef	_GRAPHLINKLIST_H_
#define _GRAPHLINKLIST_H_

#include<iostream>
#include<ctime>
#include<stack>
#include<queue>

using namespace std;
typedef char ElemTypeList;
typedef int EdgeValList;
const int MaxEdgeValList=40;
const int EdgeRange=50;
const int MaxSizeList=10;

typedef struct AdjNode
{
	int CurrAdj;
	EdgeValList EdgeValue;
	AdjNode* NextAdj;
}AdjNode,*AdjNodePtr;

typedef struct Node
{
	ElemTypeList value;
	AdjNodePtr FirstAdj;
}Node;

typedef struct DijkstraDist
{
	bool Marked;
	EdgeValList Dist;
	int PreVertex;
}DijkstraDist;

class GraphLinkList
{
public:
	GraphLinkList();
	GraphLinkList(int VertexSize);
	~GraphLinkList(){};

	void RandVerEdge(int size);
	void Print();
	void InsertVertex(ElemTypeList value);
	void SetEdge(int start,int end,int value);
	void RemoveVertex(int index);
	void RemoveEdge(int start,int end);
	bool EdgeExisted(int start,int end); 
	bool EdgeExisted(int start,int end,AdjNodePtr& EdgePtr); 
	bool EdgeExisted(int start,int end,AdjNodePtr& PreEdgePtr,AdjNodePtr& EdgePtr); 
	bool EdgeExisted(int start,int end,int& EdgeVal); 

	void DFSTravel();
	void DFS(int VerIndex,bool VertexVisted[]);
	void DFSTravelNR();
	void DFSNR(int VerIndex,bool VertexVisted[]);
	void BFSTravel();

	void TopologySort();

	void Dijkstra(int start);
	void Dijkstra(int start,int end);

private:
	Node Vertex[MaxSizeList];
	int VertexNum;
	int EdgeNum;

	void Initialize();
	void InitVertex();
	void CountEdgesPointed(int EdgesPointed[]);
	bool FindNoPointedVertex(bool VertexVisted[],int EdgesPointed[],int& index);
};

#endif