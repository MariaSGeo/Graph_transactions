#ifndef NNODEINFO_H
#define NNODEINFO_H

class nodeG;

class nnode { 		//used for listing graph nodes(nodeG) in hash table buckets

	private:
		nnode * next;
		nnode * prv;
		nodeG * graph_node;

	public:
		nnode(nodeG * g_node);
		~nnode();
		nnode * get_next();
		nnode * get_prv();
		nodeG * get_graph_node();
		void set_next(nnode * n);
		void set_prv(nnode * p);
};

class transaction {		//graph edges (they point to their vertices (from->to) )
	
	private:
		nnode * id_from;
		nnode * id_to;
		float cash_amount;

	public:
		transaction(nnode * from,nnode * to,float amount);
		~transaction();
		float get_amount();
		nnode * get_id_from();
		nnode * get_id_to();
		int new_transaction(int from,int to,float amount);			
};


class tnode {	//used for listing transaction nodes(transaction) in each graph node(nodeG)

	private:
		tnode * next;
		tnode * prv;
		transaction * t_transaction;

	public:
		tnode(transaction * tr);
		~tnode();
		tnode * get_next();
		tnode * get_prv();
		transaction * get_transaction();
		void set_next(tnode * n);
		void set_prv(tnode * p);	
};

class nodeG {	//graph vertices (each has a list of incoming and outgoing edges)
	private:	
		int node_id;
		tnode * out_transactions;
		tnode * in_transactions;
		int all_transactions_in;
		int all_transactions_out; 
		bool visited; //used in dfs functions

	public:
		nodeG(int id);
		~nodeG();
		int get_node_id();
		bool isvisited();
		void print_out_trans();
		void print_in_trans();
		tnode * get_conns_in();
		tnode * get_conns_out();
		int get_trans_in();
		int get_trans_out();
		void changestatusNV();
		void changestatusV();
		void deletetransaction_in(nnode * from);
		void deletetransaction_out(nnode * to);
		void newtransaction_in(nnode * from,nnode * to,float amount);
		void newtransaction_out(nnode * from, nnode * to,float amount);
		void newtransaction(nnode * from,nnode * to,float amount); 
		void deletetransaction(nnode * from,nnode * to);
		float amount_in();
		float amount_out();			
};





#endif