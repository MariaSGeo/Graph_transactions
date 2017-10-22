#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "nnode.h"

class hashtable{
	private:

		int table_size;
		nnode ** buckets;

		void delete_bucket_content(int b);

	public:	
		hashtable(int size);
		~hashtable();
		int get_size();
		int insert_node(nnode * n);
		int delete_node(int node_id);
		void print_bucket(int i);
		int hash_func(int n);
		nnode * return_node(int node_id);
		void create_new_transaction(int from,int to,float amount);
		void changestats();
		
};

#endif