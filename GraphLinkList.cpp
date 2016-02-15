#include "GraphLinkList.h"

void GraphLinkList::InitVertex()
{
	int i;
	for(i=0;i<MaxSizeList;i++)
	{
		Vertex[i].value=NULL;
		Vertex[i].FirstAdj=NULL;
	}
}

void GraphLinkList::Initialize()
{
	VertexNum=0;
	EdgeNum=0;
	InitVertex();
}

GraphLinkList::GraphLinkList()
{
	Initialize();
}

GraphLinkList::GraphLinkList(int VertexSize)
{
	Initialize();

	if(VertexSize>MaxSizeList)
	{
		cout<<"VertexSize exceeds the maximum!"<<endl;
	}
	else
	{
		RandVerEdge(VertexSize);
	}
}

void GraphLinkList::RandVerEdge(int size)
{
	int i,j;
	bool firstAdj;
	AdjNodePtr tmpAdj,currAdj;
	int tmpEdge;

	srand((unsigned)time(NULL));
	for(i=0;i<size;i++)
	{
		Vertex[i].value='A'+rand()%26;
		VertexNum++;
		firstAdj=false;
		for(j=0;j<size;j++)
		{
			tmpEdge=rand()%EdgeRange+1;
			if((i!=j)&&(tmpEdge<=MaxEdgeValList))
			{
				tmpAdj=new AdjNode;
				tmpAdj->CurrAdj=j;
				tmpAdj->EdgeValue=tmpEdge;
				tmpAdj->NextAdj=NULL;
		
				EdgeNum++;
				if(firstAdj==false)
				{
					firstAdj=true;
					Vertex[i].FirstAdj=tmpAdj;
					currAdj=tmpAdj;
				}
				else
				{
					currAdj->NextAdj=tmpAdj;
					currAdj=tmpAdj;
				}
			}
		}
	}
}

void GraphLinkList::Print()
{
	int i;
	AdjNodePtr tmp;
	int tmpNode;

	cout<<"This Graph has "<<VertexNum<<" vertexes and "<<EdgeNum<<" edges."<<endl;
	cout<<"V A E"<<endl;
	cout<<endl;

	for(i=0;i<MaxSizeList;i++)
	{
		if(Vertex[i].value!=NULL)
		{
			if(Vertex[i].FirstAdj==NULL)
			{
				cout<<Vertex[i].value<<endl;
			}
			else
			{
				tmp=Vertex[i].FirstAdj;
				while(tmp!=NULL)
				{
					cout<<Vertex[i].value<<" ";
					
					tmpNode=tmp->CurrAdj;
					cout<<Vertex[tmpNode].value<<" ";
					cout<<tmp->EdgeValue<<endl;
					tmp=tmp->NextAdj;
				}
			}
		}
	}
}

void GraphLinkList::InsertVertex(ElemTypeList value)
{
	int i;

	if(VertexNum==MaxSizeList)
	{
		cout<<"Graph is full!"<<endl;
		return;
	}

	if((value>='A')&&(value<='Z'))
	{
		for(i=0;i<MaxSizeList;i++)
		{
			if(Vertex[i].value==NULL)
			{
				Vertex[i].value=value;
				VertexNum++;
				return;
			}
		}
	}
	else
		cout<<"The value is not qualified!"<<endl;
}

void GraphLinkList::SetEdge(int start,int end,int value)
{
	AdjNodePtr tmp,currAdj;

	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL))
		return;

	if(EdgeExisted(start,end,currAdj)==true)
	{
		currAdj->EdgeValue=value;
	}
	else
	{
		if((value<=MaxEdgeValList)&&(value>0))
		{
			tmp=new AdjNode;
			tmp->CurrAdj=end;
			tmp->EdgeValue=value;
			tmp->NextAdj=NULL;

			currAdj=Vertex[start].FirstAdj;

			if(currAdj==NULL)
				Vertex[start].FirstAdj=tmp;
			else
			{
				while(currAdj->NextAdj!=NULL)
				{
					currAdj=currAdj->NextAdj;
				}
				currAdj->NextAdj=tmp;
			}
			EdgeNum++;
		}
	}
}

void GraphLinkList::RemoveVertex(int index)
{
	int i;
	AdjNodePtr tmp,preAdj,currAdj;

	if((index<0)||(index>MaxSizeList))
		return;

	if(Vertex[index].FirstAdj!=NULL)
	{
		while(Vertex[index].FirstAdj!=NULL)
		{
			tmp=Vertex[index].FirstAdj;
			Vertex[index].FirstAdj=Vertex[index].FirstAdj->NextAdj;
			delete tmp;
			EdgeNum--;
		}
	}

	for(i=0;i<MaxSizeList;i++)
	{
		if((i!=index)&&(EdgeExisted(i,index,preAdj,currAdj)==true))
		{
			if(preAdj==NULL)
			{
				Vertex[i].FirstAdj=currAdj->NextAdj;
			}
			else
			{
				preAdj->NextAdj=currAdj->NextAdj;
			}
			delete currAdj;
			EdgeNum--;
		}
	}

	Vertex[index].value=NULL;
	VertexNum--;
}

