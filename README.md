# Transaction System (Graph)

A Bank Acount System represented by a Graph and a Hashtable


##Graph and Hashtable

A directed Graph which grows dynamically when new nodes/accounts are inserted and new transactions are made

A hashtable contains of an array of pointers (buckets) to nnodes and each bucket extends when there is a collision detected by creating an overflow list
each bucket is a linked list of nnodes

Each nnode inludes a pointer to a graph node(nodeG) and a pointer to the next nnode 

A nodeG contains two pointers to lists of ttnodes (transactions going in, transcations going out) each with a corresponding counter and a bool variable (used in DFS like functions)

A tnode inludes a pointer to a transaction node(transaction) and a pointer to the next node 
they are used in linked lists

A transaction node consists of two nnode pointers (from to) and the amount of the transaction

Functions of the graph with paths are DFS based


## Commands

   * createnodes N1 N2 N3 N4 ....
	
	>creates the nodes/accounts with ids N1 N2 N3 N4 ....
   * delnodes N1 N2 N3 N4 ....
    
    > deletes the nodes/accounts with ids N1 N2 N3 N4 ....
   * addtran N1 N2 amount
   	
   	> adds a transaction between nodes N1 N2 with the amount given
   * deltran N1 N2
    
    > deletes a transaction between nodes
   * lookup [in | out | sum] N
   	
   	> prints the incoming | outgoing | total sum of the node N 
   * triangle N k
    
    > checks and prints if there is a triangle of transactions(starts and ends from the same node N) with at least k euros
   * conn N1 N2
   	
   	> checks and prints if there is a connection/path between nodes N1 N2
   * allcycles N
    
    > checks and prints all the cycles that the node/account N is involved in
   * traceflow N l
   	
   	> prints all the paths with the given depth l that start from the node N
   * bye
   	
   	> deletes the graph
   * print
   	
   	> prints the whole graph
   * exit
   	
   	> deletes the graph and exits the program

## Comand File

A command file can be given as a command line argument with the flag -f
the commands accepted are the same as above

## Arguments

 * flag -b size of the Hashtable
 * flag -f command file
