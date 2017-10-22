#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

hashtable::hashtable(int size){ //create a hashtable of given size , each bucket points to nnode pointer

	table_size=size;
	buckets = (nnode **)malloc(sizeof(nnode *)*size);
	for(int i=0;i<size;i++)
		buckets[i] = NULL;

}


void hashtable::delete_bucket_content(int i){ //delete each buckets content

	nnode * start = buckets[i];
	nnode * tmp = start;
	while(start !=NULL ){
		tmp=start->get_next();
		delete start;
		start=tmp;
	}

}

hashtable::~hashtable(){

	for(int i=0;i<table_size;i++){ 
		delete_bucket_content(i); 
	}
	free (buckets);

}

// change each nodes status to not visited

void hashtable::changestats(){
		for(int i=0;i<table_size;i++){ 
			nnode * tmp = buckets[i];
			while(tmp!=NULL){
				tmp->get_graph_node()->changestatusNV();
				tmp=tmp->get_next();
			}
		}
}

//insert new node in the correct bucket

int hashtable::insert_node(nnode * n){

	if(return_node(n->get_graph_node()->get_node_id())==NULL){
		nnode * insert_here;
		int key = hash_func(n->get_graph_node()->get_node_id());
		insert_here = buckets[key];
		if(buckets[key]==NULL){
			buckets[key] = n;
		}else{
			n->set_next(buckets[key]);
			buckets[key] = n;
		}
		cout << "success : created " << n->get_graph_node()->get_node_id()<<endl;
		}else{
		cout << "failure (insert_node): node already exists " << n->get_graph_node()->get_node_id()<<endl;
		delete n;
}

}

int hashtable::get_size(){return table_size;}


void hashtable::print_bucket(int i){

	if(buckets[i]==NULL)
		return;
	nnode * printb = buckets[i];
	while(printb!=NULL){
		cout <<"vertex ("<< printb->get_graph_node()->get_node_id()<<") ";
		printb->get_graph_node()->print_out_trans();
		cout <<endl;
		printb=printb->get_next();
	}
}


//delete the node given 

int hashtable::delete_node(int node_id){
	if((return_node(node_id)==NULL)){
		cout <<"failure (delete node): no such node exists "<<node_id << endl;
		return 0;
	}

	if((return_node(node_id)->get_graph_node()->get_trans_in()==0)&&(return_node(node_id)->get_graph_node()->get_trans_out()==0)){
		int key = hash_func(node_id);
		nnode * prv=NULL;
		nnode * current=buckets[key];
	 	while(current!=NULL){
			if(current->get_graph_node()->get_node_id()==node_id){
				if(prv==NULL)
					buckets[key]=current->get_next();
				else
					prv->set_next(current->get_next());
				delete current;
				cout << "success : deleted " <<node_id<< endl;
				break;
			}
			prv=current;
			current=current->get_next();
		}
	}else{
		cout << "failure (delete node) : node still has transactions" << endl;
	}
}


int hashtable::hash_func(int n){

	return (n%table_size); 

}

//returns the pointer to the node asked or NULL if it doesn't exist

nnode * hashtable::return_node(int node_id){

	int key = hash_func(node_id);
	nnode * current=buckets[key];

	 while(current!=NULL){
	 	if(current->get_graph_node()->get_node_id()==node_id)
	 		return current;
	 	current=current->get_next();
	}
	return NULL;
}

void hashtable::create_new_transaction(int from,int to,float amount){

	if((return_node(from)!=NULL)&&(return_node(to)!=NULL)){

		return_node(from)->get_graph_node()->newtransaction(return_node(from),return_node(to),amount);
		return_node(to)->get_graph_node()->newtransaction(return_node(from),return_node(to),amount);
		cout << "success : added transaction  " <<from <<"  "<<to<< "  " << amount <<endl;

	}else
		cout << "failure (new transaction): node(s) is(are) not created"<<endl;
}
