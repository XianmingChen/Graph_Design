#include "GraphMatrix.h"

void GraphMatrix::InitVertex()
{
	int i;
	for(i=0;i<MaxSize;i++)
	{
		Vertex[i]=NULL;
	}
}

void GraphMatrix::InitEdge()
{
	int i,j;

	for(i=0;i<MaxSize;i++)
	{
		for(j=0;j<MaxSize;j++)
		{
			Edge[i][j]=INT_MAX;
		}
	}
}

void GraphMatrix::Initialize()
{
	VertexNum=0;
	EdgeNum=0;
	InitEdge();
	InitVertex();
}

void GraphMatrix::SetVerEdge(int size)
{
	int i,j;
	char TmpVertex;
	int TmpEdgeVal;

	cout<<"Please input the value for each vertex."<<endl;
	for(i=0;i<size;i++)
	{
		cin>>TmpVertex;
		if((TmpVertex>='A')&&(TmpVertex<='Z'))
		{
			Vertex[i]=TmpVertex;
			VertexNum++;
		}
	}

	for(i=0;i<VertexNum;i++)
	{
		cout<<"Please input the edge matrix for vertex "<<i<<endl;
		for(j=0;j<VertexNum;j++)
		{
			if(i==j)
				Edge[i][j]=0;
			else
			{
				cout<<"Vertex "<<i<<" to vertex "<<j<<endl;
				cin>>TmpEdgeVal;
				if((TmpEdgeVal<=MaxEdgeVal)&&(TmpEdgeVal>0))
				{
					Edge[i][j]=TmpEdgeVal;
					EdgeNum++;
				}
			}
		}
	}
}

void GraphMatrix::RandVerEdge(int size)
{
	int i,j;

	srand((unsigned)time(NULL));
	for(i=0;i<size;i++)
	{
		Vertex[i]='A'+rand()%26;
		VertexNum++;
	}

	for(i=0;i<VertexNum;i++)
	{
		for(j=0;j<VertexNum;j++)
		{
			if(i==j)
				Edge[i][j]=0;
			else
			{
				Edge[i][j]=rand()%MaxEdgeVal+1;
				EdgeNum++;
			}
		}
	}
}

GraphMatrix::GraphMatrix()
{
	Initialize();
}

GraphMatrix::GraphMatrix(int VertexSize)
{
	Initialize();

	if(VertexSize>MaxSize)
	{
		cout<<"VertexSize exceeds the maximum!"<<endl;
	}
	else
	{
		SetVerEdge(VertexSize);
	}
}

GraphMatrix::GraphMatrix(int VertexSize,bool isRandom)
{
	Initialize();

	if(VertexSize>MaxSize)
	{
		cout<<"VertexSize exceeds the maximum!"<<endl;
	}
	else if(isRandom==false)
	{
		SetVerEdge(VertexSize);
	}
	else
	{
		RandVerEdge(VertexSize);
	}
}

void GraphMatrix::print()
{
	int i,j;
	cout<<"This graph has "<<VertexNum<<" vertexes and "<<EdgeNum<<" edges."<<endl;
	cout<<"The vertexes in graph are:"<<endl;
	for(i=0;i<MaxSize;i++)
	{
		if(Edge[i][i]==0)
			cout<<Vertex[i]<<" ";
		else
			cout<<" "<<" ";
	}
	cout<<endl;

	cout<<"The edge matrix of graph is:"<<endl;
	for(i=0;i<MaxSize;i++)
	{
		for(j=0;j<MaxSize;j++)
		{
			if(Edge[i][j]!=INT_MAX)
				cout<<Edge[i][j]<<" ";
			else
				cout<<"X"<<" ";
		}
		cout<<endl;
	}
}

void GraphMatrix::insert(ElemType value)
{
	int i;

	if(VertexNum==MaxSize)
	{
		cout<<"Graph is full!"<<endl;
		return;
	}

	if((value>='A')&&(value<='Z'))
	{
		for(i=0;i<MaxSize;i++)
		{
			if(Edge[i][i]!=0)
			{
				Vertex[i]=value;
				Edge[i][i]=0;
				VertexNum++;
				return;
			}
		}
	}
	else
		cout<<"The value is not qualified!"<<endl;
}

void GraphMatrix::RemoveVertex(int index)
{
	int i;
	Vertex[index]=NULL;
	VertexNum--;
	for(i=0;i<MaxSize;i++)
	{
		Edge[index][i]=INT_MAX;
		EdgeNum--;
	}
}

void GraphMatrix::SetEdge(int start,int end,int value)
{
	if((Edge[start][start]!=0)||(Edge[end][end]!=0))
		return;

	if((value<=MaxEdgeVal)&&(value>0))
	{
		Edge[start][end]=value;
		EdgeNum++;
	}
}

