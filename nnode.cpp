#include "nnode.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



using namespace std;

nnode::nnode(nodeG * g_node){  //wrapper for graph node (nodeG) so it can be used in double linked lists in the hashtable buckets
	graph_node = g_node;
	next=NULL;
	prv=NULL;
}

nnode::~nnode(){delete graph_node;}

nnode * nnode::get_next(){return next;}

nnode * nnode::get_prv(){return prv;}

nodeG * nnode::get_graph_node(){return graph_node;}

void nnode::set_next(nnode * n){next = n;}

void nnode::set_prv(nnode * p){prv = p;}



//--------------------------------------------------------------------------------------------

nodeG::nodeG(int id){ // graph node
	
	node_id = id;
	in_transactions = NULL;
	out_transactions = NULL;
	all_transactions_in = 0;
	all_transactions_out = 0;
	visited = false;

}

nodeG::~nodeG(){ 		
	while(in_transactions != NULL){ //delete allocated space for incoming transaction
		tnode * temp_transaction = in_transactions->get_next();
		delete in_transactions;
		in_transactions = temp_transaction;
	}
	while(out_transactions != NULL){//delete allocated space for outgoing transaction
		tnode * temp_transaction = out_transactions->get_next();
		delete out_transactions;
		out_transactions = temp_transaction;
	}
}

void nodeG::print_out_trans(){ //print all outgoing transactions
	tnode * tmp = out_transactions;
	if (tmp==NULL)
		return;
	for(int i=0;i<all_transactions_out;i++){
		cout <<" (" <<tmp->get_transaction()->get_id_to()->get_graph_node()->get_node_id()<<"," <<tmp->get_transaction()->get_amount()<<")";
		tmp=tmp->get_next();
	}


}

void nodeG::print_in_trans(){ //print all incoming transactions
	tnode * tmp = in_transactions;
	if (tmp==NULL)
		return;
	for(int i=0;i<all_transactions_in;i++){
		cout <<" (" <<tmp->get_transaction()->get_id_from()->get_graph_node()->get_node_id()<<"," <<tmp->get_transaction()->get_amount()<<")";
		tmp=tmp->get_next();
	}


}

int nodeG::get_node_id(){return node_id;}


void nodeG::newtransaction(nnode * from,nnode * to,float amount){ //simple handler for new transactions 

	if (from->get_graph_node()->get_node_id() == node_id )
		newtransaction_out(from,to,amount);
	else if(to->get_graph_node()->get_node_id() == node_id )
		newtransaction_in(from,to,amount);
	else
		perror("Wrong transaction nodes");
}

int nodeG::get_trans_in(){return all_transactions_in;}

int nodeG::get_trans_out(){return all_transactions_out;}

void nodeG::newtransaction_in(nnode * from,nnode * to,float amount){//insert a new incoming transaction and update

	bool done=false;
	tnode * tmp_transactions_in = in_transactions;
	if (all_transactions_in==0){
				transaction * newtransaction = new transaction(from,to,amount);
				tnode * newtnode = new tnode(newtransaction);
				in_transactions = newtnode;
				all_transactions_in++;
	}else{
		for (int i = 0; i < all_transactions_in; i++){
			if(tmp_transactions_in->get_transaction()->get_id_from()->get_graph_node()->get_node_id() == from->get_graph_node()->get_node_id()){
				tmp_transactions_in->get_transaction()->new_transaction(from->get_graph_node()->get_node_id(),to->get_graph_node()->get_node_id(),amount);
				done = true;
				break;
			}
			tmp_transactions_in->get_next();
		}
		if(!done){
			transaction * newtransaction = new transaction(from,to,amount);
			tnode * newtnode = new tnode(newtransaction);
			newtnode->set_next(in_transactions);
			in_transactions = newtnode;
			all_transactions_in++;
		}
	}
}

