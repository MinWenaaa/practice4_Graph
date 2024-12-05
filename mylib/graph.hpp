//
//-------------------- for the practice4_Graph ----------------------
//

#pragma once
#include<iostream>

namespace Minw {

	template <class T, class E>
	struct Edge {
		int dest;
		E cost;
		Edge<T, E>* link;

		Edge():dest(0), cost(0), link(nullptr) {};
		Edge(int num, E weight): dest(num), cost(weight), link(nullptr) {}
		bool operator != (Edge<T, E> R) const {
			return (dest != R.dest) ? true : false;
		}
	};

	template <class T, class E>
	struct Node {
		T data;
		Edge<T, E>* adj;
		Node() :data(0), adj(nullptr) {};
	};

	template <class T, class E>
	class undirectedGraph {
	public:
		undirectedGraph(int sz);
		~undirectedGraph();

		int insertVertex(const T& vertex);
		bool insertEdge(int v1, int v2, E cost);

		//bool isEmpty();
		E getWeight(int v1, int v2);
		//T getVertex(int v);

		bool DFS();
		bool DBS();

		int getDepthN(int v);
		int getDepthE(int v1, int v2);
	private:
		int maxVertices;
		int numEdges;
		int numVertices;
		Node<T, E>* nodeTable;

		//int getVertexPos(const T vertex);
	};
}
//------------------------------------------------------------------------
template<class T, class E>
Minw::undirectedGraph<T, E>::undirectedGraph(int sz) {
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	this->nodeTable = new Node<T, E>[maxVertices];

	if (!nodeTable) {
		std::cerr << "memory_allocation_error!" << std::endl;
		exit(1);
	}

	//for (int i = 0; i < maxVertices; i++) {
	//	this->nodeTable[i].adj = nullptr;
	//}
}
//------------------------------------------------------------------------
template<class T, class E> 
Minw::undirectedGraph<T, E>::~undirectedGraph() {
	for (int i = 0; i < numVertices; i++) {
		Edge<T, E>* p = nodeTable[i].adj;
		while (p != nullptr) {
			this->nodeTable[i].adj = p->link;
			delete p;
			p = this->nodeTable[i].adj;
		}
	}
	delete[]nodeTable;
}
//------------------------------------------------------------------------
template<class T, class E>
E Minw::undirectedGraph<T, E>::getWeight(int v1, int v2) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) return -2;

	Edge<T, E>* p = this->nodeTable[v1].adj;
	while (p->dest != v2) {
		p = p->link;
		if (!p) return -1;
	}
	return p->cost;

}
//------------------------------------------------------------------------
template<class T, class E>
int Minw::undirectedGraph<T, E>::insertVertex(const T& vertex) {
	if (numVertices == maxVertices)
		return -1;
	this->nodeTable[numVertices].data = vertex;
	numVertices++;
	return numVertices-1;
}
//------------------------------------------------------------------------
template<class T, class E>
bool Minw::undirectedGraph<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) return false;

	Edge<T, E>* q, * p = nodeTable[v1].adj;
	while (p) {					// 检查边是否已经存在
		if (p->dest == v2) return false;
		p = p->link;
	}
	p = new Edge<T, E>; q = new Edge<T, E>;
	p->dest = v2;
	p->cost = weight;
	p->link = nodeTable[v1].adj;	// 头插
	nodeTable[v1].adj = p;
	q->dest = v1;
	q->cost = weight;
	q->link = nodeTable[v2].adj;
	nodeTable[v2].adj = q;
	numEdges++;
	return true;
}
//------------------------------------------------------------------------
template<class T, class E>
bool Minw::undirectedGraph<T, E>::DFS() {

}
//------------------------------------------------------------------------
template<class T, class E>
bool Minw::undirectedGraph<T, E>::DBS() {

}
//------------------------------------------------------------------------
template<class T, class E>
int Minw::undirectedGraph<T, E>::getDepthN(int v) {

}
//------------------------------------------------------------------------
template<class T, class E>
int Minw::undirectedGraph<T, E>::getDepthE(int v1, int v2) {

}