void GraphLinkList::RemoveEdge(int start,int end)
{
	AdjNodePtr tmp,PreAdj;

	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL)
		||(Vertex[start].FirstAdj==NULL))
		return;

	if(Vertex[start].FirstAdj->CurrAdj==end)
	{
		tmp=Vertex[start].FirstAdj;
		Vertex[start].FirstAdj=Vertex[start].FirstAdj->NextAdj;
		delete tmp;
		EdgeNum--;
	}
	else
	{
		PreAdj=Vertex[start].FirstAdj;
		tmp=Vertex[start].FirstAdj->NextAdj;
		while(tmp!=NULL)
		{
			if(tmp->CurrAdj==end)
			{
				PreAdj->NextAdj=tmp->NextAdj;
				delete tmp;
				EdgeNum--;
				return;
			}
			else
			{
				tmp=tmp->NextAdj;
				PreAdj=PreAdj->NextAdj;
			}
		}
	}
}

bool GraphLinkList::EdgeExisted(int start,int end)
{
	AdjNodePtr tmp;

	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL))
	{
		return false;
	}

	tmp=Vertex[start].FirstAdj;
	while(tmp!=NULL)
	{
		if(tmp->CurrAdj==end)
		{
			return true;
		}
		else
			tmp=tmp->NextAdj;
	}
	return false;
}

bool GraphLinkList::EdgeExisted(int start,int end, int& EdgeVal)
{
	AdjNodePtr tmp;

	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL))
	{
		return false;
		EdgeVal=INT_MAX;
	}

	tmp=Vertex[start].FirstAdj;
	while(tmp!=NULL)
	{
		if(tmp->CurrAdj==end)
		{
			EdgeVal=tmp->EdgeValue;
			return true;
		}
		else
			tmp=tmp->NextAdj;
	}
	EdgeVal=INT_MAX;
	return false;
}

bool GraphLinkList::EdgeExisted(int start,int end,AdjNodePtr& EdgePtr)
{
	AdjNodePtr tmp;

	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL))
	{
		return false;
		EdgePtr=NULL;
	}

	tmp=Vertex[start].FirstAdj;
	while(tmp!=NULL)
	{
		if(tmp->CurrAdj==end)
		{
			EdgePtr=tmp;
			return true;
		}
		else
			tmp=tmp->NextAdj;
	}
	EdgePtr=NULL;
	return false;
}

bool GraphLinkList::EdgeExisted(int start,int end,AdjNodePtr& PreEdgePtr,AdjNodePtr& EdgePtr)
{
	AdjNodePtr tmp,Pretmp=NULL;

	PreEdgePtr=NULL;
	EdgePtr=NULL;
	if((start==end)||(start<0)||(start>MaxSizeList)||(end<0)||(end>MaxSizeList)
		||(Vertex[start].value==NULL)||(Vertex[end].value==NULL))
	{
		return false;	
	}

	tmp=Vertex[start].FirstAdj;
	while(tmp!=NULL)
	{
		if(tmp->CurrAdj==end)
		{
			PreEdgePtr=Pretmp;
			EdgePtr=tmp;
			return true;
		}
		else
		{
			Pretmp=tmp;
			tmp=tmp->NextAdj;
		}
	}
	return false;
}

void GraphLinkList::DFSTravel()
{
	int i;
	bool VertexVisted[MaxSizeList];

	for(i=0;i<MaxSizeList;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSizeList;i++)
	{
		if((Vertex[i].value!=NULL)&&(VertexVisted[i]==false))
			DFS(i,VertexVisted);
	}
}

void GraphLinkList::DFS(int VerIndex, bool VertexVisted[])
{
	AdjNodePtr NextAdj;

	if(VertexVisted[VerIndex]==false)
	{
		VertexVisted[VerIndex]=true;
		cout<<Vertex[VerIndex].value<<endl;

		if(Vertex[VerIndex].FirstAdj!=NULL)
		{
			NextAdj=Vertex[VerIndex].FirstAdj;
			while(NextAdj!=NULL)
			{
				if(VertexVisted[NextAdj->CurrAdj]==false)
					DFS(NextAdj->CurrAdj,VertexVisted);
				NextAdj=NextAdj->NextAdj;
			}
		}
	}
}

void GraphLinkList::DFSTravelNR()
{
	int i;
	bool VertexVisted[MaxSizeList];

	for(i=0;i<MaxSizeList;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSizeList;i++)
	{
		if((Vertex[i].value!=NULL)&&(VertexVisted[i]==false))
			DFSNR(i,VertexVisted);
	}
}

