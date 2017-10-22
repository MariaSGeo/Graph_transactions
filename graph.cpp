#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

graph::graph(hashtable * h){

	hasht = h;
	n_transactions = 0;
	n_nodes = 0;
}

graph::~graph(){delete hasht;}

int graph::createnodes(int * newnodes,int nnodes){  //newnodes(iserted in the hashtable)

	nnode * new_node;
	nodeG * new_graph_node;

	for(int i=0;i<nnodes;i++){
		new_graph_node = new nodeG(newnodes[i]);
		new_node = new nnode(new_graph_node);
		hasht->insert_node(new_node);
	}
}

int graph::delnodes (int * newnodes,int nnodes){    //delete node from hashtable

	for(int i=0;i<nnodes;i++)
		hasht->delete_node(newnodes[i]);
		
}

void graph::changestats(){hasht->changestats();}    //all to not visited

int graph::addtran (int  n1,int n2,float amount){hasht->create_new_transaction(n1,n2,amount);}

int graph::deltran (int  n1,int n2){

if((hasht->return_node(n1)==NULL) || (hasht->return_node(n2)==NULL)){
    cout<<"failure : (delete tran) node(s) do not exist " << endl;
    return -1;
}

	   hasht->return_node(n1)->get_graph_node()->deletetransaction(hasht->return_node(n1),hasht->return_node(n2));
	   hasht->return_node(n2)->get_graph_node()->deletetransaction(hasht->return_node(n1),hasht->return_node(n2));
}

int graph::lookup_in (int n){
    if(hasht->return_node(n)!=NULL){
        cout << "success : lookup in (" <<n<<") ";
       cout<<(hasht->return_node(n)->get_graph_node()->amount_in())<<endl;
    }else
        cout << "failure (lookup in) : node does not exist" <<endl;
}

int graph::lookup_out (int n){
     if(hasht->return_node(n)!=NULL){
        cout << "success : lookup out (" <<n<<") ";
        cout <<(hasht->return_node(n)->get_graph_node()->amount_out())<<endl;
    }else
        cout << "failure (lookup out) : node does not exist" <<endl;
}

int graph::lookup_sum (int n){
    if(hasht->return_node(n)!=NULL){
        cout << "success : lookup sum (" <<n<<") ";
        cout<<((hasht->return_node(n)->get_graph_node()->amount_in()) - (hasht->return_node(n)->get_graph_node()->amount_out()))<<endl;
    }else
        cout << "failure (lookup sum) : node does not exist" <<endl;
}

int graph::triangle (int n,int k){
    if(hasht->return_node(n)!=NULL)
        tri(hasht->return_node(n),k);
    else
        cout << "failure (triangle) : node does not exist" <<endl;
}

int graph::conn (int n1,int n2){   
    if((hasht->return_node(n1)!=NULL) && (hasht->return_node(n2)!=NULL)){
        if((path(hasht->return_node(n1),hasht->return_node(n2))==0))
            cout << "connection ("<<n1<<","<<n2<<") not found"<<endl ;
        else 
            cout <<")"<<endl;
    }else
        cout << "failure (conn): node(s) is(are) not created " << endl;
}

void graph::allcycles (int n){
    //cout << "NEWALLC" <<endl;
    if(hasht->return_node(n)!=NULL)
        allc(hasht->return_node(n),hasht->return_node(n),NULL,0);
    else
        cout << "failure (allcycles) : node does not exist" <<endl;
}

int graph::traceflow (int n,int pathl){
    if(hasht->return_node(n)==NULL){
        cout << "failure (traceflow) : node does not exist" <<endl;
        return 0;
    }else
        trf(hasht->return_node(n),NULL,0,pathl,0);
}

void graph::bye(){

	

}

void graph::printgraph(){
	int sizeh = hasht->get_size();
	for(int i =0;i<sizeh;i++)
		hasht->print_bucket(i);
}

void graph::DFS(nnode * n){

    tnode * connt = n->get_graph_node()->get_conns_out();
    int k = n->get_graph_node()->get_trans_out();
    tnode ** tmp;
    tmp = (tnode**)malloc(sizeof(tnode*)*k);
    for (int i = 0 ; i <k;i++ ){
        tmp[i] = connt;
        connt = connt->get_next();
    }
    cout << n->get_graph_node()->get_node_id()<<endl;
    n->get_graph_node()->changestatusV();

    for(int i =0;i<k;i++)    
        if(!(tmp[i]->get_transaction()->get_id_to()->get_graph_node()->isvisited()))
            DFS(tmp[i]->get_transaction()->get_id_to());
        
    free(tmp); 
}

