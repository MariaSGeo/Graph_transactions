#ifndef FUNCS_H
#define FUNCS_H


//functions to proccess input correctly



bool handle_createnodes(int * node);
bool handle_delnodes(int * node);
bool handle_addtrans(int * n1,int * n2,float * amount);
bool handle_deltrans(int * n1,int * n2);
bool handle_lookup(int * type,int * n);
bool handle_triangle(int * n,float * amount);
bool handle_conn(int * n1,int * n2);
bool handle_allcycles(int * n);
bool handle_traceflow(int * n,int * depth);
bool handle_bye();
bool handle_print();

#endif