void GraphLinkList::DFSNR(int VerIndex,bool VertexVisted[])
{
	stack<int> Record;
	AdjNodePtr NextAdj;
	int tmpvertex;

	if((Vertex[VerIndex].value!=NULL)&&(VertexVisted[VerIndex]==false))
	{
		Record.push(VerIndex);
		while(!Record.empty())
		{
			tmpvertex=Record.top();
			Record.pop();

			if(VertexVisted[tmpvertex]==false)
			{
				cout<<Vertex[tmpvertex].value<<endl;
				VertexVisted[tmpvertex]=true;

				NextAdj=Vertex[tmpvertex].FirstAdj;
				while(NextAdj!=NULL)
				{
					if(VertexVisted[NextAdj->CurrAdj]==false)
						Record.push(NextAdj->CurrAdj);
					NextAdj=NextAdj->NextAdj;
				}
			}
		}
	}
}

void GraphLinkList::BFSTravel()
{
	int i,tmpVertex;
	queue<int> record;
	AdjNodePtr NextAdj;
	bool VertexVisted[MaxSizeList];

	for(i=0;i<MaxSizeList;i++)
		VertexVisted[i]=false;

	for(i=0;i<MaxSizeList;i++)
	{
		if((Vertex[i].value!=NULL)&&(VertexVisted[i]==false))
		{
			record.push(i);
			NextAdj=Vertex[i].FirstAdj;
			while(NextAdj!=NULL)
			{
				if(VertexVisted[NextAdj->CurrAdj]==false)
					record.push(NextAdj->CurrAdj);
				NextAdj=NextAdj->NextAdj;
			}

			while(!record.empty())
			{
				tmpVertex=record.front();
				record.pop();
				cout<<Vertex[tmpVertex].value<<endl;
				VertexVisted[tmpVertex]=true;
			}
		}
	}
}

void GraphLinkList::CountEdgesPointed(int EdgesPointed[])
{
	int i,VerIndex;
	AdjNodePtr NextAdj;

	for(i=0;i<MaxSizeList;i++)
	{
		EdgesPointed[i]=0;
	}

	for(i=0;i<MaxSizeList;i++)
	{
		if(Vertex[i].value!=NULL)
		{
			NextAdj=Vertex[i].FirstAdj;
			while(NextAdj!=NULL)
			{
				VerIndex=NextAdj->CurrAdj;
				EdgesPointed[VerIndex]++;
				NextAdj=NextAdj->NextAdj;
			}
		}
	}
}

bool GraphLinkList::FindNoPointedVertex(bool VertexVisted[],int EdgesPointed[],int& index)
{
	int i;
	for(i=0;i<MaxSizeList;i++)
	{
		if((EdgesPointed[i]==0)&&(VertexVisted[i]==false)&&(Vertex[i].value!=NULL))
		{
			index=i;
			return true;
		}
	}
	return false;
}

void GraphLinkList::TopologySort()
{
	int i,tmpVertex;
	int ZeroPointedVertex;
	queue<int> record;
	AdjNodePtr NextAdj;
	bool VertexVisted[MaxSizeList];
	int EdgesPointed[MaxSizeList];

	for(i=0;i<MaxSizeList;i++)
		VertexVisted[i]=false;

	CountEdgesPointed(EdgesPointed);

	if(FindNoPointedVertex(VertexVisted,EdgesPointed,ZeroPointedVertex)==true)
	{
		record.push(ZeroPointedVertex);
		while(!record.empty())
		{
			tmpVertex=record.front();
			record.pop();
			cout<<Vertex[tmpVertex].value<<endl;
			VertexVisted[tmpVertex]=true;

			NextAdj=Vertex[tmpVertex].FirstAdj;
			while(NextAdj!=NULL)
			{
				tmpVertex=NextAdj->CurrAdj;
				EdgesPointed[tmpVertex]--;
				NextAdj=NextAdj->NextAdj;
			}

			if(FindNoPointedVertex(VertexVisted,EdgesPointed,ZeroPointedVertex)==true)
			{
				record.push(ZeroPointedVertex);
			}
		}

		for(i=0;i<MaxSizeList;i++)
		{
			if((VertexVisted[i]==false)&&(Vertex[i].value!=NULL))
			{
				cout<<"This graph contains a cycle."<<endl;
				return;
			}
		}
		cout<<"Graph topological sort done!"<<endl;
	}
	else
		cout<<"This graph contains a cycle."<<endl;
}