void GraphMatrix::RandSetEdge(int VerIndex)
{
	int i;
	int temp;

	if(Edge[VerIndex][VerIndex]!=0)
		return;

	srand((unsigned)time(NULL));
	for(i=0;i<MaxSize;i++)
	{
		if((Edge[i][i]==0)&&(i!=VerIndex))
		{
			temp=rand()%MaxEdgeVal+1;
			if(Edge[VerIndex][i]==INT_MAX)
				EdgeNum++;

			Edge[VerIndex][i]=temp;

			temp=rand()%MaxEdgeVal+1;
			if(Edge[i][VerIndex]==INT_MAX)
				EdgeNum++;

			Edge[i][VerIndex]=temp;
		}
	}
}

void GraphMatrix::RemoveEdge(int start,int end)
{
	if(Edge[start][end]!=INT_MAX)
	{
		EdgeNum--;
		Edge[start][end]=INT_MAX;
	}
}

int GraphMatrix::NumEdge()
{
	return EdgeNum;
}

int GraphMatrix::NumVertex()
{
	return VertexNum;
}

int GraphMatrix::VertexEdge(int VerIndex)
{
	int i;
	int count=0;

	for(i=0;i<MaxSize;i++)
	{
		if((Edge[VerIndex][i]<=MaxEdgeVal)&&(Edge[VerIndex][i]>0))
			count++;

		if((Edge[i][VerIndex]<=MaxEdgeVal)&&(Edge[i][VerIndex]>0))
			count++;
	}
	return count;
}

void GraphMatrix::DFSTravel()
{
	int i;
	bool VertexVisted[MaxSize];

	for(i=0;i<MaxSize;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSize;i++)
	{
		if((Edge[i][i]==0)&&(VertexVisted[i]==false))
			DFS(i,VertexVisted);
	}
}

void GraphMatrix::DFS(int VerIndex, bool VertexVisted[])
{
	int i;
	if(VertexVisted[VerIndex]==false)
	{
		VertexVisted[VerIndex]=true;
		cout<<Vertex[VerIndex]<<endl;

		for(i=0;i<MaxSize;i++)
		{
			if((Edge[VerIndex][i]!=INT_MAX)&&(VertexVisted[i]==false))
				DFS(i,VertexVisted);
		}
	}
}

void GraphMatrix::DFSTravelNR()
{
	int i;
	bool VertexVisted[MaxSize];

	for(i=0;i<MaxSize;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSize;i++)
	{
		if((Edge[i][i]==0)&&(VertexVisted[i]==false))
			DFSNR(i,VertexVisted);
	}
}

void GraphMatrix::DFSNR(int VerIndex,bool VertexVisted[])
{
	stack<int> connect;
	int i,curr;
	bool foundnext=false;

	connect.push(VerIndex);
	VertexVisted[VerIndex]=true;
	cout<<Vertex[VerIndex]<<endl;

	while(!connect.empty())
	{
		curr=connect.top();
		foundnext=false;
		for(i=0;i<MaxSize;i++)
		{
			if((Edge[VerIndex][i]!=INT_MAX)&&(VertexVisted[i]==false))
			{
				connect.push(i);
				VertexVisted[i]=true;
				cout<<Vertex[i]<<endl;	
				foundnext=true;
				break;
			}
		}

		if(foundnext==false)
		{
			connect.pop();
		}
	}
}

void GraphMatrix::BFSTravel()
{
	int i,j,tmp;
	queue<int> record;
	bool VertexVisted[MaxSize];

	for(i=0;i<MaxSize;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSize;i++)
	{
		if((Edge[i][i]==0)&&(VertexVisted[i]==false))
		{
			record.push(i);
			cout<<Vertex[i]<<endl;
			VertexVisted[i]=true;
			while(!record.empty())
			{
				tmp=record.front();
				record.pop();
				for(j=0;j<MaxSize;j++)
				{
					if((Edge[i][j]!=INT_MAX)&&(VertexVisted[j]==false))
					{
						record.push(j);
						VertexVisted[j]=true;
						cout<<Vertex[j]<<endl;	
					}
				}

			}
		}
	}
}

void GraphMatrix::Floyd()
{
	int i,j,k;
	EdgeVal Distance[MaxSize][MaxSize];
	int Path[MaxSize][MaxSize];

	for(i=0;i<MaxSize;i++)
	{
		for(j=0;j<MaxSize;j++)
		{
			Distance[i][j]=Edge[i][j];
			Path[i][j]=j;
		}
	}

	for(i=0;i<MaxSize;i++)
	{
		if(Edge[i][i]==0)
		{
			for(j=0;j<MaxSize;j++)
			{
				if(Edge[j][j]==0)
				{
					for(k=0;k<MaxSize;k++)
					{
						if(Edge[k][k]==0)
						{
							if(Edge[j][i]+Edge[i][k]<Edge[j][k])
							{
								Edge[j][k]=Edge[j][i]+Edge[i][k];
								Path[j][k]=i;
							}
						}
					}
				}
			}
		}
	}

}

