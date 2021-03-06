#include"graph.h"
#include"Dijkstra.h"
#include"MinHeap.h"
#include<fstream>
#include<malloc.h>
#include<conio.h>


void DijkstraMH(struct graph* G, int source, MinHeap *mh, int distance[N], int predecesor[N]){

	MinHeapNode temp;
	Init(mh);
	int adjnodes[N], adjweights[N], nodesCounter=0;
	temp.distance = 0;
	distance[0] = 0;
	mh->seen[source] = 1;
			
	temp.destinationVertex = source;
	Insert(mh, temp);

	for(int node = 0; node < G->noOfEdges; node ++){
		if(node!= source)
			distance[node]=inf;
	}

	distance[source]=0;
	

	for (int i = 0; i < G->noOfEdges;i++){//getting the adjencent nodes of the source and their weights

		if (G->pEdge[i].source == source){
			adjnodes[nodesCounter] = G->pEdge[i].destination;
			adjweights[nodesCounter] = G->pEdge[i].weight;
			nodesCounter ++;
		}
	}	
	for(int j = 1; j <= G->noOfVertices; j ++){//deals with the source's adjencent nodes	
		for (int i = 0; i < nodesCounter; i ++){
		
			if(j!=source){
				if(adjnodes[i] == j){
					temp.distance = adjweights[i];
					distance[adjnodes[i]]= adjweights[i];
					mh->seen[adjnodes[i]]=0;
					
					temp.destinationVertex = adjnodes[i];
					Insert(mh,temp);
					break;
				}
			
				else{			
					distance[j]= inf;
					mh->seen[j]=0;
				}
			}
		}
	}

	while( mh -> heapSize ){

		MinHeapNode min = DeleteMin(mh);
		int currentVertex = min.destinationVertex;
		
		if( mh -> seen[currentVertex] )
			continue;

		mh -> seen[currentVertex] = 1;
		
		for (int i = 0; i < G->noOfEdges;i++){//getting the adjencent nodes of the source's adjencent node taken into consideration
			
			if (G->pEdge[i].source == currentVertex){
				adjnodes[nodesCounter] = G->pEdge[i].destination;
				adjweights[nodesCounter] = G->pEdge[i].weight;
				nodesCounter ++;
			}
		}	
		
		for (int i = 0; i < nodesCounter; i ++){
			if( distance[adjnodes[i]] > distance[currentVertex] + adjweights[i]){//Dijkstra minimum criteria

				distance[adjnodes[i]] = distance[currentVertex] + adjweights[i];
				temp.destinationVertex = adjnodes[i];
				temp.distance = distance[adjnodes[i]];
				Insert( mh, temp );
				predecesor[adjnodes[i]] = currentVertex;

			}
		}
	}
}
void printResult(struct graph* G, int distance[N],int source){

	for(int i=1;i<=G->noOfVertices;i++){
		if( distance[i] != 0 && distance[i] != inf && i!=source)
			printf("Distance from source to %d is %d\n",i,distance[i]);
	}
	getch();
}
void getDistance(struct graph* graph, int source, int destination, MinHeap *mh, int distance[N], int predecesor[N]){
	
	DijkstraMH( graph, source, mh, distance, predecesor );
	printf("Distance from %d to %d is: %d", source, destination, distance[destination] );
	getch();
}
void getPath(struct graph* graph, int source, int destination, MinHeap *mh, int distance[N], int predecesor[N]){
	
	DijkstraMH(graph, source, mh, distance, predecesor);
	printf("The path from %d to %d is: ", source, destination);

	int i = destination;
	int count = 0, path[N];
	if(source == 1)
		printf("%d, ", source);
	while( i != source){
		if( predecesor[i] != 0 ){
			i = predecesor[i];
			path[count] = i;
			count ++;
		}
		else 
			break;
	}
	for(int j = count;j >= 0;j --)
		if(path[j] > 0)
			printf("%d, ", path[j]);
	printf("%d", destination);
	getch();
}
bool hasNegativeweights(struct graph* G){
	bool ok=false;
	int adjweights[N],nodesCounter=0;
		
	for(int j = 0; j <= G->noOfVertices; j ++ ){//getting the adjencent nodes' weights of every node
		for (int i = 0; i < G->noOfEdges; i ++)

			if (G->pEdge[i].source == j){
				adjweights[nodesCounter] = G->pEdge[i].weight;
				nodesCounter ++;
			}		
		for (int i=0;i<nodesCounter;i++){
			if(adjweights[i]< 0)
				ok = true;
		}
	}
	return ok;
}
void Dijkstra(struct graph* G, int source, int distance[N], int predecesor[N]){

	int currentVertex, count, visited[100], min;

	for(int node = 0; node < G->noOfEdges; node ++){
		if(node!= source)
		visited[node] = 0;
		distance[node]=inf;
	}

	distance[source]=0;
	
	for(int node = 0; node < G->noOfEdges; node ++){
		if (G->pEdge[node].source == source){
			visited[G->pEdge[node].destination] = 0;
			distance[G->pEdge[node].destination]=G->pEdge[node].weight;
		}
	}
	count=2;
	
	while(count <= G->noOfVertices) {
		min = inf;
		for(int node = 0; node < G->noOfVertices; node ++)
			if(distance[node]<min && !visited[node]){
				min=distance[node];
				currentVertex=node;
			}
		visited[currentVertex]=1;
		count++;
		
		for(int node = 0; node <= G->noOfEdges; node ++){

			if(G->pEdge[node].source == currentVertex)
				if((distance[currentVertex] + G->pEdge[node].weight < distance[G->pEdge[node].destination]) && !visited[G->pEdge[node].destination])

					distance[G->pEdge[node].destination] = distance[currentVertex] + G->pEdge[node].weight;
		}
	}
}
void DFS(graph *G, std::vector<int> &visited2, std::vector<int> &visitedweights, int end, int weight, int prevweight, int &count, int distanceDFS[20]){

	int back;
	back = visited2.back();
	std::vector<int> adjNodes = getAdjNodes(G, back);
	std::vector<int> weights = getAdjweights(G, back);

	typedef std::vector<int>::iterator iterNodes;
	typedef std::vector<int>::iterator iterweights;

	
	for (std::pair<iterNodes, iterweights> i(adjNodes.begin(), weights.begin()); i.first != adjNodes.end(); ++ i.first, ++ i.second){
	
		int node = (*i.first);

		if (nodeVisited(visited2, node)) 
			continue;

		if (node == end){
			visited2.push_back(*i.first);
			prevweight = weight;
			weight = weight + (*i.second);
			visitedweights.push_back(weight);
			
			count ++;
			distanceDFS[count] = weight;

			int n = (int)visited2.size() - 1;
			visited2.erase(visited2.begin() + n);
			int m = (int)visitedweights.size() - 1;
			visitedweights.erase(visitedweights.begin() + m);
			weight = prevweight;
		
			break;
		}
	}

	for (std::pair<iterNodes, iterweights> i(adjNodes.begin(), weights.begin()); i.first != adjNodes.end(); ++ i.first, ++ i.second){

		int node = (*i.first);

		if (nodeVisited(visited2, node) || node == end)
			continue;
		prevweight=weight;
		weight = weight + (*i.second);
		visited2.push_back(node);
		
		DFS(G, visited2,visitedweights, end, weight, prevweight, count, distanceDFS);

		int n = (int)visited2.size() - 1;
		visited2.erase(visited2.begin() + n);
		int m = (int)visitedweights.size() - 1;
		if(m > 0)
			visitedweights.erase(visitedweights.begin() + m);
		weight = prevweight;
	}

}

