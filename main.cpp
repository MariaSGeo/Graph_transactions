#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nnode.h"
#include "hashtable.h"
#include "graph.h"
#include "funcs.h"

#define BUFFERSIZE 256

using namespace std;

int main (int argv,char ** argc){

	char * filedesc;
	int hash_size;
	bool manual = true;
    char *token,*token1;
    char buffer[BUFFERSIZE];


	/*----------------------------
			arguments checks  
	  ----------------------------*/

	if(argv<3){
		cout<< "not enough parameters"<<endl;
		return -1;
	}else if ((argv>=3)&&(argv<=5)){
		if (argv==3){
			if(strcmp(argc[1],"-b")!=0) {
				cout << "there is no param -b "<<endl;
				return -1;
			}
		}else{
			if (argv == 5){
				if((strcmp(argc[1],"-b")!=0)&&(strcmp(argc[3],"-b")!=0)){
					cout << "there is no param -b"<<endl;
					return -1;
				}
			}	
		}
	}else{
		cout << "too many parameters" <<endl;
		return -1;
	}


	/*-------------------------------	
			arguments and init 
	--------------------------------*/

	if(argv == 3)
		hash_size == atoi(argc[2]);
	else{
		if(strcmp(argc[1],"-b")==0){
			hash_size = atoi(argc[2]);
			filedesc = argc[4];
		}else{
			hash_size = atoi(argc[4]);
			filedesc = argc[2];
		}	
		manual = false;
	}

	hashtable * ht = new hashtable(hash_size);
	graph * n_graph = new graph(ht);

	
	if(!manual){	//read from file

		FILE * fp;
		fp = fopen(filedesc,"r");
		if(fp == NULL){
      		cout << "Error opening file" << endl;
      		return-1;
   		}
   		while(fgets(buffer,BUFFERSIZE,fp)!=NULL){
     		//cout << buffer;
     		token=strtok(buffer," ");
     		if ((strcmp(token,"createnodes"))==0){ //create nodes ,each with a unique id
     			int node;
     			while((token1=strtok(NULL," "))!=NULL){
     				node=atoi(token1);
     				n_graph->createnodes(&node,1);
     			}
     		}
 
     		if ((strcmp(token,"delnodes"))==0){	//delete nodes with given ids
     			int node;
     			while((token1=strtok(NULL," "))!=NULL){
     				node=atoi(token1);
     				n_graph->delnodes(&node,1);
     				//token = strtok(NULL," ");
     				//cout <<"hey?" << endl; 
     			}

     		}
     			
     		if ((strcmp(token,"addtran"))==0){ //add a transaction between nodes
     			int n1,n2;
                    float amount;
     			if(handle_addtrans(&n1,&n2,&amount)){
     				n_graph->addtran(n1,n2,amount);
     				//n_graph->printgraph();
     				//getchar();
     			}
     			else
     				cout << "invalid instruction" << endl;
     		}
     		if ((strcmp(token,"deltran"))==0){	//delete a transaction between nodes
     			int n1,n2;
     			if(handle_deltrans(&n1,&n2)){
     				n_graph->deltran(n1,n2);
     				//n_graph->printgraph();
     				//getchar();
     			}
     			else
     				cout << "invalid instruction" << endl;

     		}

     		if ((strcmp(token,"lookup"))==0){	//look up 
     			int type,n;
     			if(handle_lookup(&type,&n))
     				if(type==1)
     					n_graph->lookup_in(n);	//incoming transactions
     				else if(type==2)
     					n_graph->lookup_out(n);	//outgoin transactions
     				else	
     					n_graph->lookup_sum(n); //the sum of incoming and outgoing transactions
     			else
     				cout << "invalid instruction" << endl;	

     		}

     		if ((strcmp(token,"triangle"))==0){	//check and print if there is a triangle of transactions (starts and ends from the same node)
     			int n;
                    float amount;
     			if(handle_triangle(&n,&amount)){
     				n_graph->triangle(n,amount);
                         cout << endl;
     			}else
     				cout << "invalid instruction" << endl;

     		}

     		if ((strcmp(token,"conn"))==0){ //check and print if there is a connection/path between two nodes
     			int n1,n2;
     			if(handle_conn(&n1,&n2)){
     				n_graph->conn(n1,n2);
     				n_graph->changestats();
     			}
     			else
     				cout << "invalid instruction" << endl;	

     		}

     		if ((strcmp(token,"allcycles"))==0){ //print all the cycles that the node/account with the given id is involved in
     			int n;
     			if(handle_allcycles(&n)){
     				n_graph->allcycles(n);
     				n_graph->changestats();
				}
     			else
     				cout << "invalid instruction" << endl;	
     		}

     		if ((strcmp(token,"traceflow"))==0){ // print all the paths with the given depth that start from the node with the given id
     			int n,depth;
     			if(handle_traceflow(&n,&depth)){
     				n_graph->traceflow(n,depth);
     				n_graph->changestats();
                         //getchar();
     			}else
     				cout << "invalid instruction" << endl;		
     		}

     		if ((strcmp(token,"bye\n"))==0){ //delete the graph and continue to manual instractions
     			cout << "bye" << endl;
     			delete n_graph;
                n_graph =NULL;
                //return 0;    


     		}
     		if ((strcmp(token,"print\n"))==0){ //print the graph
     			cout << "print" << endl;
     			n_graph->printgraph();
     		}
   		}
    	fclose(fp);
	}
          cout <<endl<<endl;
          cout << "insert one of the following commands : " << endl;
          cout << " createnodes N1 N2 N3 N4 ..." << endl;
          cout << " delnodes N1 N2 N3 N4 ...." << endl;
          cout << " addtran N1 N2 amount" << endl;
          cout << " deltran N1 N2" << endl;
          cout << " lookup [in | out | sum] N" << endl;
          cout << " triangle N k" << endl;
          cout << " conn N1 N2" << endl;
          cout << " allcycles N" << endl;
          cout << " traceflow N l" << endl;
          cout << " bye" << endl;
          cout << " print" << endl;
          cout << " exit" << endl; 
    cin.getline(buffer,BUFFERSIZE);
	while(strcmp(buffer,"exit")!=0) { // manual input
          token=strtok(buffer," ");
               if ((strcmp(token,"createnodes"))==0){
                    int node;
                    while((token1=strtok(NULL," "))!=NULL){
                         node=atoi(token1);
                         n_graph->createnodes(&node,1);
                    }
               }
 
               if ((strcmp(token,"delnodes"))==0){
                    int node;
                    while((token1=strtok(NULL," "))!=NULL){
                         node=atoi(token1);
                         n_graph->delnodes(&node,1);
                         //token = strtok(NULL," ");
                         //cout <<"hey?" << endl; 
                    }

               }
                    
               if ((strcmp(token,"addtran"))==0){
                    int n1,n2;
                    float amount;
                    if(handle_addtrans(&n1,&n2,&amount)){
                         n_graph->addtran(n1,n2,amount);
                         //n_graph->printgraph();
                         //getchar();
                    }
                    else
                         cout << "invalid instruction" << endl;
               }

               if ((strcmp(token,"deltran"))==0){
                    int n1,n2;
                    if(handle_deltrans(&n1,&n2)){
                         n_graph->deltran(n1,n2);
                    //n_graph->printgraph();
                         //getchar();
                    }
                    else
                         cout << "invalid instruction" << endl;

               }

               if ((strcmp(token,"lookup"))==0){
                    int type,n;
                    if(handle_lookup(&type,&n))
                         if(type==1)
                              n_graph->lookup_in(n);
                         else if(type==2)
                              n_graph->lookup_out(n);
                         else 
                              n_graph->lookup_sum(n);
                    else
                         cout << "invalid instruction" << endl;  

               }

               if ((strcmp(token,"triangle"))==0){
                    int n;
                    float amount;
                    if(handle_triangle(&n,&amount)){
                         n_graph->triangle(n,amount);
                         cout << endl;
                    }else
                         cout << "invalid instruction" << endl;

               }

               if ((strcmp(token,"conn"))==0){
                    int n1,n2;
                    if(handle_conn(&n1,&n2)){
                         n_graph->conn(n1,n2);
                         n_graph->changestats();
                    }
                    else
                         cout << "invalid instruction" << endl;  

               }

               if ((strcmp(token,"allcycles"))==0){
                    int n;
                    if(handle_allcycles(&n)){
                         n_graph->allcycles(n);
                         n_graph->changestats();
                    }
                    else
                         cout << "invalid instruction" << endl;  
               }

               if ((strcmp(token,"traceflow"))==0){
                    int n,depth;
                    if(handle_traceflow(&n,&depth)){
                         n_graph->traceflow(n,depth);
                         n_graph->changestats();
                         //getchar();
                    }else
                         cout << "invalid instruction" << endl;       
               }

               if ((strcmp(token,"bye\n"))==0){
                    cout << "bye" << endl;
                    delete n_graph;
                    n_graph =NULL;
                    //return 0;

               }
               if ((strcmp(token,"print\n"))==0){
                    cout << "print" << endl;
                    n_graph->printgraph();
               }
                         cin.getline(buffer,BUFFERSIZE);


     }
     if(n_graph!=NULL){
          delete n_graph;
     }
}
