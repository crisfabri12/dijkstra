#include <bits/stdc++.h>

using namespace std;
#include "fibonacci_heap.cpp"

#define INF 0x3f3f3f3f


typedef pair<int, int> iPair;

class Graph {
	int V; 
	list<pair<int, int>> *adj;
	
public:
	Graph(int V); 
	
	void addEdge(int u, int v, int w);
	void dijkstra_p(int s);
	void dijkstra(int s);
	void dijkstra_h(int src);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w) {
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Graph::dijkstra_p(int src) {
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
	vector<int> dist(V, INF);
	
	pq.push(make_pair(0, src));
	dist[src] = 0;
	
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		list<pair<int, int>>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}




void Graph::dijkstra(int src)
{
	vector<int> dist(V, INF); 
	
	vector<bool> sptSet(V, 0);
	
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	
	dist[src] = 0;
	
	
	for (int count = 0; count < V - 1; count++) {
		int u;
		int min = INT_MAX;
		for (int v = 0; v < V; v++){
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], u = v;
		}
		
		sptSet[u] = true;
		
		list<pair<int, int>>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;
			if (!sptSet[V] && weight && dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
		
	}
	
	for (int i = 0; i < V; i++)
		cout << i << " \t\t\t\t" << dist[i] << endl;
}




void Graph::dijkstra_h(int src) {
	
	
	
	vector<Node *> vertices;
	for(int j=0; j < V ; j++)
	{
		Node* v = new Node(j, -1);
		vertices.push_back(v);
	}
	
	vertices[src]->key = 0;
	vertices[src]->state = LABELED;
	
	std::vector<Edge*> edges;
	for(int i = 0; i < V; i++ ){
		list<pair<int, int>>::iterator j;
		for (j = adj[i].begin(); j != adj[i].end(); ++j) {
			int weight = (*j).second;
			Edge* edge = new Edge(vertices[i], vertices[(*j).first], weight);
			edge->head->addIncomingEdge(edge);
			edge->tail->addOutgoingEdge(edge);
			edges.push_back(edge);
		}
	}
	
	FibonacciHeap* heap = new FibonacciHeap();
	heap->insertVertex(vertices[src]);
	
	bool abort = false;
	long j = 0;
	
	do
	{
		Node* v = heap->deleteMin();
		
		v->state = SCANNED;
		std::cout<< v->incomingEdges.size() << std::endl;
		for(int i = 0; i < v->incomingEdges.size(); i++)
		{
			Edge* currentEdge = v->incomingEdges[i];
			Node* headOfCurrentEdge = currentEdge->tail;
			
			if(headOfCurrentEdge->state != SCANNED)
			{
				if(headOfCurrentEdge->state == UNLABELED)
				{
					headOfCurrentEdge->state = LABELED;
					headOfCurrentEdge->pred = v;
					headOfCurrentEdge->key = v->key + currentEdge->length;
					heap->insertVertex(headOfCurrentEdge);
				}
				else if(headOfCurrentEdge->key > v->key + currentEdge->length )
				{
					headOfCurrentEdge->pred = v;
					heap->decreaseKey(v->key + currentEdge->length, headOfCurrentEdge);
				}
			}
		}
	}
	while(!heap->isEmpty());
	
	Node* temp = vertices[src];
	
	int vertexCount = 0;
	
	printf("%f\n", vertices[0]->key);
	
	while(temp)
	{
		printf("%d", temp->data);
		temp = temp->pred;
		if(temp)
			printf(" - ");
		
		vertexCount++;
	}
	
	printf("\n%d\n", vertexCount);
	
	
}
