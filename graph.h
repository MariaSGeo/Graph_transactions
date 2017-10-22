#ifndef GRAPH_H
#define GRAPH_H

#include "hashtable.h"

class graph{

	private:
		int n_transactions;
		int n_nodes;
		hashtable * hasht;

	public:
		graph(hashtable * ht);
		~graph();
		void DFS(nnode * n);
		void changestats();
		int createnodes(int * newnodes,int n_nodes);
		int delnodes (int * newnodes,int n_nodes);
		int addtran (int  n1,int n2,float amount);
		int deltran (int  n1,int n2);
		int lookup_in (int n);
		int lookup_out (int n);
		int lookup_sum (int n);
		int triangle (int n,int k);
		int allc(nnode * n1,nnode * n2,nnode * vlist,int times);
		int tri(nnode * n1,int amount);
		int trf(nnode * curr,nnode * visited,int times,int pathl,int amount);
		int conn (int n1,int n2);
		int path(nnode * n1,nnode * n2);
		void allcycles (int n);
		int traceflow (int n,int pathl);
		void bye();
		void printgraph();
		void dump(char * filename);	
};

#endif