void GraphLinkList::Dijkstra(int start)
{
	int i,j;
	AdjNodePtr Adj;
	DijkstraDist SingleSource[MaxSizeList];
	bool ShorterFound;
	int tmpmin,newstart;
	int PrintPreVertex;

	if(Vertex[start].value==NULL)
		return;

	//Initialization
	for(i=0;i<MaxSizeList;i++)
	{
		if(Vertex[i].value!=NULL)
		{
			SingleSource[i].Marked=false;
			SingleSource[i].Dist=INT_MAX;
			SingleSource[i].PreVertex=start;
		}	
	}

	//The start node itself
	SingleSource[start].Marked=true;
	SingleSource[start].Dist=0;

	Adj=Vertex[start].FirstAdj;
	while(Adj!=NULL)
	{
		SingleSource[Adj->CurrAdj].Dist=Adj->EdgeValue;
		Adj=Adj->NextAdj;
	}

	for(i=0;i<MaxSizeList-1;i++) //It needs MaxSizeList-1 times to search
	{
		tmpmin=INT_MAX;
		ShorterFound=false;
		for(j=0;j<MaxSizeList;j++)
		{
			if((SingleSource[j].Marked==false)&&(SingleSource[j].Dist<tmpmin))
			{
				ShorterFound=true;
				tmpmin=SingleSource[j].Dist;
				newstart=j;
			}
		}

		if(ShorterFound==true)
		{
			SingleSource[newstart].Marked=true;
			Adj=Vertex[newstart].FirstAdj;
			while(Adj!=NULL)
			{
				if(Adj->EdgeValue+tmpmin<SingleSource[Adj->CurrAdj].Dist)
				{
					SingleSource[Adj->CurrAdj].Dist=Adj->EdgeValue+tmpmin;
					SingleSource[Adj->CurrAdj].PreVertex=newstart;
				}
				Adj=Adj->NextAdj;
			}
		}
		else
			break;
	}

	//Print the shortest paths
	for(i=0;i<MaxSizeList-1;i++) //It needs MaxSizeList-1 times to search
	{
		if(Vertex[i].value!=NULL)
		{
			cout<<Vertex[i].value<<"<-";
			PrintPreVertex=i;
			while(SingleSource[PrintPreVertex].PreVertex!=start)
			{
				PrintPreVertex=SingleSource[PrintPreVertex].PreVertex;
				cout<<Vertex[PrintPreVertex].value<<"<--";
			}
			cout<<Vertex[start].value<<"  ";
			cout<<SingleSource[i].Dist<<endl;
		}
	}
}

void GraphLinkList::Dijkstra(int start,int end)
{
	int i,j;
	AdjNodePtr Adj;
	DijkstraDist SingleSource[MaxSizeList];
	bool ShorterFound;
	int tmpmin,newstart;
	int PrintPreVertex;

	if((Vertex[start].value==NULL)||(Vertex[end].value==NULL))
		return;

	//Initialization
	for(i=0;i<MaxSizeList;i++)
	{
		if(Vertex[i].value!=NULL)
		{
			SingleSource[i].Marked=false;
			SingleSource[i].Dist=INT_MAX;
			SingleSource[i].PreVertex=start;
		}	
	}

	//The start node itself
	SingleSource[start].Marked=true;
	SingleSource[start].Dist=0;

	Adj=Vertex[start].FirstAdj;
	while(Adj!=NULL)
	{
		SingleSource[Adj->CurrAdj].Dist=Adj->EdgeValue;
		Adj=Adj->NextAdj;
	}

	for(i=0;i<MaxSizeList-1;i++) //It needs MaxSizeList-1 times to search
	{
		tmpmin=INT_MAX;
		ShorterFound=false;
		for(j=0;j<MaxSizeList;j++)
		{
			if((SingleSource[j].Marked==false)&&(SingleSource[j].Dist<tmpmin))
			{
				ShorterFound=true;
				tmpmin=SingleSource[j].Dist;
				newstart=j;
			}
		}

		if(newstart==end)
				break;

		if(ShorterFound==true)
		{
			SingleSource[newstart].Marked=true;
			Adj=Vertex[newstart].FirstAdj;
			while(Adj!=NULL)
			{
				if(Adj->EdgeValue+tmpmin<SingleSource[Adj->CurrAdj].Dist)
				{
					SingleSource[Adj->CurrAdj].Dist=Adj->EdgeValue+tmpmin;
					SingleSource[Adj->CurrAdj].PreVertex=newstart;
				}
				Adj=Adj->NextAdj;
			}
		}
		else
			break;
	}

	//Print the shortest paths
	cout<<Vertex[end].value<<"<-";
	PrintPreVertex=end;
	while(SingleSource[PrintPreVertex].PreVertex!=start)
	{
		PrintPreVertex=SingleSource[PrintPreVertex].PreVertex;
		cout<<Vertex[PrintPreVertex].value<<"<--";
	}
	cout<<Vertex[start].value<<"  ";
	cout<<SingleSource[end].Dist<<endl;
}