int graph::path(nnode * n1,nnode * n2){

    if(n1->get_graph_node()->get_node_id()==n2->get_graph_node()->get_node_id()){
        cout << "success : conn ( " ;
        cout << n1->get_graph_node()->get_node_id();
        cout << " ";
        return 1;
    }else{
        tnode * connt = n1->get_graph_node()->get_conns_out();
        int k = n1->get_graph_node()->get_trans_out();
        tnode ** tmp;
        tmp = (tnode**)malloc(sizeof(tnode*)*k);
        for (int i = 0 ; i <k;i++ ){
            tmp[i] = connt;
            connt = connt->get_next();
        }
        n1->get_graph_node()->changestatusV();
        for(int i =0;i<k;i++)
        {
            if(!(tmp[i]->get_transaction()->get_id_to()->get_graph_node()->isvisited())) {
               
                if(path(tmp[i]->get_transaction()->get_id_to(),n2)==1){
                    cout << n1->get_graph_node()->get_node_id();
                    cout <<" ";
                    free(tmp);
                    return 1;
                }
            }
        }
        free(tmp); 
        return 0;
    }
}

int graph::tri(nnode * n1,int amount){
    bool found=false;
    tnode * connt1 = n1->get_graph_node()->get_conns_out();
    int k1 = n1->get_graph_node()->get_trans_out();
    tnode ** tmp1;
    tmp1 = (tnode**)malloc(sizeof(tnode*)*k1);
    for (int i = 0 ; i <k1;i++ ){
        tmp1[i] = connt1;
        connt1 = connt1->get_next();
    }
    for (int i =0;i <k1;i++ ) {
        tnode * connt2 = tmp1[i]->get_transaction()->get_id_to()->get_graph_node()->get_conns_out();
        int k2 = tmp1[i]->get_transaction()->get_id_to()->get_graph_node()->get_trans_out();
        tnode ** tmp2;
        tmp2 = (tnode**)malloc(sizeof(tnode*)*k2);
        for (int j = 0 ; j <k2;j++ ){
            tmp2[j] = connt2;
            connt2 = connt2->get_next();
        }
        for (int j = 0 ; j <k2;j++ ){
            tnode * connt3 = tmp2[j]->get_transaction()->get_id_to()->get_graph_node()->get_conns_out();
            int k3 = tmp2[j]->get_transaction()->get_id_to()->get_graph_node()->get_trans_out();
            tnode ** tmp3;
            tmp3 = (tnode**)malloc(sizeof(tnode*)*k3);
            for (int k = 0 ; k <k3;k++ ){
                tmp3[k] = connt3;
                connt3 = connt3->get_next();
            }
            for (int k = 0 ; k <k3;k++ ){
                if((tmp2[j]->get_transaction()->get_amount()>=amount)&&(tmp1[i]->get_transaction()->get_amount()>=amount)&&(tmp3[k]->get_transaction()->get_amount()>=amount)&&(n1->get_graph_node()->get_node_id() == tmp3[k]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()) ){
                    cout << "success : triangle ("<<n1->get_graph_node()->get_node_id()<<"," <<amount<<") (";
                    cout << tmp3[k]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()<<" ";
                    cout << tmp1[i]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()<<" ";
                    cout << tmp2[j]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()<<")";//<<endl;
                    found = true;
                }
            }
            free(tmp3);
        } 
        free(tmp2);   
    }
    free(tmp1);
        if(!found)
            cout << "success : triangle ("<<n1->get_graph_node()->get_node_id()<<"," <<amount<<") not found"<<endl;
}


/*
int (nnode * curr,nnode * vlist){

}

int  graph::allc(nnode * curr,nnode * start,nnode * vlist,int times){
cout << curr->get_graph_node()->get_node_id() <<" "<<times<< endl;

    tnode * connt = curr->get_graph_node()->get_conns_out();
    int k = curr->get_graph_node()->get_trans_out();
    tnode ** tmp;
    tmp = (tnode**)malloc(sizeof(tnode*)*k);
    for (int i = 0 ; i <k;i++ ){
        tmp[i] = connt;
        connt = connt->get_next();
    }
    
    if((curr->get_graph_node()->get_node_id()==start->get_graph_node()->get_node_id()) && (times>=2)){
        if((times==2)&&(uniques(vlist)==1)||(times>2))
            cout << "success : allcycles ( " ;
            nnode * tmp=vlist;
            while(tmp!=NULL){
                cout << tmp->get_graph_node()->get_node_id()<< " ";
                tmp=tmp->get_next();
            }
            cout <<")"<<endl;
           //del edw?
            return 1;
    }
    if(curr->get_graph_node()->isvisited()){
        return 0;
        free(tmp); 
    }
    else{
        curr->get_graph_node()->changestatusV();
        nodeG * g=new nodeG(curr->get_graph_node()->get_node_id());
            nnode * nn = new nnode(g);
            nn->set_next(vlist);
            vlist = nn;
    }


    for(int i =0;i<k;i++)  {  
            nnode * tmp2=vlist;
            allc(tmp[i]->get_transaction()->get_id_to(),start,vlist,times+1);
               
    }
    nnode *  tmpd=vlist;
    vlist=vlist->get_next(); //ti tha ta kanw????
    delete tmpd;
    nnode * t = vlist;
   
    //del edw??
    free(tmp); 
    return 0;
}*/