int minDistance(struct graph* graph, int distanceDFS[N]){
	int min = inf;
	for(int j = 0;j <= graph->noOfVertices; j ++)
		if(distanceDFS[j] < min && distanceDFS[j] > 0)
			min = distanceDFS[j];
	return min;
}

void bruteForceDijkstra(int source, graph *G, MinHeap *mh, int end, int weight, int prevweight, int &count, int distance[N], int predecesor[N]){
	int destination;
	int minDistanceDFS[N] = {0}, distanceDFS[N] = {0};
	int cnt = 0;
	

		for(int i = 0; i <= G->noOfVertices; i ++){
			distance[i] = 0;	
			minDistanceDFS[i]  = 0;
			distanceDFS[i] = 0;
		}

		std::vector<int> visited;
		std::vector<int> visitedweights;
		
		DijkstraMH( G, source, mh, distance, predecesor);
		
		for(int destination = 1; destination <= G->noOfVertices; destination ++){
		
			distanceDFS[source] = 0;//vector for all the paths from source to destination
		
			if(destination != source){
				visited.push_back(source);
				DFS(G, visited, visitedweights, destination, weight, prevweight, count, distanceDFS);
				minDistanceDFS[destination] = minDistance( G, distanceDFS);

				for(int i = 0; i <= G->noOfVertices; i ++)
					distanceDFS[i] = 0;				//reset the vector				
			}
		}

}