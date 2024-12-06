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
		int depth;
		Edge<T, E>* link;

		Edge():dest(0), cost(0), link(nullptr), depth(-1){};
		Edge(int num, E weight): dest(num), cost(weight), link(nullptr), depth(-1) {}
		bool operator != (Edge<T, E> R) const {
			return (dest != R.dest) ? true : false;
		}
	};

	template <class T, class E>
	struct Node {
		T data;
		int depth;
		Edge<T, E>* adj;
		Node() :data(0), adj(nullptr), depth(-1) {};
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

		bool DFS(int v);
		bool BFS(int v);

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
	while (p) {
		if (p->dest == v2) return p->cost;
		p = p->link;
	}

	if (!p) return -1;
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
	while (p) {					// �����Ƿ��Ѿ�����
		if (p->dest == v2) return false;
		p = p->link;
	}
	p = new Edge<T, E>; q = new Edge<T, E>;
	p->dest = v2;
	p->cost = weight;
	p->link = nodeTable[v1].adj;	// ͷ��
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
bool Minw::undirectedGraph<T, E>::DFS(int v) {
	//	�����нڵ������Ϊδ����״̬
	bool* visited_node = new bool[numVertices]();
	for (int i = 0; i < numVertices; i++) {
		nodeTable[i].depth = -1;
		Edge<T,E>* p = nodeTable[i].adj;
		while (p) {
			p->depth = -1;
			p = p->link;
		}
	}

	// ��ʼ����
	int last_pn = v, pn = v, current_depth = 0;
	Edge<T, E>* pe = nodeTable[pn].adj;
	Edge<T, E>* pt = nullptr;
	nodeTable[pn].depth = current_depth++;
	while (pe) {
		// ��ǵ�ǰ�ڵ㡢�ߺͶ�Ӧ��
		pe->depth = current_depth;
		pt = nodeTable[pe->dest].adj;
		while (pt) {
			if (pt->dest == pn) {
				pt->depth = current_depth++;
				break;
			}
			pt = pt->link;
		}
		pn = pe->dest;
		if (nodeTable[pn].depth == -1) nodeTable[pn].depth = current_depth++;


		// Ѱ����һ����
		pe = nodeTable[pn].adj;
		while (pe) {
			if (pe->depth == -1) break;
			pe = pe->link;
		}
		if (!pe) {	// ��ǰ�ڵ������ϣ���ǲ�Ѱ�������ڵ�
			visited_node[pn] = true;
			bool flag = false;
			for (int i = 0; i < numVertices; i++) {
				if (visited_node[i] || nodeTable[i].depth == -1) continue;
				pn = i;
				flag = true;
			}
			if (!flag) return true;	// ���нڵ������ɣ�����ѭ��
			pe = nodeTable[pn].adj;
			while (pe) {
				if (pe->depth == -1) break;
				pe = pe->link;
			}
		}

	}
	return false;
}
//------------------------------------------------------------------------
template<class T, class E>
bool Minw::undirectedGraph<T, E>::BFS(int v) {

}
//------------------------------------------------------------------------
template<class T, class E>
int Minw::undirectedGraph<T, E>::getDepthN(int v) {
	if (v<0 || v> numVertices) return -1;
	return nodeTable[v].depth;
}
//------------------------------------------------------------------------
template<class T, class E>
int Minw::undirectedGraph<T, E>::getDepthE(int v1, int v2) {
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) return -2;

	Edge<T, E>* p = this->nodeTable[v1].adj;
	while (p) {
		if (p->dest == v2) return p->depth;
		p = p->link;
	}

	if (!p) return -1;
}