int  graph::allc(nnode * curr,nnode * start,nnode * vlist,int times){

    
    curr->get_graph_node()->changestatusV();
    nodeG * g=new nodeG(curr->get_graph_node()->get_node_id());
    nnode * nn = new nnode(g);
    nn->set_next(vlist);
    vlist = nn;

    tnode * connt = curr->get_graph_node()->get_conns_out();
    int k = curr->get_graph_node()->get_trans_out();
    tnode ** tmp;
    tmp = (tnode**)malloc(sizeof(tnode*)*k);
    for (int i = 0 ; i <k;i++ ){
        tmp[i] = connt;
        connt = connt->get_next();
    }
    
    if((curr->get_graph_node()->get_node_id()==start->get_graph_node()->get_node_id()) && (times>=3)){
            cout << "success : allcycles ( " ;
            nnode * tmp=vlist;
            while(tmp!=NULL){
                cout << tmp->get_graph_node()->get_node_id()<< " ";
                tmp=tmp->get_next();
            }
            cout <<")"<<endl;
           //del edw?
            return 1;
    }
    for(int i =0;i<k;i++)  {  
           //cout << curr->get_graph_node()->get_node_id() <<" "<<times<<"  "<<k <<" ";
           //cout << tmp[i]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()<<endl;
            if( (!(tmp[i]->get_transaction()->get_id_to()->get_graph_node()->isvisited())) || ((tmp[i]->get_transaction()->get_id_to()->get_graph_node()->get_node_id()==start->get_graph_node()->get_node_id())&&(times>=2)))
                allc(tmp[i]->get_transaction()->get_id_to(),start,vlist,times+1);
               
    }
    nnode *  tmpd=vlist;
    vlist=vlist->get_next(); //ti tha ta kanw????
    delete tmpd;
    nnode * t = vlist;
   
    //del edw??
    free(tmp); 
    return 0;
}


int checksame(nnode * curr,nnode * list){
    nnode * tmp=list;
    while(tmp!=NULL){
        if(curr->get_graph_node()->get_node_id() == tmp->get_graph_node()->get_node_id())
            return 0;
        tmp=tmp->get_next();
    }
    return 1;
}

int  graph::trf(nnode * curr,nnode * vlist,int times,int pathl,int amount){

tnode * connt = curr->get_graph_node()->get_conns_out();
    int k = curr->get_graph_node()->get_trans_out();
    tnode ** tmp;
    tmp = (tnode**)malloc(sizeof(tnode*)*k);
    for (int i = 0 ; i <k;i++ ){
        tmp[i] = connt;
        connt = connt->get_next();
    }
    
    if((times==pathl)&&(checksame(curr,vlist)==1)){
        cout << "success : traceflow (";
        nnode * tmp=vlist;
        if(!(curr->get_graph_node()->isvisited()))
                 cout << curr->get_graph_node()->get_node_id()<<" ";

        while(tmp!=NULL){
            cout << tmp->get_graph_node()->get_node_id()<< " ";
            tmp=tmp->get_next();
        }
        cout <<") = "<<amount<<endl;
       //del edw?
        return 1;
    }
    if(curr->get_graph_node()->isvisited()){
        return 0;
        free(tmp); 
    }else{
        curr->get_graph_node()->changestatusV();
        nodeG * g=new nodeG(curr->get_graph_node()->get_node_id());
            nnode * nn = new nnode(g);
            nn->set_next(vlist);
            vlist = nn;
    }


    for(int i =0;i<k;i++)  {  
            nnode * tmp2=vlist;
            trf(tmp[i]->get_transaction()->get_id_to(),vlist,times+1,pathl,amount+tmp[i]->get_transaction()->get_amount());
               
    }
    nnode *  tmpd=vlist;
    vlist=vlist->get_next(); //ti tha ta kanw????
    delete tmpd;
    nnode * t = vlist;
    /*while(t!=NULL){
        cout << t->get_graph_node()->get_node_id()<<"<--";
        t=t->get_next();
    }
    cout << endl;*/
    //del edw??
    free(tmp); 
    return 0;
}