void swap(MSTEdgeType& A,MSTEdgeType& B)
{
	MSTEdgeType tmp;
	tmp=A;
	A=B;
	B=tmp;
}

int partition(MSTEdgeType* MST_Edge,int start,int end)
{
	int i,pos=start;
	MSTEdgeType pivot=MST_Edge[end];

	for(i=start;i<end;i++)
	{
		if(MST_Edge[i].value<pivot.value)
		{
			swap(MST_Edge[i],MST_Edge[pos]);
			pos++;
		}
	}
	swap(MST_Edge[end],MST_Edge[pos]);
	return pos;
}

void EdgeSort(MSTEdgeType* MST_Edge,int start,int end)
{
	int mid;
	if(start<end)
	{
		mid=partition(MST_Edge,start,end);
		EdgeSort(MST_Edge,start,mid-1);
		EdgeSort(MST_Edge,mid+1,end);
	}
}

int GraphMatrix::Kruskal_Find_Parent(int* parent,int index)
{
	while(parent[index]>=0)
	{
		index=parent[index];
	}
	return index;
}

void GraphMatrix::MST_Kruskal()
{
	int i,j,EdgeCount=0;
	MSTEdgeType* MST_Edge=new MSTEdgeType[EdgeNum];
	int* ParentVert=new int[VertexNum];
	int start_parent,end_parent;

	for(i=0;i<MaxSize;i++)
	{
		for(j=0;j<MaxSize;j++)
		{
			if((Edge[i][j]!=INT_MAX)&&(i!=j))
			{
				MST_Edge[EdgeCount].value=Edge[i][j];
				MST_Edge[EdgeCount].StartV=i;
				MST_Edge[EdgeCount].EndV=j;
				EdgeCount++;
			}
		}
	}
	EdgeSort(MST_Edge,0,EdgeCount-1);

	for(i=0;i<VertexNum;i++)
	{
		ParentVert[i]=-1;
	}

	for(i=0;i<EdgeNum;i++)
	{
		start_parent=Kruskal_Find_Parent(ParentVert,MST_Edge[i].StartV);
		end_parent=Kruskal_Find_Parent(ParentVert,MST_Edge[i].EndV);

		if(start_parent!=end_parent)
		{
			ParentVert[start_parent]=end_parent;
			cout<<"Vertex "<<start_parent<<" to vertex "
				<<end_parent<<": "<<MST_Edge[i].value<<endl;
		}
	}

	delete []MST_Edge;
	delete []ParentVert;
}

int GraphMatrix::FindMinEdge(bool* mark,int* MarkVerList,int VerMarked,int& newVer)
{
	int i;
	int tmpmin=INT_MAX;
	int Vercount,index;

	for(Vercount=0;Vercount<VerMarked;Vercount++)
	{
		index=MarkVerList[Vercount];
		for(i=0;i<VertexNum;i++)
		{
			if((mark[i]==false)&&(i!=index))
			{
				if(Edge[index][i]<tmpmin)
				{
					tmpmin=Edge[index][i];
					newVer=i;
				}

				if(Edge[i][index]<tmpmin)
				{
					tmpmin=Edge[i][index];
					newVer=i;
				}
			}
		}
	}
	return tmpmin;
}

void GraphMatrix::MST_Prime()
{
	int i;
	int SearchVer,newVer,newEdge,VerMarked=0;
	bool* mark=new bool[VertexNum];
	int* MarkVerList=new int[VertexNum];

	for(i=0;i<VertexNum;i++)
	{
		mark[i]=false;
	}

	SearchVer=0;
	MarkVerList[VerMarked]=SearchVer;
	VerMarked++;
	mark[SearchVer]=true;	
	newEdge=FindMinEdge(mark,MarkVerList,VerMarked,newVer);
	MarkVerList[VerMarked]=newVer;
	VerMarked++;
	mark[newVer]=true;
	cout<<"Vert "<<SearchVer<<" to vert "<<newVer<<": "<<newEdge<<endl;

	while(VerMarked<VertexNum)
	{
		newEdge=FindMinEdge(mark,MarkVerList,VerMarked,newVer);
		MarkVerList[VerMarked]=newVer;
		VerMarked++;
		mark[newVer]=true;
		cout<<"Vert "<<SearchVer<<" to vert "<<newVer<<": "<<newEdge<<endl;
	}
	delete[] mark;
	delete[] MarkVerList;
}