void nodeG::newtransaction_out(nnode * from,nnode * to,float amount){ //insert a new outgoing transaction and update

	bool done=false;
	tnode * tmp_transactions_out = out_transactions;
	if (all_transactions_out==0){
				transaction * newtransaction = new transaction(from,to,amount);
				tnode * newtnode = new tnode(newtransaction);
				out_transactions = newtnode;
				all_transactions_out++;
	}else{
		for (int i = 0; i < all_transactions_out; i++){
			if(tmp_transactions_out->get_transaction()->get_id_to()->get_graph_node()->get_node_id() == to->get_graph_node()->get_node_id()){
				tmp_transactions_out->get_transaction()->new_transaction(from->get_graph_node()->get_node_id(),to->get_graph_node()->get_node_id(),amount);
				done=true;
				break;
			}
			tmp_transactions_out->get_next();
		}
		if(!done){
				transaction * newtransaction = new transaction(from,to,amount);
				tnode * newtnode = new tnode(newtransaction);
				newtnode->set_next(out_transactions);
				out_transactions = newtnode;
				all_transactions_out++;

		}
	}

}


void nodeG::deletetransaction_out(nnode * from){ //delete an outgoing transaction and update lists
	tnode * current=out_transactions;
	tnode * prv=NULL;
	while(current!=NULL){

		if((from->get_graph_node()->get_node_id()==current->get_transaction()->get_id_to()->get_graph_node()->get_node_id())) {
			if(prv==NULL)
				out_transactions = current->get_next();
			else
				prv->set_next(current->get_next());
			delete current;
			all_transactions_out--;
			cout << "success : deleted transaction (from)" <<endl;
			return;
		}
		prv=current;
		current=current->get_next();
	}
	cout<<"no such transaction"<<endl;
}

void nodeG::deletetransaction_in(nnode * to){  //delete an incoming transaction and update lists

	tnode * current=in_transactions;
	tnode * prv=NULL;
	while(current!=NULL){

		if((to->get_graph_node()->get_node_id()==current->get_transaction()->get_id_from()->get_graph_node()->get_node_id())) {
			if(prv==NULL)
				in_transactions = current->get_next();
			else
				prv->set_next(current->get_next());
			delete current;
			all_transactions_in--;
			cout << "success : deleted transaction (to)" <<endl;
			return;
		}
		prv=current;
		current=current->get_next();
	}
	cout<<"no such transaction"<<endl;
}


tnode * nodeG::get_conns_in(){return in_transactions;}

tnode * nodeG::get_conns_out(){return out_transactions;}

bool nodeG::isvisited(){return visited;}

void nodeG::changestatusNV(){visited=false;} 

void nodeG::changestatusV(){visited=true;}


void nodeG::deletetransaction(nnode * from,nnode * to){ //delete a transaction that the node is involved
	if(from->get_graph_node()->get_node_id() == node_id){
		deletetransaction_out(to); 
	}else{
		deletetransaction_in(from);
	}
}

float nodeG::amount_in(){//sum all incoming transactions
	float sum = 0;
	tnode * tmp = in_transactions;

	for(int i=0;i<all_transactions_in;i++){
		sum+=tmp->get_transaction()->get_amount();
		tmp=tmp->get_next();
	}
	return sum;
}

float nodeG::amount_out(){//sum all outgoing transactions
	float sum = 0;
	tnode * tmp = out_transactions;
	for(int i=0;i<all_transactions_out;i++){
		sum+=tmp->get_transaction()->get_amount();
		tmp=tmp->get_next();
	}
	return sum;
}

//-------------------------------------------------------------------

transaction::transaction (nnode * fr,nnode * t,float amount){ //memeber of tnode ,has info about the transaction (to,from,amount)
	id_from=fr;
	id_to=t;
	cash_amount=amount;
}

transaction::~transaction(){return;}

int transaction::new_transaction(int from,int to,float amount){
	if ((from == id_from->get_graph_node()->get_node_id()) && (to == id_to->get_graph_node()->get_node_id()))
		cash_amount += amount;
	else
		cout << "error : ivalid transaction change "<<endl;
		
}

nnode * transaction::get_id_to(){return id_to;}

nnode * transaction::get_id_from(){return id_from;}

float transaction::get_amount(){return cash_amount;}
//--------------------------------------------------------------------------------------------------------------------------


tnode::tnode(transaction * tr){ //used in transaction lists incoming/outgoing
	t_transaction = tr;
	next=NULL;
	prv=NULL;
}

tnode::~tnode(){delete t_transaction;}

tnode * tnode::get_next(){return next;}

tnode * tnode::get_prv(){return prv;}

transaction * tnode::get_transaction(){return t_transaction;}

void tnode::set_next(tnode * n){next = n;}

void tnode::set_prv(tnode * p){prv = p;}



//----------------------------------------------------
