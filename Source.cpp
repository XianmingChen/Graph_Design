#include "GraphMatrix.h"
#include "GraphLinkList.h"

int main()
{
	GraphMatrix Graph(5,true);
	Graph.print();

	cout<<endl;
	Graph.MST_Kruskal();

	cout<<endl;
	Graph.MST_Prime();

	/*Graph.BFSTravel();

	cout<<endl;
	Graph.insert('D');
	Graph.print();
	Graph.BFSTravel();*/

	/*GraphLinkList Graph(5);
	Graph.Print();

	cout<<endl;
	Graph.Dijkstra(1,4);*/

	/*cout<<endl;
	Graph.RemoveVertex(0);
	Graph.DFSTravel();*/

 	system("pause");
	return 0;
}